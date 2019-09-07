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
    return ;
}
