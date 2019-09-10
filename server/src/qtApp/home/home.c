#include "home.h"
#include  <stdio.h>
#include  <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pjson.h"


void * getTemperature (responseWriter w, request * r)
{
    /*
       {“userName”:”Qrt3T4”,“userToken”: ”Qr5T4Y” ,
       ”deviceNumber”:0}
       数据内容：获得到温度并返回状态
       {“ temperature ”：20 ,“stateCode” : 0 }
       数据内容：未获取到温度
       { “ stateCode ” : 1 }
       */
    char userName[1024];
    char userToken[1024];
    int deviceNumber;
    int stateCode;

    int u_fd;
    char cmd;
    char rcv_buf[1024];

    getValueFromBody(r, "userName", userName); 
    getValueFromBody(r, "userToken", userToken); 
    getValueFromBody(r, "deviceNumber", (void *)&deviceNumber); 

    if ((u_fd = u_connect()) < 0)
    {
        stateCode = GET_FAILED;
        setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
    }
    else
    {
        cmd = GET_TEMPERATURE;
        if (u_send(u_fd, cmd))
        {
            if (u_recv(u_fd, rcv_buf, 1024))
            {
                stateCode = GET_SUCCESSED;
                setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
                setValueToBody(&w, "temperature", (void *)atoi(rcv_buf), INT_MODE);
            }
            else
            {
                stateCode = GET_FAILED;
                setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
            }
        }
        else
        {
            stateCode = GET_FAILED;
            setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
        }
    }

    u_close(u_fd);
    sendw(w);
}

void * getHumidity (responseWriter w, request * r)
{
    /*
    数据内容：获得到湿度
    {“humidity” ：21,“stateCode” : 0 }
    数据内容：未获取到湿度
    { “ stateCode ” : 1 }
    */
    char userName[1024];
    char userToken[1024];
    int deviceNumber;
    int stateCode;

    int u_fd;
    char cmd;
    char rcv_buf[1024];

    getValueFromBody(r, "userName", userName); 
    getValueFromBody(r, "userToken", userToken); 
    getValueFromBody(r, "deviceNumber", (void *)&deviceNumber); 

    if ((u_fd = u_connect()) < 0)
    {
        stateCode = GET_FAILED;
        setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
    }
    else
    {
        cmd = GET_HUMIDITY;
        if (u_send(u_fd, cmd))
        {
            if (u_recv(u_fd, rcv_buf, 1024))
            {
                stateCode = GET_SUCCESSED;
                setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
                setValueToBody(&w, "humidity", (void *)atoi(rcv_buf), INT_MODE);
            }
            else
            {
                stateCode = GET_FAILED;
                setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
            }
        }
        else
        {
            stateCode = GET_FAILED;
            setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
        }
    }

    u_close(u_fd);
    sendw(w);
}

void * getLightIntensity (responseWriter w, request * r)
{
    /*
    数据内容：获得到光照
    {“light” ：300,“stateCode” : 0}
    数据内容：未获取到光照
    { “ stateCode ” : 1 }
    */
    char userName[1024];
    char userToken[1024];
    int deviceNumber;
    int stateCode;

    int u_fd;
    char cmd;
    char rcv_buf[1024];

    getValueFromBody(r, "userName", userName); 
    getValueFromBody(r, "userToken", userToken); 
    getValueFromBody(r, "deviceNumber", (void *)&deviceNumber); 

    if ((u_fd = u_connect()) < 0)
    {
        stateCode = GET_FAILED;
        setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
    }
    else
    {
        cmd = GET_LIGHTINTENSITY;
        if (u_send(u_fd, cmd))
        {
            if (u_recv(u_fd, rcv_buf, 1024))
            {
                stateCode = GET_SUCCESSED;
                setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
                setValueToBody(&w, "light", (void *)atoi(rcv_buf), INT_MODE);
            }
            else
            {
                stateCode = GET_FAILED;
                setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
            }
        }
        else
        {
            stateCode = GET_FAILED;
            setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);
        }
    }

    u_close(u_fd);
    sendw(w);
}

void * getVideo (responseWriter w, request * r)
{}

void * getThreeAxisData (responseWriter w, request * r)
{}
    
