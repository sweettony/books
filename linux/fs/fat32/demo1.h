#ifndef DEMO1_H_
#define DEMO1_H_
#include <sys/types.h>

/* __attribute__ ((packed)) is used on all structures to make gcc ignore any
 * alignments */
#define  BOOTCODE_SIZE 448
#define  BOOTCODE_FAT32_SIZE 420
struct msdos_volume_info {
  __u8		drive_number;	/* BIOS drive number */
  __u8		RESERVED;	/* Unused */
  __u8		ext_boot_sign;	/* 0x29 if fields below exist (DOS 3.3+) */
  __u8		volume_id[4];	/* Volume ID number */
  __u8		volume_label[11];/* Volume label */
  __u8		fs_type[8];	/* Typically FAT12 or FAT16 */
} __attribute__ ((packed));

struct msdos_boot_sector
{
  __u8	        boot_jump[3];	/* Boot strap short or near jump */
  __u8          system_id[8];	/* Name - can be used to special case partition manager volumes */
  __u8          sector_size[2];	/* bytes per logical sector */
  __u8          cluster_size;	/* sectors/cluster */
  __u16         reserved;	/* reserved sectors */
  __u8          fats;		/* number of FATs */
  __u8          dir_entries[2];	/* root directory entries */
  __u8          sectors[2];	/* number of sectors */
  __u8          media;		/* media code (unused) */
  __u16         fat_length;	/* sectors/FAT */
  __u16         secs_track;	/* sectors per track */
  __u16         heads;		/* number of heads */
  __u32         hidden;		/* hidden sectors (unused) */
  __u32         total_sect;	/* number of sectors (if sectors == 0) */
  union {
    struct {
      struct msdos_volume_info vi;
      __u8	boot_code[BOOTCODE_SIZE];
    } __attribute__ ((packed)) _oldfat;
    struct {
      __u32	fat32_length;	/* sectors/FAT */
      __u16	flags;		/* bit 8: fat mirroring, low 4: active fat */
      __u8	version[2];	/* major, minor filesystem version */
      __u32	root_cluster;	/* first cluster in root directory */
      __u16	info_sector;	/* filesystem info sector */
      __u16	backup_boot;	/* backup boot sector */
      __u16	reserved2[6];	/* Unused */
      struct msdos_volume_info vi;
      __u8	boot_code[BOOTCODE_FAT32_SIZE];
    } __attribute__ ((packed)) _fat32;
  } __attribute__ ((packed)) fstype;
  __u16		boot_sign;
} __attribute__ ((packed));
#define fat32	fstype._fat32
#define oldfat	fstype._oldfat

#endif //DEMO1_H_