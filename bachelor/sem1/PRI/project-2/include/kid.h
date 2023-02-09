#ifndef _KID_H_
#define _KID_H_


#include <stdbool.h>


#define TELEPHONE_LENGTH 10
#define NAME_LENGTH 20
#define DATE_LENGTH 11
#define LINE_LENGTH 300

#define BEZ_ZASTRZEZEN_STRING "Bez zastrzezen"
#define WEGETARIANSKA_STRING "Wegetarianska"
#define BEZGLUTENOWA_STRING "Bezglutenowa"

#define BIEDRONKI_STRING "Biedronki"
#define SKRZATY_STRING "Skrzaty"
#define KRASNOLUDKI_STRING "Krasnoludki"

typedef struct Preschooler{
        int kid_id;
        char surname[NAME_LENGTH];
        char name[NAME_LENGTH];
        char parent_telephone[TELEPHONE_LENGTH];
        char birth_date[DATE_LENGTH];
        enum DIETA{ BEZ_ZASTRZEZEN, WEGETARIANSKA, BEZGLUTENOWA} diet;
        enum AGE_CATEGORY {BIEDRONKI, SKRZATY, KRASNOLUDKI} group;

        struct Preschooler* next;
        struct Preschooler* prev;
} Preschooler;

void giveName(char*, const char*);
bool checkName( const char*);
void giveBirthdate(char*);
bool checkBirthdate( const char*);
void giveTelephone(char*);
bool checkTelephone( const char*);
void chooseDiet(Preschooler*);
void chooseGroup(Preschooler*);
void printElement(Preschooler*);


#endif
