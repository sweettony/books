#include <stdio.h>
#include <unistd.h>

int main()
{
    char buff[1024];
    snprintf(buff, 10, "%d", 010);
    printf("%s\n", buff);

    FILE* p = fopen("./print.txt", "a+");
    fprintf(p, "%d    hi baby    you know\n", 1201);
    fclose(p);
    while (1)
    {
        sleep(10);
    }
    
    return 0;
}