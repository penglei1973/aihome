#include "puart.h"
#include <stdio.h>
#include <stdbool.h>

extern int  u_connect()
{
    const char * uart_dev = UART_DEV;
    int speed = SPEED;
    int flow_ctrl = FLOW_CTRL;   
    int databits = DATABITS;   
    int stopbits = STOPBITS;    
    int parity = PARITY;    

    int uart_fd;        
    int err;  

    uart_fd = uart_open("/dev/ttyUSB0");

    if (uart_fd <= 0)
    {
        printf("open dev failed!\n");
        return -1;
    }
    else
    {
        printf("uart_open success!\n");
    }

    err = uart_init(uart_fd, speed, flow_ctrl, databits, stopbits, parity);
    if (!err)
    {
        printf("uart_init failed!\n"); 
        return -1;
    }
    else
    {
        printf("uart_init success!\n");
    }

    return uart_fd;
}

bool u_recv(int uart_fd, char * rcv_buf, int len)
{
    struct timeval tv = {1,0};
    uart_recv(uart_fd, rcv_buf, len, &tv); 
    return true;
}

bool u_send(int uart_fd, char cmd)
{
    int err;

    err = uart_send(uart_fd, &cmd, 1);
    if (!err)
    {
        printf("uart_send failed!\n");
        return false;
    }
    else
    {
        printf("uart_send success!\n");
    }

    return true;
}

void u_close(int uart_fd)
{
    uart_close(uart_fd);
}
