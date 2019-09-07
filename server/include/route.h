#ifndef _ROUTE_H__
#define _ROUTE_H__
#include "phttp.h"
#include "funcMap.h"

typedef void * (* handleFunc)(responseWriter, request *); 

static handleFunc funcMap[1024];

extern void * Router(responseWriter, request *);
extern void * Register(void);

#endif
