#include "file_system.h"

int deleteFile(char* file_name){
    FILE *vdisk;
    sinfo dinfo;
    inode tmp;
    int i;
    int found_flag=0;
    int addr_inode;

    vdisk = fopen(disk_name, "rb+");
    if( vdisk == NULL ){
        printf("Error with opening disk\n");
        return -1;
    }

    if( fseek(vdisk, 0, SEEK_SET) != 0 ){
        printf("Error with fseek1");
        return -1;
    }
    if( fread(&dinfo, sizeof(sinfo), 1, vdisk) !=1 ){
        printf("Error with superblock\n");
        return -1;
    }

    for( i=0; i<dinfo.used_inodes; ++i){
        if( fread(&tmp, sizeof(inode), 1 , vdisk) != 1){
            printf("Error with inodes read\n");
            return -1;
        }
        if( strcmp(file_name, tmp.fname) == 0 ){
            addr_inode = ftell(vdisk)-sizeof(inode);
            found_flag=1;
            break;/*found*/
        }
    }

    if( !found_flag ){
        printf("Error:no such file\n");
        return -1;
    }

    strcpy(tmp.fname, "\0");
    tmp.is_used = 0;
    if( fseek(vdisk, tmp.addr_to_data, SEEK_SET) != 0 ){
        printf("Error with fseek\n");
        return -1;
    }
    for(i=0; i<tmp.fsize; ++i){
        if( fwrite("x", sizeof(char), 1, vdisk) != 1){
            printf("Error with deleting data\n");
            return -1;
        }
    }

    if( fseek(vdisk, addr_inode, SEEK_SET) != 0 ){
        printf("Error with fseek\n");
        return -1;
    }
    if( fwrite(&tmp, sizeof(inode), 1, vdisk) !=1 ){
        printf("Error with writing inode\n");
        return -1;
    }


    if( fclose(vdisk) != 0 ){
        printf("Error with closig disk\n");
        return -1;
    }
    return 0;
}