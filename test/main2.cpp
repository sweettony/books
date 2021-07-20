#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define PATH "/dev/mmcblk0"

inline void sys_err(const char* funcname, int line)
{
    printf("[%s, %d] : errno = %d, err = %s\n", funcname, line, errno, strerror(errno));
    return;
}

int main()
{
    int ret = 0;
    while(1)
    {
        ret = ::access(PATH, F_OK);
        if(ret < 0)
        {
            sys_err(__FUNCTION__, __LINE__);
        }
        else
        {
            printf("OK\n");
        }
        sleep(1);
    }
    return 0;
}