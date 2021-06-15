#ifndef _ERR_H_
#define _ERR_H_
#include <errno.h>
#include <stdio.h>
#include <string.h>
inline void sys_err(const char* funcname, int line)
{
    printf("[%s, %d] : errno = %d, err = %s\n", funcname, line, errno, strerror(errno));
    return;
}
#endif //_ERR_H_