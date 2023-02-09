#include "file_system.h"
int ls(void){
    FILE *vdisk;
    sinfo dinfo;
    inode tmp;
    int i;

    vdisk = fopen(disk_name, "rb");
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
        if( fread(&tmp, sizeof(inode), 1, vdisk) !=1 ){
            printf("Error with inode read\n");
            return -1;
        }
        if( strcmp(tmp.fname, NO_NAME) ){
            printf("%s\t", tmp.fname);
        }
    }
    printf("\n");


    if( fclose(vdisk) != 0 ){
        printf("Error with closig disk\n");
        return -1;
    }

    return 0;
}