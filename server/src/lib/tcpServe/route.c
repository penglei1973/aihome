#include "route.h"
#include "phttp.h"

void * Router(responseWriter w, request * r)
{
    ((handleFunc)funcMap[(int)r->funcCode])(w, r);
    return ;
}


void * Register(void)
{ 
    funcMap[0x00] = (handleFunc)userRegister;
    funcMap[0x01] = (handleFunc)userLogin;
    funcMap[0x02] = (handleFunc)forgotPassword;
    funcMap[0x21] = (handleFunc)sendOldPassword;
    funcMap[0x03] = (handleFunc)changePassword;
    funcMap[0x04] = (handleFunc)getTemperature;
    funcMap[0x05] = (handleFunc)getHumidity;
    funcMap[0x06] = (handleFunc)getLightIntensity;
    funcMap[0x07] = (handleFunc)getThreeAxisData;
    funcMap[0x08] = (handleFunc)changeTheLights;
    funcMap[0x09] = (handleFunc)changeFan;
    funcMap[0x0a] = (handleFunc)changeDoor;
    funcMap[0x0b] = (handleFunc)getVideo;
    return ;
}
