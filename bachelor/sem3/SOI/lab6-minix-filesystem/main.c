#include "file_system.h"

int main(int argc, char**argv){
    if( argc < 2){
        return 1;
    }

    if( strcmp(argv[1], "create") == 0){
        if( argc< 3 ){
            return -1;
        }
        return createVD( atoi(argv[2]) );
    }else if( strcmp( argv[1], "copyTo")==0 ){
        if( argc<3 ){
            return -1;
        }
        return copyTo( argv[2] );
    }else if( strcmp( argv[1], "copyFrom")==0){
        if( argc<3 ){
            return -1;
        }
        return copyFrom( argv[2] );
    }else if( strcmp( argv[1], "ls")==0){
        return ls();
    }else if( strcmp( argv[1], "remove")==0){
        if( argc<3 ){
            return -1;
        }
        return deleteFile( argv[2] );
    }else if( strcmp( argv[1], "printMap")==0){
        return printMap();
    }else if( strcmp( argv[1], "delete")==0){
        return deleteVD();
    }else{
        printf("Bad argument\n");
    }
    

    return 0;
}