#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <common_err.h>

int main(int argc, char* arg[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    if(argc != 2)
    {
        printf("please input server port!!!\n");
        return 0;
    }
    in_port_t port = atoi(arg[1]);
    struct sockaddr_in server_addr;
    server_addr.sin_family        = AF_INET;
    server_addr.sin_port          = htons(port);
    server_addr.sin_addr.s_addr   = htonl(INADDR_LOOPBACK);

    int ret = connect(fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
    if(ret < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    close(fd);
    return 0;
}