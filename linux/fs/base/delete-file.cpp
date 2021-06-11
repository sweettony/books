#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = ::open("gdb.pdf", O_RDONLY);
    int fd1 = ::open("demo_copy.pdf", O_RDONLY|O_CREAT|O_WRONLY, S_IRWXU);
    if(fd < 0 || fd1 < 0 )
        return 0;
    int ret = 0;
    sleep(6);
    printf("-----sleep over\n");
    char buff[5<<20];
    while (true)
    {
            
        ret = read(fd, buff, (5<<20));
        if(ret <= 0)
        {
            printf("hi\n");
            break;
        }
        write(fd1, buff, ret);
    }
    
    return 0;
}