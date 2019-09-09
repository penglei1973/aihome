#ifndef _PUART_H__
#define _PUART_H__

#include "uart.h"
#include <stdio.h>
#include <stdbool.h>

#define UART_DEV   "/dev/ttyUSB0"
#define SPEED      115200
#define FLOW_CTRL  0
#define DATABITS   8 
#define STOPBITS   1 
#define PARITY     'N'; 

extern bool u_recv(int uart_fd, char * rcv_buf, int len);
extern bool u_send(int uart_fd, char cmd);
extern int u_connect();
extern void u_close(int uart_fd);

#endif
