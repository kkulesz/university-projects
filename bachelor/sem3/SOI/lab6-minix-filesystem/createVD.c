#include "file_system.h"

int createVD(int size_in_kB){
    FILE* vdisk;
    sinfo dinfo;
    inode tmp_inode;
    int size, info_space, data_space;
    int num_of_inodes;
    int i;

    if( size_in_kB < MIN_DISK_SIZE || size_in_kB > MAX_DISK_SIZE){
        printf("Invalid size of disk\n");
        return -1;
    }
    
    size = 1024*size_in_kB;
    info_space = 128*size_in_kB;/* 1/8 of all space*/
    data_space = size-info_space;

    num_of_inodes = (info_space-sizeof(dinfo))/sizeof(inode);

    vdisk = fopen(disk_name, "wb+");
    if( vdisk == NULL ) {
        printf("Error with creating disk\n");
        return -1;
    }
    if( fseek(vdisk, size-1, SEEK_SET) != 0 ){
        printf("Error with setting size of disk\n");
        return -1;
    }

    dinfo.disk_size = size;
    dinfo.free_space = data_space;
    dinfo.all_inodes = num_of_inodes;
    dinfo.used_inodes = 0;
    dinfo.number_of_files = 0;
    dinfo.addr_of_next_free_inode = sizeof(dinfo);
    dinfo.addr_of_next_free_space = info_space;

    /*  writing infos */
    if( fseek(vdisk, 0, SEEK_SET) != 0 ){
        printf("Error with setting size of disk\n");
        return -1;
    }

    if( fwrite(&dinfo, sizeof(dinfo), 1, vdisk ) != 1 ){
        printf("Error with writing to disk");
        return -1;
    }

    tmp_inode.addr_to_data=NO_ADDR;
    tmp_inode.fsize=NO_SIZE;
    tmp_inode.is_used=0;
    strcpy( tmp_inode.fname, NO_NAME );

    for( i=0; i<num_of_inodes; ++i ){
        /*tmp_inode.index = i;*/
        if( fwrite(&tmp_inode, sizeof(inode), 1, vdisk) != 1 ){
            printf("Error with writing inodes\n");
            return -1;
        }
    }
    if( fclose(vdisk) != 0 ){
        printf("Error with closig disk\n");
        return -1;
    }
    return 0;
}