#include <node_api.h>
#include <LEDSender2010.h>

namespace LEDSender2010 {
    napi_value Init(napi_env env, napi_value exports) {
        return exports;
    }

    NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}  // namespace LEDSender2010