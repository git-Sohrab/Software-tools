#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dos2sd.h"


/**
 *
 *
 * Editor/Debugger: Sohrab Oryakhel
 * Student Number: 214302145
 * Date: 2017/09/27
 *
 *
 *
 *
 * This file consists of a function that extracts the content of certain files in
 * a disk image. It consists of two functions, main() and extract(). extract()
 * takes a file, a disk image and a file name (fName) as input. It looks 
 * for fName in the disk image and if it exists, extract() will extract all of 
 * its content to a separate file and save it to local disk.
 *
 **/

static void extract(FILE *fd, struct ATRSSDISK *disk, char fName[])
{
  int sector, entry, i, j, count, start, baseFileNumber;
  char name[13], ext[4];
  int exists = 1;                                     /*File exists, if exists = 1*/
  FILE *fp;

  sector = 361;                                       /*List of files is only in sector 361*/
  baseFileNumber = 0;

  for(entry = 0; entry < ATR_SECTOR_SIZE; entry += 16) {
    if(disk -> sector[sector - 1][entry] == 0x042) {
      for(i = 0; i < 8; i++) 
        name[i] = disk -> sector[sector - 1][entry + 5 + i];    /*Initialize file name: name*/
      name[8] = '.';                                            /*Add '.' for file extention*/
      for(i = 0; i < 3; i++) 
        ext[i] = disk -> sector[sector - 1][entry + 13 + i];    /*Initialize file extension: ext*/ 
      ext[3] = '\0';                                            
	    for (i = 9; i < 13; i++)                                  /*Combine file name in one variable for check loop*/
      	name[i] = ext[i - 9];
      count = disk -> sector[sector - 1][entry + 1] | disk -> sector[sector - 1][entry + 2] << 8;
      start = disk -> sector[sector - 1][entry + 3] | disk -> sector[sector - 1][entry + 4] << 8;

      for (i = 0; fName[i] != '\0' && name[i] != '\0'; i++) {   /*Check if each char of input matches each char of file name*/
	      exists = !(fName[i] != name[i]);                        /*If at any point in the check loop, that characters dont match, exists = 0*/
        if (!exists) {
          break;
        }
      }
      for (i = 9; i < 12; i++) {                                /*Remove the ext chars in name because they are capitalized. Replace with NULL*/
        name[i] = 0x00;
      }
      if (exists > 0) {
        if (name[0] == 'S') {                                   /*If the file is SAMPLE  .JPG*/
          fp = fopen(strcat(name, "JPG"), "w");
        }
        else {
          fp = fopen(strcat(name, ".txt"), "w");                /*If file is any of the text files: HELLO, WALRUS, JAB*/
        }
        for (i = start; i < count + start; i++) {
          for (j = 0; j < ATR_SECTOR_SIZE - 3; j++) {
            fprintf(fp, "%c", disk -> sector[i - 1][j]);
          }
        }
        fputc('\n', fp);
        fclose(fp);
      }
    }
    baseFileNumber++;
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
