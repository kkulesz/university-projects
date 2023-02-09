#include "file_system.h"

/*
extern const char* disk_name;
extern const char* NO_NAME;
*/
int copyTo(char* file_name){
    FILE *vdisk, *file_to_copy;
    sinfo dinfo;
    inode tmp, file_inode;
    int size_of_file;
    char buffer[BUFFER_SIZE];
    int i;
    int adr_inode;

    printf("Coping %s from Minix\n", file_name);


    /*OPENNING*/
    file_to_copy = fopen(file_name, "r");
    if( file_to_copy == NULL ){
        printf("Error: no such file\n");
        return -1;
    }
    vdisk = fopen(disk_name, "rb+");
    if( vdisk == NULL ){
        printf("Error with opening disk\n");
        return -1;
    }

    /*READING INFOS*/

    if( fseek(vdisk, 0, SEEK_SET) != 0 ){
        printf("Error with fseek1\n");
        return -1;
    }
    if( fread(&dinfo, sizeof(sinfo), 1, vdisk) != 1 ){
        printf("Error with reading superblock\n");
        return -1;
    }
    
    if( fseek(file_to_copy, 0L, SEEK_END) != 0 ){/*SEEK_END not portable*/
        printf("Error with fseek(SEEK_END)\n");
        return -1;
    }
    size_of_file = ftell(file_to_copy);

    if( size_of_file == -1L ){
        printf("Error ftell\n");
        return -1;
    }

    /*CHECKING NAME*/
    if( strlen(file_name) > MAX_FILE_NAME_LEN ){
        printf("Error: file name is too long\n");
        return -1;
    }


    for( i=0; i<dinfo.used_inodes; ++   i){
        if( fread(&tmp, sizeof(inode), 1, vdisk) != 1){
            printf("Error with reading inodes\n");
            return -1;
        }

        if( strcmp(tmp.fname, file_name) == 0 ){
            printf("Error:file name is occupied\n");
            return -1;
        }
    }
    /*Checking if can allocate:

    first: check if there is empty space after last block of data and free inode
    -if yes: allocate it there
    -if not: go through all inodes and check if there is continous space 
        for new file
        -if yes, allocate it there
        -if no, do nothing
    */
    if( size_of_file<dinfo.free_space   &&
     dinfo.addr_of_next_free_inode < dinfo.disk_size*128    &&
     dinfo.addr_of_next_free_inode > 0 ){

        if( fseek(vdisk, dinfo.addr_of_next_free_inode, SEEK_SET) != 0 ){
            printf("Error with fseek2\n");
            return -1;
        }
        adr_inode = dinfo.addr_of_next_free_inode;
        dinfo.addr_of_next_free_inode += sizeof(inode);

        if( fread(&file_inode, sizeof(inode), 1, vdisk) !=1 ){
            printf("Error with fread\n");
            return -1;
        }
        if( file_inode.is_used == 1){
            printf("Error: inode is used, bad structure of file\n");
            return -1;
        }

        file_inode.fsize = size_of_file;
        file_inode.addr_to_data = dinfo.addr_of_next_free_space;
        strcpy(file_inode.fname, file_name);
        file_inode.is_used=1;

        
        dinfo.addr_of_next_free_space += size_of_file;
        dinfo.free_space -= size_of_file;
        ++dinfo.number_of_files;
        ++dinfo.used_inodes;

        if( fseek(vdisk, 0, SEEK_SET) != 0 ){
            printf("Error with fseek3\n");
            return -1;
        }
        if( fwrite(&dinfo, sizeof(sinfo), 1, vdisk) != 1 ){
            printf("Error with writing superblock\n");
            return -1;
        }    
    }else{/* find empty slot after deleted file*/
        if( fseek(vdisk, sizeof(sinfo), SEEK_SET) != 0){
            printf("Error with fseek4\n");
            return -1;
        }
        for( i=0; i< dinfo.used_inodes; ++i ){
            if( fread(&tmp, sizeof(inode), 1, vdisk) != 1 ){
                printf("Error with looking for empty inode\n");
                return -1;
            }
            if( tmp.is_used == 0 && tmp.fsize >= size_of_file){
                file_inode = tmp;
                /* 
                    przypisac wolne miejsce do nastepnego inode'a
                    jezeli nastepny nie jest wolny, to znalezc node nieprzypisany do zadnego miejsca
                    jezeli takiego nie ma, to wolne miejsce zostaje utracone bezpowrtonie
                */
                file_inode.fsize = size_of_file;
                file_inode.is_used=1;
                strcpy(file_inode.fname,file_name);

                adr_inode = sizeof(dinfo) + i*sizeof(inode);
                break;/* slot found*/
            }
        }
    }
    /*WRITE UPDATED INODE*/
    if( fseek(vdisk, adr_inode, SEEK_SET) != 0 ){
        printf("Error with fseek5\n");
        return -1;
    }
    if( fwrite(&file_inode, sizeof(inode), 1, vdisk) != 1 ){
        printf("Error with writing inode\n");
        return -1;
    }
    /*COPING DATA*/
    if( fseek(vdisk, file_inode.addr_to_data, SEEK_SET) != 0){
        printf("Error with fseek6\n");
        return -1;
    }
    if( fseek(file_to_copy, 0, SEEK_SET) !=0 ){
        printf("Error with fseek7\n");
        return -1;
    }
    if( fread(buffer, sizeof(char), size_of_file, file_to_copy) < 0){
        printf("Error with reading from file\n");
        return -1;
    }

    if( fwrite(buffer, sizeof(char), size_of_file, vdisk) < 0){
        printf("Error with writing to file\n");
        return -1;
    }


    /*END OF WORK*/
    if( fclose(file_to_copy) != 0 ){
        printf("Error with closig disk\n");
        return -1;
    }

    if( fclose(vdisk) != 0 ){
        printf("Error with closig disk\n");
        return -1;
    }
    return 0;
    
}