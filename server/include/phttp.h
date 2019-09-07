#ifndef _PHTTP_H__
#define _PHTTP_H__
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "thread_pool.h"
#include "linkqueue.h"

typedef struct ResponseWriter
{
    unsigned int client;
    unsigned char msgType;
    unsigned char funcCode;
    unsigned short bodyLen;
    unsigned char body[1024];
}responseWriter;

typedef struct Request
{
    unsigned char msgType;
    unsigned char funcCode;
    unsigned short bodyLen;
    unsigned char body[1024];
}request;

extern int startup(unsigned short *);
extern void error_die(const char *);
extern void accept_request(void *);
extern bool bufToRequset(request *, const char *);
extern void * sendw(responseWriter w);

#endif
