#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <common_err.h>

#define SERVER_PORT 6352

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
    struct server_param* parms;
    socklen_t len = sizeof(struct sockaddr_in);

    int connect_fd = accept(fd, (struct sockaddr*)&client_addr, &len);
    if(connect_fd < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    //getsockname
    struct sockaddr_storage generic_addr;
    len = sizeof(struct sockaddr_storage);
    ret = getsockname(connect_fd, (struct sockaddr*)&generic_addr, &len);
    if(ret != 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    if( generic_addr.ss_family == AF_INET)
    {
        struct sockaddr_in* inet = (struct sockaddr_in*)&generic_addr;
        char str_inet[INET_ADDRSTRLEN];
        struct in_addr* pin_addr = &inet->sin_addr;
        inet_ntop(AF_INET, pin_addr, str_inet, INET_ADDRSTRLEN);
        if(ret != 0)
        {
            sys_err(__FUNCTION__, __LINE__);
            return 0;
        }
        printf("inet local = {%s, %u}\n", str_inet, ntohs(inet->sin_port));       
    }
    ret = getpeername(connect_fd, (struct sockaddr*)&generic_addr, &len);
    if(ret != 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;
    }

    if( generic_addr.ss_family == AF_INET)
    {
        struct sockaddr_in* inet = (struct sockaddr_in*)&generic_addr;
        char str_inet[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &inet->sin_addr, str_inet, INET_ADDRSTRLEN);
        if(ret != 0)
        {
            sys_err(__FUNCTION__, __LINE__);
            return 0;
        }
        printf("inet peer = {%s, %u}\n", str_inet, ntohs(inet->sin_port));       
    }
    return 0;
}