#ifndef _HOME_H__
#define _HOME_H__

#include <stdbool.h>
#include "phttp.h"
#include "route.h"

#define GET_SUCCESSED 0
#define GET_FAILED 1

#define GET_TEMPERATURE    't'
#define GET_HUMIDITY       'h'
#define GET_LIGHTINTENSITY 'l'

void * getTemperature (responseWriter w, request * r);
void * getHumidity (responseWriter w, request * r);
void * getLightIntensity (responseWriter w, request * r);
void * getVideo (responseWriter w, request * r);
void * getThreeAxisData (responseWriter w, request * r);
    

#endif
