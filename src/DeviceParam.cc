#include <windows.h>

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

TSenderParam* allocTSenderParam() {
    return (TSenderParam *) malloc(sizeof(TSenderParam));
}

void freeTSenderParam(TSenderParam *param) {
    free(param);
}