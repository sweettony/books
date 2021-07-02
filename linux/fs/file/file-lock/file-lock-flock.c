/** 此Demo测试函数flock
 *  traditional ("process-associated") UNIX record locks, as standardized by POSIX
 *  flock 是一个针对进程(具体一点是针对 open file table)的读写锁，
 *  在线程中是不生效, 如果线程要生效, 需要open两次。
 *  具体描述：
 *  A call to flock() may block if an incompatible lock is held by another process.  To make  a
    nonblocking request, include LOCK_NB (by ORing) with any of the above operations.

    A single file may not simultaneously have both shared and exclusive locks.

    Locks  created  by  flock()  are associated with an open file table entry.  This means that
    duplicate file descriptors (created by, for example, fork(2) or dup(2)) refer to  the  same
    lock,  and  this lock may be modified or released using any of these descriptors.  Further‐
    more, the lock is released either by an explicit LOCK_UN operation on any of  these  dupli‐
    cate descriptors, or when all such descriptors have been closed.

    If  a  process  uses  open(2)  (or similar) to obtain more than one descriptor for the same
    file, these descriptors are treated independently by flock().  An attempt to lock the  file
    using  one  of  these file descriptors may be denied by a lock that the calling process has
    already placed via another descriptor.

    A process may hold only one type of lock (shared  or  exclusive)  on  a  file.   Subsequent
    flock() calls on an already locked file will convert an existing lock to the new lock mode.

    Locks created by flock() are preserved across an execve(2).

    A shared or exclusive lock can be placed on a file regardless of the mode in which the file
    was opened.
**/
#include <sys/file.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* thread1(void* param)
{
    int fd = (int)param;
    const char* buff = "12345678944444444444444444444444444444444444";
    int ret;
    printf("fd = %d\n", fd);
    while(1)
    {
        ret = flock(fd, LOCK_EX|LOCK_NB);
        if(ret != 0)
        {
            EWOULDBLOCK
            printf("ret1 = %d, error = %d, %s\n", ret, errno, strerror(errno));
            sleep(1);
            continue;
        }
        printf("thread 1 is in blocking\n");
        sleep(6);
        write(fd, buff, strlen(buff));
        printf("thread 1 is not in blocking\n");
        flock(fd, LOCK_UN);
        sleep(1);
    }
    
}
void* thread2(void* param)
{
    int fd = (int)param;
    const char* buff = "12345678944444444444444444444444444444444444";
    int ret;
    printf("fd = %d\n", fd);
    while(1)
    {
        ret = flock(fd, LOCK_EX|LOCK_NB);
        if(ret != 0)
        {
            printf("ret2 = %d, error = %d, %s\n", ret, errno, strerror(errno));
            sleep(3);
            continue;
        }
        printf("thread 2 is in blocking\n");
        sleep(6);
        write(fd, buff, strlen(buff));
        printf("thread 2 is not in blocking\n");
        flock(fd, LOCK_UN);
        sleep(1);
    }
}
int main()
{
    int fd1 = open("./cc.txt", O_RDWR|O_CREAT);
    if(fd1 < 0)
    {
        printf("fd1 = %d, error = %d\n", fd1, errno);        
        return 0;
    }

    int fd2 = open("./cc.txt", O_RDWR|O_CREAT);
    if(fd2 < 0)
    {
        printf("fd2 = %d, error = %d\n", fd2, errno);
        return 0;
    }

    pthread_t th1, th2;
    pthread_create(&th1, NULL, &thread1, (void*)fd1);
    pthread_create(&th2, NULL, &thread2, (void*)fd1);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}