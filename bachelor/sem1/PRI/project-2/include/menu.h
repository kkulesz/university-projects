#ifndef _MENU_H_
#define _MENU_H_


#include "list.h"
#include <stdbool.h>


void end(DDL*);
void menu(DDL*);
void showMenu();
void chooseSearch(DDL*);
void chooseSort(DDL*);
bool chooseFile();
void chooseSave(DDL*);
void chooseRead(DDL*);
void choosePrint(DDL*);
/* Usuwa element o podanym przez uzytkownika id*/
void chooseElementToRemove(DDL*);


#endif
