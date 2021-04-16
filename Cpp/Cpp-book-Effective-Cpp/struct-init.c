#include <stdio.h>

struct TEST
{
    int a;
};

static struct TEST a = 
{
    .a = 3
};
int main()
{
    printf("a = %d\n", a.a);
    return 0;
}
