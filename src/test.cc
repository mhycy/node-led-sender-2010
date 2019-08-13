extern "C" {
#include <windows.h>
#include <tchar.h>

#include <node_api.h>
// #include "LEDSender2010Wrapper.h"

#define WM_LED_NOTIFY          1025
//是否等待下位机应答，直接发送所有数据
#define NOTIFY_NONE        1
//是否阻塞方式；是则等到发送完成或者超时，才返回；否则立即返回
#define NOTIFY_BLOCK       2
//是否将发送结果以Windows窗体消息方式送到调用得应用
#define NOTIFY_EVENT       4

typedef struct DEVICE_PARAM{
  WORD  devType;
  WORD  comSpeed;
  WORD  comPort;
  WORD  comFlow;
  WORD  locPort;
  WORD  rmtPort;
  WORD  srcAddr;
  WORD  dstAddr;
  char  rmtHost[16];
  DWORD txTimeo;   //发送后等待应答时间 ====超时时间应为txTimeo*txRepeat
  DWORD txRepeat;  //失败重发次数
  DWORD txMovewin; //划动窗口
  DWORD key;
  long  pkpLength; //数据包大小
}TDeviceParam, *PDeviceParam;

typedef struct SENDER_PARAM{
  TDeviceParam devParam;
  long  wmHandle;
  long  wmMessage;
  long  wmLParam;
  long  notifyMode;
}TSenderParam, *PSenderParam;

namespace LEDSender2010Wrapper {
    napi_value Test(napi_env env, napi_callback_info args) {
        // Node 相关声明
        napi_value return_value;
        napi_status status;

        TSenderParam SenderParam;
        memset(&SenderParam, 0, sizeof(TSenderParam));

        // 设定目标IP
        strcpy(SenderParam.devParam.rmtHost, "192.168.1.56");
        SenderParam.devParam.rmtPort = 6666;
        SenderParam.devParam.locPort = 8881;

        SenderParam.devParam.txTimeo = 10;
        SenderParam.devParam.txRepeat = 3;

        // 配置阻塞模式
        SenderParam.wmHandle = 0;
        SenderParam.wmMessage = WM_LED_NOTIFY;
        SenderParam.notifyMode = NOTIFY_BLOCK;
        
        // 初始化实例
        // HINSTANCE hInstance;
        // hInstance = LoadLibraryEx(_T("D:\\个人项目\\node-ledsender2010-wrapper\\build\\Debug\\LEDSender2010.dll"), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

        /*
        if(hInstance != NULL) {
            // 声明
            long (_stdcall *LED_GetBright)(TSenderParam *param);
            LED_GetBright = (long (_stdcall *)(TSenderParam *)) GetProcAddress(hInstance, "LED_GetBright");

            long result = LED_GetBright(&SenderParam);

            status = napi_create_int32(env, result, &return_value);
            if (status != napi_ok) { return nullptr; }
        } else {
            status = napi_create_int32(env, GetLastError(), &return_value);
        }
        */

        status = napi_create_int32(env, -100, &return_value);
        if (status != napi_ok) { return nullptr; }

        try {
            // 声明
            __declspec(dllimport) long LED_GetBright(TDeviceParam param);
            long result = 100;
            
            result = LED_GetBright(&SenderParam);

            status = napi_create_int32(env, result, &return_value);
            if (status != napi_ok) { return nullptr; }
        } catch(...) {
            status = napi_create_int32(env, GetLastError(), &return_value);
            if (status != napi_ok) { return nullptr; }
        }
        return return_value;
    }

    napi_value Init(napi_env env, napi_value exports) {
        napi_status status;
        napi_value fn;

        status = napi_create_function(env, nullptr, 0, Test, nullptr, &fn);
        if (status != napi_ok) return nullptr;

        status = napi_set_named_property(env, exports, "test", fn);
        if (status != napi_ok) return nullptr;
        return exports;
    }

    NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}  // namespace LEDSender2010Wrapper
}