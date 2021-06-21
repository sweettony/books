#include <stdio.h>
#include <strings.h>
struct A
{
    char a[8];
    int c;
};

struct B
{
    int a;
    struct A b; //align struct A member of the max size.
};

int main()
{
    printf("size of struct = %d\n", sizeof(struct B));
    return 0;
}