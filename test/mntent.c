#include <stdio.h>
#include <stdlib.h>
#include <mntent.h>

int main(void)
{
  struct mntent *ent;
  FILE *aFile;

  aFile = setmntent("/proc/mounts", "r");
  if (aFile == NULL) {
    perror("setmntent");
    exit(1);
  }
  while (NULL != (ent = getmntent(aFile))) {
    printf("%s %s\n", ent->mnt_fsname, ent->mnt_dir);
  }
  endmntent(aFile);
}