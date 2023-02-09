#ifndef _LIST_H_
#define _LIST_H_

#include "kid.h"
#include <stdbool.h>

#define NAME_KEY "Imie"
#define SURNAME_KEY "Nazwisko"
#define BIRTHDATE_KEY "Data urodzenia"
#define TELEPHONE_KEY "Telefon"
#define DIET_KEY "Dieta"
#define GROUP_KEY "Grupa"

typedef struct DDL{
    int elements;

    Preschooler* head;
    Preschooler* tail;
} DDL;


DDL* init_list();
void addKid(DDL*);
void pushBack(DDL*, Preschooler*);
void removeElement(DDL*, Preschooler*);
void removeAll(DDL*);
/* Sortuje liste alfabetycznie albo od najmlodszego na podstawie podanego klucza */
void sortAlphaDate(DDL*, const char*);
/* Zwraca prawde jezeli pierwszy jest wczesniej w hierarchii*/
bool compareAlphaDate(Preschooler*, Preschooler*, const char*);
void swap(Preschooler*, Preschooler*);
void copy(Preschooler*, Preschooler*);

void findId(DDL*,const int);
void findSurname(DDL*, const char*);
void printDiet(DDL*);
void printGroup(DDL*);
void printList(DDL*);

#endif
