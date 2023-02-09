#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "kid.h"
#include "list.h"
#include "file.h"
#include "additional.h"


void getFileName(char* file_name){
    puts("Podaj nazwe pliku:");
    scanf("%[^\n]s ",file_name);
    clear_buffer();
}

void saveBinaryFile(DDL* list){
    FILE* to_file;
    char file_name[NAME_LENGTH];
    getFileName(file_name);
    to_file = fopen(file_name, "wb");
    if( NULL == to_file ){
        puts("Blad podczas otwierania pliku!");
        return;
    }
    Preschooler* temp = list->head;
    while( temp ){
        fwrite(temp,sizeof(Preschooler), 1, to_file);
        temp=temp->next;
    }
    fclose(to_file);
    puts("Lista zapisana");
    return;
}

void saveTextFile(DDL* list){
    FILE* to_file;
    char file_name[NAME_LENGTH];
    getFileName(file_name);
    to_file = fopen(file_name, "w");
    if( NULL == to_file ){
        puts("Blad podczas otwierania pliku!");
        return;
    }
    Preschooler* temp = list->head;
    while( temp ){
        fprintf(to_file,"{\n");
        fprintf(to_file,"\"%s\":\"%s\",\n",NAME_KEY, temp->name);
        fprintf(to_file,"\"%s\":\"%s\",\n",SURNAME_KEY, temp->surname);
        fprintf(to_file,"\"%s\":\"%s\",\n",TELEPHONE_KEY, temp->parent_telephone);
        fprintf(to_file,"\"%s\":\"%s\",\n",BIRTHDATE_KEY, temp->birth_date);
        switch(temp->diet){
        case(BEZ_ZASTRZEZEN):fprintf(to_file,"\"%s\":\"%s\",\n", DIET_KEY, BEZ_ZASTRZEZEN_STRING); break;
        case(WEGETARIANSKA): fprintf(to_file,"\"%s\":\"%s\",\n", DIET_KEY, WEGETARIANSKA_STRING);  break;
        case(BEZGLUTENOWA):  fprintf(to_file,"\"%s\":\"%s\",\n", DIET_KEY, BEZGLUTENOWA_STRING);   break;
        }

        switch(temp->group){
        case(BIEDRONKI):  fprintf(to_file,"\"%s\":\"%s\",\n", GROUP_KEY, BIEDRONKI_STRING);  break;
        case(SKRZATY):    fprintf(to_file,"\"%s\":\"%s\",\n", GROUP_KEY, SKRZATY_STRING);    break;
        case(KRASNOLUDKI):fprintf(to_file,"\"%s\":\"%s\",\n", GROUP_KEY, KRASNOLUDKI_STRING);break;
        }
        fprintf(to_file,"}\n");

        temp=temp->next;
    }
    fclose(to_file);
    puts("Lista zapisana");
    return;
}

void readBinaryFile(DDL* list){
    FILE* from_file;
    char file_name[NAME_LENGTH];
    getFileName(file_name);
    from_file = fopen(file_name, "rb");
    if( NULL == from_file ){
        puts("Blad podczas otwierania pliku!");
        return;
    }
    while( !feof(from_file) ){
        Preschooler* new_kid = malloc( sizeof(Preschooler) );
        fread(new_kid, sizeof(Preschooler), 1, from_file);
        bool result = checkName(new_kid->name) &&
                      checkName(new_kid->surname) &&
                      checkBirthdate(new_kid->birth_date) &&
                      checkTelephone(new_kid->parent_telephone);

        if( result ){
            pushBack(list, new_kid);
        }
    }
    fclose(from_file);
    return;
}

void readTextFile(DDL* list){
    char file_name[NAME_LENGTH];
    getFileName(file_name);
    FILE* from_file = fopen(file_name, "r");
    if( from_file == NULL ){
        puts("Blad podczas otwierania pliku!");
        return;
    }
    while( !feof(from_file) ){
        Preschooler* new_kid = malloc( sizeof(Preschooler) );
        bool result = checkCharacter('{', from_file)&&
            getString(NAME_KEY,new_kid->name, from_file) &&
            getString(SURNAME_KEY, new_kid->surname, from_file) &&
            getString(TELEPHONE_KEY, new_kid->parent_telephone, from_file) &&
            getString(BIRTHDATE_KEY, new_kid->birth_date, from_file) &&
            getDiet(DIET_KEY, new_kid, from_file) &&
            getGroup(GROUP_KEY, new_kid, from_file) &&
            checkCharacter('}', from_file);

        if(result){
            pushBack(list, new_kid);
        }
    }
    fclose(from_file);
    return;
}

