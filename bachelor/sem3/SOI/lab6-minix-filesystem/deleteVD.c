#include "file_system.h"

int deleteVD(void){
    return unlink(disk_name);
}