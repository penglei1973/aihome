#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pjson.h"

void * changeTheLights(responseWriter w, request * r)
{
    /*
       {“userToken”:”Qr5T4Y”,”deviceNumber”:0,
       “deviceCode” : 0, “userName”: ”Qrt3T4”} ->开灯
       {“userToken”: ”Qr5T4Y” ,”deviceNumber”:0,
       “deviceCode” : 1,“userName”: ”Qrt3T4”} ->关灯

       数据内容：{ “stateCode” : 0,”deviceState”:0} 用
       户操作成功设备处于打开状态
       数据内容：{ “stateCode” : 1，deviceState:1 } 用
       户操作失败设备处于关闭状态
       */

    char userName[1024];
    char userToken[1024];
    int deviceNumber;
    int deviceCode;
    int stateCode;
    int deviceState;

    int u_fd;
    char cmd;
    char rcv_buf[1024];

    getValueFromBody(r, "userName", userName); 
    getValueFromBody(r, "userToken", userToken); 
    getValueFromBody(r, "deviceNumber", (void *)&deviceNumber); 
    getValueFromBody(r, "deviceCode", (void *)&deviceCode); 

    if ((u_fd = u_connect()) < 0)
    {
        deviceState = STATE_CLOSE;
        stateCode = OPERATION_FAILED;
    }
    else
    {
        cmd = ((deviceNumber << 1) | deviceCode) + LED1_ON;
        if (u_send(u_fd, cmd))
        {
            deviceState = STATE_OPEN;
            stateCode = OPERATION_SUCCESSFUL;
            //收到M0信息
            u_recv(u_fd, rcv_buf, 1024);
            printf("msg from M0: %s\n", rcv_buf);
        }
        else
        {
            deviceState = STATE_ERROR;
            stateCode = OPERATION_FAILED;
        }
    }


    setValueToBody(&w, "deviceState", (void *)deviceState, INT_MODE);
    setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);

    u_close(u_fd);
    sendw(w);
}

void * changeFan(responseWriter w, request * r)
{
    
    char userName[1024];
    char userToken[1024];
    int deviceNumber;
    int deviceCode;
    int stateCode;
    int deviceState;

    int u_fd;
    char cmd;
    char rcv_buf[1024];

    getValueFromBody(r, "userName", userName); 
    getValueFromBody(r, "userToken", userToken); 
    getValueFromBody(r, "deviceNumber", (void *)&deviceNumber); 
    getValueFromBody(r, "deviceCode", (void *)&deviceCode); 

    if ((u_fd = u_connect()) < 0)
    {
        deviceState = STATE_CLOSE;
        stateCode = OPERATION_FAILED;
    }
    else
    {
        cmd = ((deviceNumber << 1) | deviceCode) + FAN_ON;
        cmd = deviceCode + FAN_ON;
        if (u_send(u_fd, cmd))
        {
            deviceState = STATE_OPEN;
            stateCode = OPERATION_SUCCESSFUL;
        }
        else
        {
            deviceState = STATE_ERROR;
            stateCode = OPERATION_FAILED;
        }
    }


    setValueToBody(&w, "deviceState", (void *)deviceState, INT_MODE);
    setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);

    u_close(u_fd);
    sendw(w);
}

void * changeDoor(responseWriter w, request * r)
{
    char userName[1024];
    char userToken[1024];
    int deviceNumber;
    int deviceCode;
    int stateCode;
    int deviceState;

    int u_fd;
    char cmd;
    char rcv_buf[1024];

    getValueFromBody(r, "userName", userName); 
    getValueFromBody(r, "userToken", userToken); 
    getValueFromBody(r, "deviceNumber", (void *)&deviceNumber); 
    getValueFromBody(r, "deviceCode", (void *)&deviceCode); 

    if ((u_fd = u_connect()) < 0)
    {
        deviceState = STATE_CLOSE;
        stateCode = OPERATION_FAILED;
    }
    else
    {
        cmd = ((deviceNumber << 1) | deviceCode) + DOOR_ON;
        if (u_send(u_fd, cmd))
        {
            deviceState = STATE_OPEN;
            stateCode = OPERATION_SUCCESSFUL;
            //收到M0信息
            u_recv(u_fd, rcv_buf, 1024);
            printf("msg from M0: %s\n", rcv_buf);
        }
        else
        {
            deviceState = STATE_ERROR;
            stateCode = OPERATION_FAILED;
        }
    }


    setValueToBody(&w, "deviceState", (void *)deviceState, INT_MODE);
    setValueToBody(&w, "stateCode", (void *)stateCode, INT_MODE);

    u_close(u_fd);
    sendw(w);
}
