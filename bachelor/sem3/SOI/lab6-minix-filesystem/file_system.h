#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

#include <stdio.h> /* FILE*/
#include <string.h> /* strcpy etc*/
#include <unistd.h> /* unlink */
#include <stdlib.h> /* atoi*/

#define MAX_DISK_SIZE 100
#define MIN_DISK_SIZE 2

#define BUFFER_SIZE 10*1024
#define MAX_FILE_NAME_LEN 15
static const char* disk_name = "disk";

#define NO_SIZE -1
#define NO_ADDR -1
static const char* NO_NAME = "\0";

typedef struct inode{
/*    int index; */
    int fsize;
    int addr_to_data;
    int is_used;
    char fname[MAX_FILE_NAME_LEN];
} inode;

typedef struct superblock_info{
    int disk_size;
    int free_space;/* free space at the end of the file*/
    int number_of_files;
    int all_inodes;
    int used_inodes;/* used at least once, if they are freed, they are still used*/
    int addr_of_next_free_inode;
    int addr_of_next_free_space;
} sinfo;

int createVD(int);
int copyTo(char*);
int copyFrom(char*);
int ls(void);
int deleteFile(char*);
int deleteVD(void);
int printMap(void);

#endif /*_FILE_SYSTEM_H_*/
