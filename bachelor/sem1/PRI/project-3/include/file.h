#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdbool.h>
#include "kid.h"
#include "list.h"

#define NAME_KEY "Imie"
#define SURNAME_KEY "Nazwisko"
#define BIRTHDATE_KEY "Data urodzenia"
#define TELEPHONE_KEY "Telefon"
#define DIET_KEY "Dieta"
#define GROUP_KEY "Grupa"

void getFileName(char*);
void saveBinaryFile(DDL*);
void saveTextFile(DDL*);
/* Zwraca prawde, jezeli podany znak jest pierwszy w linijce*/
bool checkCharacter(const char, FILE*);
bool getName(const char*, char*, FILE*);
bool getTelephone( const char*, char*, FILE*);
bool getBirthday( const char*, char*, FILE*);
bool getString(const char*, char*, FILE*);
bool getValue(const char*, char*, FILE*);
bool checkKey(const char*, char* );
bool getNumber(const char*, int*, FILE*);
void readBinaryFile(DDL*);
void readTextFile(DDL*);
bool getDiet(const char*, Preschooler*, FILE*);
bool getGroup(const char*, Preschooler*, FILE*);


#endif
