#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/hdreg.h>
#include <linux/fs.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "demo1.h"


#if __BYTE_ORDER == __BIG_ENDIAN
#include <asm/byteorder.h>
#ifdef __le16_to_cpu
/* ++roman: 2.1 kernel headers define these function, they're probably more
 * efficient then coding the swaps machine-independently. */
#define CF_LE_W	__le16_to_cpu
#define CF_LE_L	__le32_to_cpu
#define CT_LE_W	__cpu_to_le16
#define CT_LE_L	__cpu_to_le32
#else
#define CF_LE_W(v) ((((v) & 0xff) << 8) | (((v) >> 8) & 0xff))
#define CF_LE_L(v) (((unsigned)(v)>>24) | (((unsigned)(v)>>8)&0xff00) | \
               (((unsigned)(v)<<8)&0xff0000) | ((unsigned)(v)<<24))
#define CT_LE_W(v) CF_LE_W(v)
#define CT_LE_L(v) CF_LE_L(v)
#endif /* defined(__le16_to_cpu) */

#else

#define CF_LE_W(v) (v)
#define CF_LE_L(v) (v)
#define CT_LE_W(v) (v)
#define CT_LE_L(v) (v)

#endif /* __BIG_ENDIAN */

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define FATERR()  printf("%s <%s, %d> err, errno = %s\n", __FILENAME__, __FUNCTION__, __LINE__, strerror(errno));

int init_media(int dev_fd, struct msdos_boot_sector* pbs, int* isfat32)
{
  struct hd_geometry geometry;
  int ret = ioctl(dev_fd, HDIO_GETGEO, &geometry);
  if(ret < 0)
  {
    FATERR()
    return -1;
  }
    
  if (geometry.sectors == 0 || geometry.heads == 0)
  {
    FATERR()
    return -1;
  }
    

  pbs->secs_track = CT_LE_W(geometry.sectors); /* Set up the geometry information */
  pbs->heads      = CT_LE_W(geometry.heads);
  
  pbs->media          = (char)0xf8;            /* Set up the media descriptor for a hard drive */
  pbs->dir_entries[0] = (char)0;               /* Default to 512 entries */
  pbs->dir_entries[1] = (char)2;
  
  __uint64_t size = 0;
  ret = ioctl(dev_fd, BLKGETSIZE64, &size);
  if(ret != 0) 
  {
    FATERR()
    return -1;
  }
  __int32_t sector_size = 0;
  ret = ioctl(dev_fd, BLKSSZGET, &sector_size);
  pbs->sector_size = sector_size;

  if(ret != 0)
  {
    FATERR()
    return -1;
  }
  if ( size > 1064960)
  {
    /* For FAT32, try to do the same as M$'s format command
	   * (see http://www.win.tue.nl/~aeb/linux/fs/fat/fatgen103.pdf p. 20):
	   * fs size <= 260M: 0.5k clusters
	   * fs size <=   8G: 4k clusters
	   * fs size <=  16G: 8k clusters
	   * fs size >   16G: 16k clusters
	   */
    __uint64_t sz_mb = (size >> 20);
    printf("sz_mb = %llu\n", sz_mb);
    __uint8_t sec_per_cluster = sz_mb > (16 < 20) ? 32 : 
                                sz_mb > (8 < 10)  ? 16 : 
                                sz_mb > 260       ? 8  : 1;
    pbs->cluster_size = sec_per_cluster * 512 < sector_size ? 1 : sec_per_cluster * 512 / sector_size;
  }
  else
  {
      /* FAT12 and FAT16: start at 4 sectors per cluster */
      pbs->cluster_size = (char)4;
      *isfat32 = 0;
  }
  printf("total = %llu, sector = %d, cluster = %d\n", size, sector_size, pbs->cluster_size);
  
  return 0;
}

#define BOOT_JUMP "\xEB\x3C\x90"
#define SYSTEM_ID "QV-FS\x20\x20\x20" /** padded with space 0x20**/

static int init_BIOS_params_blk(struct msdos_boot_sector* bs, int isfat32)
{
  
}
static int init_bs(struct msdos_boot_sector* bs, int isfat32)
{
  //jump code
  memcpy(bs->boot_jump, BOOT_JUMP, 3);
  //oem
  memcpy(bs->system_id, "QV-FAT", 8);
  //init BIOS parameter block
  init_BIOS_params_blk();
}

typedef struct tag_media_info
{
  __uint16_t sector_bytes;
  __uint8_t  cluster_sectors;
  __uint8_t  isfat32;
  __uint8_t  media;

} MEDIA_INFO;

int main(int argc, char* argv[])
{
  if(argc != 2)
    return 0;
  struct msdos_boot_sector bs;
  int isfat32 = 1;
  printf("devname = %s\n", argv[1]);
  int fd = open(argv[1], O_RDWR|O_EXCL|O_SYNC);
  printf("fd = %d\n", fd);
  init_media(fd, &bs, &isfat32);
  init_bs(&bs, isfat32);
  return 0;
}