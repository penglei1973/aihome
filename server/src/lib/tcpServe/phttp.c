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
#include "phttp.h"



/**********************************************************************/
/* Print out an error message with perror() (for system errors; based
 * on value of errno, which indicates system call errors) and exit the
 * program indicating an error. */
/**********************************************************************/
void error_die(const char *sc)
{
    perror(sc);
    exit(1);
}

/**********************************************************************/
/* This function starts the process of listening for web connections
 * on a specified port.  If the port is 0, then dynamically allocate a
 * port and modify the original port variable to reflect the actual
 * port.
 * Parameters: pointer to variable containing the port to connect on
 * Returns: the socket */
/**********************************************************************/
int startup(unsigned short *port)
{
    int httpd = 0;
    int on = 1;
    struct sockaddr_in name;

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    /*
       if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)  
       {  
       error_die("setsockopt failed");
       }
       */
    if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
        error_die("bind");
    if (*port == 0)  /* if dynamically allocating a port */
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
            error_die("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(httpd, 5) < 0)
        error_die("listen");
    return(httpd);
}

void accept_request(void * arg)
{
    int client = (intptr_t)arg;
    char buf[1024];
    request * r = (request *)malloc(sizeof(request));
    responseWriter w;
    memset(&w, 0, sizeof(w));
    w.client = client;

    recv(client, buf, sizeof(buf), 0);
    if (!bufToRequset(r, buf))
    {
        free(r);
        close(client);
        exit(-1);
    }

    w.funcCode = r->funcCode;
  
#if 1
    printf("msgType = %#x\n", r->msgType);
    printf("funcCode = %#x\n", r->funcCode);
    printf("bodyLen = %d\n", r->bodyLen);
    printf("body = %s\n", r->body);
#endif

    Router(w, r);

    free(r);
    close(client);
}

bool bufToRequset(request * r, const char * buf)
{
    if (0xaa != *((unsigned char *)(memcpy(&(r->msgType),
                buf, sizeof(r->msgType)))))
    {
        free(r);
        return false;
    }

    buf += sizeof(r->msgType);

    memcpy(&(r->funcCode), buf, sizeof(r->funcCode));
    buf += sizeof(r->funcCode);

    memcpy(&(r->bodyLen), buf, sizeof(r->bodyLen));
    buf += sizeof(r->bodyLen);

    memcpy(&(r->body), buf, r->bodyLen);
    *(r->body + r->bodyLen) = '\0';

    return true;
}

void * sendw(responseWriter w)
{
    unsigned char buf[1024];

    w.msgType = 0xff; 
    w.bodyLen = (short)strlen(w.body);
    
#if 1
    printf("msgType = %#x\n", w.msgType);
    printf("funcCode = %#x\n", w.funcCode);
    printf("bodyLen = %#x\n", w.bodyLen);
    printf("%s\n", w.body);
#endif

    /*
    send(w.client, (void *)&w.msgType, sizeof(unsigned char), 0);
    send(w.client, (void *)&w.funcCode, sizeof(unsigned char), 0);
    send(w.client, (void *)&w.bodyLen, sizeof(unsigned short), 0);
    send(w.client, (void *)w.body, w.bodyLen, 0);
    */

    memcpy(&buf[0], &w.msgType, 1); 
    memcpy(&buf[1], &w.funcCode, 1); 
    memcpy(&buf[2], &w.bodyLen, 2); 
    memcpy(&buf[4], w.body, w.bodyLen); 

    //send(w.client, (unsigned char *)&w + 4 , 4 + w.bodyLen, 0);
    send(w.client, (unsigned char *)buf , 4 + w.bodyLen, 0);
}
