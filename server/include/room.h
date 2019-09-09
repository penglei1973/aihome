#ifndef _ROOM_H__
#define _ROOM_H__

#include "phttp.h"
#include "route.h"

#define DEVICE_OPEN 0
#define DEVICE_CLOSE 1
#define DEVICE_GET 2

#define STATE_OPEN 0
#define STATE_CLOSE 1
#define STATE_ERROR 2

#define OPERATION_SUCCESSFUL 0
#define OPERATION_FAILED 1

#define LED1_ON   '0'
#define LED1_OFF  '1'
#define LED2_ON   '2'
#define LED2_OFF  '3'
#define FAN_ON    '4'
#define FAN_OFF   '5'
#define DOOR_ON   '6'
#define DOOR_OFF  '7'

extern void * changeTheLights(responseWriter w, request * r);
extern void * changeFan(responseWriter w, request * r);
extern void * changeDoor(responseWriter w, request * r);

#endif 
