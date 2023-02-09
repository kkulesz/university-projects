#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#include "kid.h"
#include "additional.h"
#include "list.h"
#include "file.h"
#include "menu.h"


int main(){
    puts("Baza danych przedszkola");
    DDL* list = init_list();
    menu(list);
    return 0;
}

