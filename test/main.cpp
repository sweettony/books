#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define PATH "/var/fat32/mytext.txt"

inline void sys_err(const char* funcname, int line)
{
    printf("[%s, %d] : errno = %d, err = %s\n", funcname, line, errno, strerror(errno));
    return;
}

#define check_err(ret) \
    if(ret < 0) \
    { \
        sys_err(__FUNCTION__, __LINE__); \
    }
int linux_write()
{
    int fd = ::open(PATH, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
    if(fd < 0)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;        
    }
    //const char* text = "i love you";
    char* text = (char*)malloc((20<<20));
    int ret = 0;
    time_t sec;
    time_t sec1;
    struct timespec time_start;
    struct timespec time_end;
    unsigned long long int diff;
    unsigned long long int start;
    unsigned long long int end;
    while(1)
    {
        ret = clock_gettime(CLOCK_REALTIME, &time_start);
        check_err(ret);
        //ret = ::write(fd, text, strlen(text));
        printf("s = %llu\n", start);
        ret = ::write(fd, text, (20<<20));
        check_err(ret);
        printf("ret = %d\n", ret);
        ret = clock_gettime(CLOCK_REALTIME, &time_end);
        check_err(ret);
        start = time_start.tv_sec * 1000 + time_start.tv_nsec / 1000000;
        end   = time_end.tv_sec * 1000 + time_end.tv_nsec /1000000;
        diff  = end - start;
        printf("e = %llu\n", end);
        printf("-----------------------usage = %llu\n", diff);
        sleep(1);
    }
    return 0;
}
int standard_fwrite()
{
    FILE* fd = ::fopen(PATH, "w+");
    if(fd == NULL)
    {
        sys_err(__FUNCTION__, __LINE__);
        return 0;        
    }
    //const char* text = "i love you";
    char* text = (char*)malloc((20<<20));
    int ret = 0;
    time_t sec;
    time_t sec1;
    struct timespec time_start;
    struct timespec time_end;
    unsigned long long int diff;
    unsigned long long int start;
    unsigned long long int end;
    char* buff = (char*)malloc((10<<20));
    ret = setvbuf(fd, buff, _IOFBF, (10<<10));
    printf("cc\n");
    check_err(ret);
    while(1)
    {
        ret = clock_gettime(CLOCK_REALTIME, &time_start);
        check_err(ret);
        printf("s = %llu\n", start);
        //ret = ::write(fd, text, (20<<20));
        ret = ::fwrite(text, 1, (20<<20), fd);
        printf("ret = %d\n", ret);
        ret = ferror(fd);
        printf("error ret = %d\n", ret);
        //printf("errno = %d[]")
        check_err(ret);
        printf("ret = %d\n", ret);
        ret = clock_gettime(CLOCK_REALTIME, &time_end);
        check_err(ret);
        start = time_start.tv_sec * 1000 + time_start.tv_nsec / 1000000;
        end   = time_end.tv_sec * 1000 + time_end.tv_nsec /1000000;
        diff  = end - start;
        printf("e = %llu\n", end);
        printf("-----------------------usage = %llu\n", diff);
        sleep(1);
    }
    return 0;
}
int main()
{
    //linux_write();
    standard_fwrite();
    return 0;
}