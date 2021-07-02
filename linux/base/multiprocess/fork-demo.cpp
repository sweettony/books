/** 学习fork函数 
 * fork()
 *  通过复制 calling process 来产生新的进程
 *  新进程和 calling process 完全一样。
 *  但是有几点是不同的
 *  POSIX.1-2001
 *  1. 父类和子类的进程ID不同
 *  2. does not inherit parent's memory locks( mlock mulock)
 *     为进程锁定一块物理内存，不允许交换。
 *  3. 子类的 set of pending signal 被初始化为空
 *  4. 子类不继承 record locks; flock会继承
 *  5. 子类不继承 timers
 *  6. 
 * */

#include <unistd.h>
#include <stdio.h>
int main()
{
    pid_t pid = fork();
    if(pid  == 0)
    {
        /** child process **/
        while(true)
        {
            printf("<pid = %d>i am child, my fater pid is %d\n", getpid(), getppid());
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        /** parent process **/
        while(true)
        {
            printf("<pid = %d>i am father\n", getpid());
            sleep(1);
        }

    }
    else
    {


    }
    return 0;
}   