#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    if( argc != 2 )
    {
        printf("------please input file path!!!\n");    
        return 0;
    }

    printf("input file = %s\n", argv[1]);

    struct stat stfile;
    int ret = stat(argv[1], &stfile);
    if( ret != 0)
    {
        printf("errno = %d\n", errno);
    }

    printf("dev id        = %x\n", stfile.st_dev);
    printf("inode number  = %d\n", stfile.st_ino);
    printf("mode          = %d\n", stfile.st_mode);
    printf("link          = %d\n", stfile.st_nlink);
    printf("st_uid        = %d\n", stfile.st_uid);
    printf("st_gid        = %d\n", stfile.st_gid);
    printf("st_device id  = %x\n", stfile.st_rdev);
    printf("size          = %ld\n", stfile.st_size);
    printf("blk_size      = %ld\n", stfile.st_blksize);
    printf("blk_count     = %ld\n", stfile.st_blocks);
    printf("atime         = %ld\n", stfile.st_atime);
    printf("mtime         = %ld\n", stfile.st_mtime);
    printf("ctime         = %ld\n", stfile.st_ctime);
    return 0;
}