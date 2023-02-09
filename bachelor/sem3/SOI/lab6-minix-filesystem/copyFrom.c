#include "file_system.h"

int copyFrom(char* file_name){
    FILE *vdisk, *file;
    char buffer[BUFFER_SIZE];
    sinfo dinfo;
    inode tmp, file_inode;
    int i;
    int found_flag=0;

    printf("Coping %s to Minix\n", file_name);

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
        if( fread(&tmp, sizeof(inode), 1, vdisk) != 1 ){
            printf("Error with fread\n");
            return -1;
        }

        if( strcmp(file_name, tmp.fname) == 0){
            file_inode = tmp;
            found_flag = 1;
            break;/* found, no need to go further*/
        }
    }

    if(!found_flag){
        printf("Error: no such file\n");
        return -1;
    }
    file = fopen(file_name, "w");
    if( file == NULL ){
        printf("Error: no such file\n");
        return -1;
    }

    /*COPING DATA*/
    rewind(vdisk);
    if( fseek(vdisk, file_inode.addr_to_data, SEEK_SET) != 0){
        printf("Error with fseek\n");
        return -1;
    }
    if( fread(buffer, sizeof(char), file_inode.fsize, vdisk) < 0){
        printf("Error with reading data\n");
        return -1;
    }
    /*printf("buffer: %s\n", buffer);*/
    if( fwrite(buffer, sizeof(char), file_inode.fsize, file) < 0){
        printf("Error with writig data\n");
        return -1;
    }

    /*END OF WORK*/
    if( fclose(file) != 0 ){
        printf("Error with closig disk\n");
        return -1;
    }

    if( fclose(vdisk) != 0 ){
        printf("Error with closig disk\n");
        return -1;
    }

    return 0;

}