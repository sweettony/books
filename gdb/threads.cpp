#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int cc()
{
    int a = 4, b =4;
    return (a + b);
}
void * threadproc(void * arg)
{
    int sum = 0;
    while(true)
    {
        sleep(3);
        sum = 0;
        for(int i = 0; i < 100; i++)
        {
            sum +=i;
            cc();
        }
    }
    return NULL;
}

int main()
{
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id, NULL, &threadproc, NULL);
    if(ret < 0)
    {
        std::cout << "pthread_create  failed" << std::endl;
    }
    int sum;
    while (true)
    {
        sleep(3);
        sum = 0;
        for(int i = 0; i < 100; i++)
        {
            sum +=i;
            cc();
        }
    }
    
    pthread_join(pthread_id, NULL);
    return 0;
}
