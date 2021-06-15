#include <stdio.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

#include "common_err.h"

#define SERVER_PORT (6060)
#define CLIENT_PORT (6061)

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    
    struct sockaddr_in server_addr;
    server_addr.sin_family        = AF_INET;
    server_addr.sin_port          = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr   = htonl(INADDR_LOOPBACK);

    struct sockaddr_in client_addr;
    client_addr.sin_family        = AF_INET;
    client_addr.sin_port          = htons(CLIENT_PORT);
    client_addr.sin_addr.s_addr   = htonl(INADDR_LOOPBACK);

    
    int ret = bind(fd, (struct sockaddr*)&client_addr, sizeof(struct sockaddr_in));
    if(fd < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    ret = connect(fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
    if(ret < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    unsigned char* buff = new unsigned char[4<<10];
    int wri_ret = 0;
    for(;;)
    {
        ret     = scanf("%s", buff);
        wri_ret = write(fd, buff, strlen((char*)buff));
        printf("scanf read bytes = %d; write bytes = %d\n", ret, wri_ret);
        if(ret == 1 && buff[0] == '2')
        {
            printf("break\n");
            break;
        }
    }
    delete[] buff;
    ::close(fd);
}