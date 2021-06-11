#include <errno.h>
#include <string.h>
#include <stdio.h>
int main()
{
    int error = ENETDOWN;
    printf("%s\n", strerror(error));
    return 0;
}