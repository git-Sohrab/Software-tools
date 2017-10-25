#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "dos2sd.h"

/**
* fileInfo.c - This is my solution to the third lab of eecs2031 ....
* The code below consists of one function; listFiles() which lists the files in sectors of a disk.
* The function loops through each sector and after finding a file, it lists it's name, occupied 
* sub-sectors and file size.
* 
*
* Editor/Debugger: Sohrab Oryakhel
* Student number: 214302145
* Date: 09/25/2017
*
**/



static void listFiles(FILE *fd, struct ATRSSDISK *disk, char fName[])
{
  int sector, entry, i, j, count, start, baseFileNumber;
  char name[13], ext[4];
  int exists = 1;

  baseFileNumber = 0;
  for(sector = 361; sector <= 368; sector++) {
    for(entry = 0; entry < ATR_SECTOR_SIZE; entry += 16) {
      if(disk -> sector[sector - 1][entry] == 0x042) {
        for(i = 0; i < 8; i++) {
          name[i] = disk -> sector[sector - 1][entry + 5 + i];
        }
        name[8] = '.';
        for(i = 0; i < 3; i++) 
          ext[i] = disk -> sector[sector - 1][entry + 13 + i];
        ext[3] = '\0';
	      for (i = 9, j = 0; i < 13; i++, j++) 
	        name[i] = ext[j];
        count = disk->sector[sector-1][entry+1]|disk->sector[sector-1][entry+2]<<8;
        start = disk->sector[sector-1][entry+3]|disk->sector[sector-1][entry+4]<<8;
        for (j = 0; fName[j] != '\0' && name[j] != '\0'; j++) {
	        exists = !(fName[j] != name[j]);
          if (!exists) {
            break;
          }
        }
        if (exists > 0){
          fprintf(fd, "%s sector List ", fName);
	        for (i = start; i < start + count; i++) { 
		        printf("%d ", i);
	        }	
	        printf("Total file size %d\n", (count * 128));
	      }
      }
      baseFileNumber++;
    }
  }
}

int main(int argc, char *argv[])
{
  struct ATRSSDISK *disk;

  if(argc != 3) {
    fprintf(stderr,"usage: %s disk file\n", argv[0]);
    exit(1);
  }
  if((disk = readDisk(argv[1])) == (struct ATRSSDISK *)NULL) {
    fprintf(stderr,"Unable to read disk %s\n", argv[1]);
    exit(1);
  }
  else {
    listFiles(stdout, disk, argv[2]);
    freeDisk(disk);
    return 0;
  }
}