bool checkCharacter( const char character, FILE* from_file){
    char buf[LINE_LENGTH];
    char* result = fgets(buf, LINE_LENGTH, from_file);
    if(result){
        if( character==buf[0]){
            return true;
        }
    }
    return false;
}

bool getString(const char* key, char* string, FILE* from_file){
    char buf[LINE_LENGTH];
    if( getValue(key, buf,from_file)){
        int size = strlen(buf);
        if( buf[0]=='"' && buf[size-1]=='"' && size-2<LINE_LENGTH ){
            strncpy( string, buf+1, size-1);
            string[size-2]='\0';
            int instance;
            if( !strcmp(key, NAME_KEY) ){ instance=1;}
            else if( !strcmp(key, SURNAME_KEY)) {instance=2;}
            else if( !strcmp(key, TELEPHONE_KEY)) {instance=3;}
            else if( !strcmp(key, BIRTHDATE_KEY)) {instance=4;}
            switch(instance){
            case(1): if(checkName(string)) {return true;} break;
            case(2): if(checkName(string)) {return true;} break;
            case(3): if(checkTelephone(string)) {return true;} break;
            case(4): if(checkBirthdate(string)) {return true;} break;
            }
        }
    }
    return false;
}

bool getValue(const char* key, char* string, FILE* from_file){
    char buf[LINE_LENGTH];
    char* result = fgets( buf, LINE_LENGTH, from_file);
    if( result && checkKey(key, buf)){
        //+3 na "":
        char* beginning = buf+strlen(key)+3;
        char* end=strrchr(beginning, ',');
        ptrdiff_t size=end-beginning;
        if(size){
            strncpy(string, beginning, size);
            string[size]='\0';
            return true;
        }
    }
    return false;
}

bool checkKey(const char* key, char* string){
    int key_length = strlen(key);
    if( string[0] == '"' && string[key_length+1]== '"' && string[key_length+2]==':'){
        if( strncmp(string+1, key, key_length)==0 ){
            return true;
        }
    }
    return false;
}

bool getDiet(const char* key, Preschooler* kid, FILE* from_file){
    char buf[LINE_LENGTH];
    char diet_word[NAME_LENGTH];
    if( getValue(key, buf, from_file) ){
        int size = strlen(buf);
        if( buf[0]=='"' && buf[size-1]=='"' && size-2<LINE_LENGTH ){
            strncpy(diet_word, buf+1, size-1);
            diet_word[size-2]='\0';
            if( !strcmp(diet_word,BEZ_ZASTRZEZEN_STRING) ) {kid->diet = BEZ_ZASTRZEZEN; return true;}
            else if( !strcmp(diet_word,WEGETARIANSKA_STRING) ) {kid->diet = WEGETARIANSKA; return true;}
            else if( !strcmp(diet_word,BEZGLUTENOWA_STRING) ) {kid->diet = BEZGLUTENOWA; return true;}
        }
    }
    return false;
}

bool getGroup(const char* key, Preschooler* kid, FILE* from_file){
    char buf[LINE_LENGTH];
    char group_word[NAME_LENGTH];
    if( getValue(key, buf, from_file) ){
        int size = strlen(buf);
        if( buf[0]=='"' && buf[size-1]=='"' && size-2<LINE_LENGTH ){
            strncpy(group_word, buf+1, size-1);
            group_word[size-2]='\0';
            if( !strcmp(group_word,BIEDRONKI_STRING) ) {kid->group = BIEDRONKI; return true;}
            else if( !strcmp(group_word, SKRZATY_STRING) ) {kid->group = SKRZATY; return true;}
            else if( !strcmp(group_word, KRASNOLUDKI_STRING) ) {kid->group = KRASNOLUDKI; return true;}
        }

    }
    return false;
}
