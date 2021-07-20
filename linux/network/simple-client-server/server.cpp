#include <stdio.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

#include "common_err.h"

#define SERVER_PORT (6060)

struct server_param
{
    struct sockaddr_in client_addr;
    int sock_fd;
};

void* thread_proc(void* param);

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    // bind
    struct sockaddr_in server_addr;
    
    // when using INADDR_ANY,  bind PORT to any address.
    // when using specific IP, bind PORT to this.
    server_addr.sin_family        = AF_INET;
    server_addr.sin_port          = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr   = htonl(INADDR_LOOPBACK);

    
    int ret = bind(fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
    if(ret < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    ret = listen(fd, 10);
    if(ret < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }
    struct sockaddr_in client_addr;
    pthread_t thread_id;
    struct server_param* parms;
    socklen_t len = sizeof(struct sockaddr_in);
    for(;;)
    {
        int connect_fd = accept(fd, (struct sockaddr*)&client_addr, &len);
        if(connect_fd < 0)
        {
            sys_err(__FUNCTION__, __LINE__);
            return 0;
        }
        parms = new server_param();
        parms->sock_fd = connect_fd;
        memcpy(&parms->client_addr, &client_addr, sizeof(struct sockaddr_in));
        ret = pthread_create(&thread_id, NULL, thread_proc, parms);
        if(ret != 0)
        {
            sys_err(__FUNCTION__, __LINE__);
            ::close(connect_fd);
        }
    }
}

void* thread_proc(void* param)
{
    struct server_param* parms = (struct server_param* )param;
    unsigned char* buff = new unsigned char[100];
    int ret = 0;
    while(true)
    {
        ret = read(parms->sock_fd, buff, 100);
        if(ret == 1)
        {
            switch (buff[0])
            {
                case '1':
                    {
                        printf("client info:\n");
                        unsigned char* ip = (unsigned char*)(&parms->client_addr.sin_addr.s_addr);
                        printf("\tip   = %u.%u.%u.%u\n", ip[0], ip[1], ip[2], ip[3]);
                        printf("\tport = %d\n", ntohs(parms->client_addr.sin_port));
                    }
                    break;
                case '2':
                    {
                        
                    }
                    break;
                
                default:
                    break;
            }
            if(buff[0] == '3')
            {
                break;
            }
        }
        else if (ret <= 0)
        {
            sys_err(__FUNCTION__, __LINE__);
            break;
        }
        else
        {
            for(int i = 0; i < ret; i++)
                printf("%c", buff[i]);
            printf("\n");
        }
    }
    printf("close\n");
    ::close(parms->sock_fd);
    delete   parms;
    delete[] buff;
    return (void*)9;
}

