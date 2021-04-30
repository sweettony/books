#include <stdio.h>

int main()
{
    int array[10];
    printf("addr = %p\n", array);
    printf("addr = %p\n", &array);
    printf("addr = %p\n", array + 1);
    printf("addr = %p\n", &array + 1);
    printf("size = %d\n", sizeof(array));
    return 0;
}