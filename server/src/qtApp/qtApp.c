#include "phttp.h"
#include "route.h"

int main(void)
{
    Register();

    int server_sock = -1;
    unsigned short port = 6666;
    int client_sock = -1;
    struct sockaddr_in client_name;
    socklen_t  client_name_len = sizeof(client_name);
    pthread_t newthread;

    server_sock = startup(&port);
    printf("httpd running on port %d\n", port);

    int i;
    int *arg;
    int ret;
    int task_num;
    thread_pool_t *thread_pool;

    thread_pool = create_thread_pool(10,3);
    if(!thread_pool){
        printf("Fail to create_thread_pool");
        return -1;
    }

    while (1)
    {
        client_sock = accept(server_sock,
            (struct sockaddr *)&client_name,
            &client_name_len);
        if (client_sock == -1)
            error_die("accept");
        /* accept_request(&client_sock); */
        /*;
          if (pthread_create(&newthread , NULL, (void *)accept_request, (void *)(intptr_t)client_sock) != 0)
          perror("pthread_create");
          */
        if (requst_thread_work(thread_pool, (void *)accept_request, (void *)(intptr_t)client_sock) != 0)
            perror("fail to requst_thread_work");
    }

    close(server_sock);
    destroy_thread_pool(thread_pool);

    return(0);
}
