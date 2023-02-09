#include "file_system.h"

int printMap(void){
    FILE *vdisk;
    sinfo dinfo;
    inode tmp;
    int i;
    int addr;

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

    printf("Disk size: %d\n", dinfo.disk_size);
    printf("Space never used: %d\n", dinfo.free_space);
    printf("Max number of inodes: %d\n", dinfo.all_inodes);
    printf("Number of files: %d\n", dinfo.number_of_files);
    printf("======================\n");
    printf("Typ\tAdres\tRozmiar\tStan\n");

    printf("D_inf\t0\t%ld\t1\n", sizeof(sinfo));
    printf("\n");
    
    for( i=0; i<(dinfo.used_inodes+1); ++i){
        addr = ftell(vdisk);
        if( addr == -1L){
            printf("Errow with ftell\n");
            return -1;
        }
        if( fread(&tmp, sizeof(tmp), 1, vdisk) != 1){
            printf("Error with reading\n");
            return -1;
        }
        if( tmp.fsize == NO_SIZE && tmp.addr_to_data==NO_ADDR && !strcmp(tmp.fname, NO_NAME) ){
            printf("Inode\t%d\t%ld\t0\n", addr, (dinfo.all_inodes-dinfo.used_inodes)*sizeof(inode) );
        }else{
            printf("Inode\t%d\t%ld\t%d\t\n", addr, sizeof(tmp), tmp.is_used );
        }
    }
    if( fseek(vdisk, sizeof(sinfo), SEEK_SET) != 0 ){
        printf("Errow with fseek\n");
        return -1;
    }
    printf("\n");

    for( i=0; i <(dinfo.used_inodes+1); ++i){
        addr = ftell(vdisk);
        if( fread(&tmp, sizeof(tmp), 1, vdisk) != 1){
            printf("Error with reading\n");
            return -1;
        }
        if( tmp.fsize == NO_SIZE && tmp.addr_to_data==NO_ADDR && !strcmp(tmp.fname, NO_NAME) ){
            printf("File\t%d\t%d\t0\n", dinfo.addr_of_next_free_space, dinfo.disk_size-dinfo.addr_of_next_free_space);
        }else{
            printf("File\t%d\t%d\t%d\t\n", tmp.addr_to_data, tmp.fsize, tmp.is_used );
        }

    }    

    return 0;
}