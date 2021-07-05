/**
 * advisory record locking
 * 
 * 
 * unlock:
 *  As well as being removed by an explicit F_UNLCK, record locks are 
 *  automatically released when the process terminates.
 * fork and execve
 *  Record locks are not inherited by a child created via fork, but are preserved across an execve
 * for read lock or write lock
 *  read lock  => must have open with reading 
 *  write lock => must have open with writing
 * when pid is set?
 *  
 * */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>

int file_lock_fork();
int fork_file_lock();

int main()
{
    file_lock_fork();
    return 0;
}

int file_lock_fork()
{
    int fd = open("./cc.txt", O_RDWR|O_TRUNC);
    if(fd < 0)
    {
        printf("fd = %d, error = %d\n", fd, errno);        
        return 0;
    }

    struct flock process_file_lock;
    process_file_lock.l_whence = SEEK_SET;
    process_file_lock.l_start  = 0;
    process_file_lock.l_len    = 0;
    process_file_lock.l_type   = F_WRLCK;
    int ret;

    
    printf("---------------------lock\n");
    ret = fcntl(fd, F_SETLK, &process_file_lock);
    if(ret != 0)
    {
        printf("fd = %d, error = %d\n", fd, errno);        
        return 0;
    }    
    ret = fork();
    
    if(ret == 0)
    {
        struct flock file_lock;
        file_lock.l_whence = SEEK_SET;
        file_lock.l_start  = 0;
        file_lock.l_len    = 0;
        file_lock.l_type   = F_RDLCK;
        ret = fcntl(fd, F_GETLK, &file_lock);
        printf("-%d-%d-%d\n", file_lock.l_type, file_lock.l_pid, file_lock.l_whence);
    }
    else if (ret > 0)
    {
        sleep(5);
        struct flock file_lock;
        file_lock.l_whence = SEEK_SET;
        file_lock.l_start  = 0;
        file_lock.l_len    = 0;
        file_lock.l_type   = F_RDLCK;
        ret = fcntl(fd, F_GETLK, &file_lock);
        printf("-%d-%d-%d\n", file_lock.l_type, file_lock.l_pid, file_lock.l_whence);
        do
        {
            process_file_lock.l_type = F_UNLCK;
            ret = fcntl(fd, F_SETLK, &process_file_lock);        
            sleep(1);
        }while(0 != ret);
        printf("---------------------unlock\n");
    }
    else
    {

    }
    return 0;  
}
int fork_file_lock()
{
    int fd = open("./cc.txt", O_RDWR|O_TRUNC);
    if(fd < 0)
    {
        printf("fd = %d, error = %d\n", fd, errno);        
        return 0;
    }
    struct flock process_file_lock;
    process_file_lock.l_whence = SEEK_SET;
    process_file_lock.l_start  = 15;
    process_file_lock.l_len    = 20;
    process_file_lock.l_type   = F_WRLCK;
    int ret;
    ret = fork();
    if(ret == 0)
    {
        sleep(100);
        printf("---------------------lock\n");
        ret = fcntl(fd, F_SETLK, &process_file_lock);
        if(ret != 0)
        {
            printf("fd = %d, error = %d\n", fd, errno);        
            return 0;
        }
            sleep(100);
        do
        {
            process_file_lock.l_type = F_UNLCK;
            ret = fcntl(fd, F_SETLK, &process_file_lock);        
            sleep(1);
        }while(0 != ret);
        printf("---------------------unlock\n");
    }
    else if (ret > 0)
    {
        sleep(100);
        printf("---------------------lock\n");
        ret = fcntl(fd, F_SETLK, &process_file_lock);
        if(ret != 0)
        {
            printf("fd = %d, error = %d\n", fd, errno);        
            return 0;
        }
            sleep(100);
        do
        {
            process_file_lock.l_type = F_UNLCK;
            ret = fcntl(fd, F_SETLK, &process_file_lock);        
            sleep(1);
        }while(0 != ret);
        printf("---------------------unlock\n");
    }
    else
    {

    }
    return 0;
}
