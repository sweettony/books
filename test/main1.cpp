#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/vfs.h> 

#define PATH "/var/fat32/mytext.txt"

typedef unsigned long long int uint64;

inline void sys_err(const char* funcname, int line)
{
    printf("[%s, %d] : errno = %d, err = %s\n", funcname, line, errno, strerror(errno));
    return;
}

int main()
{
    int fd = ::open(PATH, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
    if(fd < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;        
    }
    const char* text = "i love you";
    int ret = 0;
    uint64 total, free;
    while(1)
    {
        struct statfs stvfs;
        ret = statfs("/var/fat32", &stvfs);
        if(ret < 0)
        {
            sys_err(__FUNCTION__, __LINE__);
            return 0;        
        }
        total = (uint64)(stvfs.f_bsize/1024) * (uint64)(stvfs.f_blocks/1024);
        free  =  (uint64)(stvfs.f_bfree/1024) * (uint64)(stvfs.f_bsize/1024);
        printf("sd=========> total = %llu; free = %llu\n", total, free);
        sleep(1);
    }
    return 0;
}