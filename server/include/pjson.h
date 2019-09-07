#ifndef _PJSON_H__
#define _PJSON_H__
#define INT_MODE 1
#define STRING_MODE 2

#include <json/json.h>
#include "phttp.h"

extern void getValueFromBody(request * r, const char * field, void * arg);
extern void setValueToBody(responseWriter * w, const char * field, void * arg, int flag);

#endif
