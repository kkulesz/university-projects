#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "additional.h"
#include "kid.h"


void giveName(char* string ,const char* message){
    printf("Podaj %s:\n", message);
    while(1){
        scanf("%s", string);
        clear_buffer();
        if( checkName(string)){
            return;
        }
        else{
            puts("zly format");
        }
    }
}

bool checkName(const char* string){
    if(string[0]<'A' || string[0]>'Z'){
        return false;
    }
    int word_length = strlen(string);
    for( int i = 1; i<word_length; ++i ){
        if( string[i]<'a' || string[i]>'z'){
            return false;
        }
    }
    return true;
}

void giveBirthdate(char* date){
    puts("Podaj date \nFormat RRRR/MM/DD");
    while(1){
        char input[TELEPHONE_LENGTH];
        scanf("%s", input);
        clear_buffer();
        if( checkBirthdate(input) ){
            strcpy(date, input);
            return;
        }
        else{
            puts("zly format");
        }
    }
}

bool checkBirthdate( const char* date){
    if( strlen(date) != DATE_LENGTH-1 ){
        return false;
    }
    if( date[4] != '/' || date[7] != '/' ){
        return false;
    }
    for( int i=0; i<DATE_LENGTH-1; ++i){
        if( i==4 || i==7){
            ++i;
        }
        if( date[i]<'0' || date[i]>'9' ){
            return false;
        }
    }
    int year ,month, day;
    year = strtol(date,NULL,10);
    month = strtol(date+5, NULL, 10);
    day = strtol( date+8, NULL, 10);

    if( month>12 ){
        return false;
    }
    if( month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        if(day > 31){
            return false;
        }
    }else if( month == 4 || month == 6 || month == 9 || month == 11){
        if( day>30){
            return false;
        }
    }else if(month==2){
        if(year%4==0){
            if( day>29 ){
                return false;
            }
        }else{
            if( day>28 ){
                return false;
            }
        }
    }
    return true;
}

void giveTelephone(char* tel){
    puts("Podaj numer telefonu rodzina:");
    while(1){
        scanf("%s", tel);
        clear_buffer();
        if( checkTelephone(tel) ){
            return;
        }
        else{
            puts("zly format");
        }
    }
}

bool checkTelephone(const char* tel){
    if( strlen(tel) != TELEPHONE_LENGTH-1 ){
        return false;
    }//
    for( int i=0; i<TELEPHONE_LENGTH-1; ++i ){
        if( tel[i]<'0' || tel[i]>'9' ){
            return false;
        }
    }
    return true;	
}

void chooseDiet(Preschooler* kid){
    puts("Wybierz diete:\n"
         "[1]Bez zastrzezen [2]Wegeterianska [3]Bezglutenowa");
    char option;
    while(1){
        scanf("%c", &option);
        clear_buffer();
        switch( option ){
            case('1'): kid->diet = BEZ_ZASTRZEZEN; return;
            case('2'): kid->diet = WEGETARIANSKA; return;
            case('3'): kid->diet = BEZGLUTENOWA; return;
            default: puts("Popraw sie"); break;
        }
    }
}

void chooseGroup(Preschooler* kid){
    puts("Wybierz kategorie:\n"
         "[1]Biedronki  [2]Skrzaty  [3]Krasnoludki");
    char option;
    while(1){
        scanf("%c", &option);
        clear_buffer();
        switch( option ){
            case('1'): kid->group = BIEDRONKI; return;
            case('2'): kid->group = SKRZATY; return;
            case('3'): kid->group = KRASNOLUDKI; return;
            default: puts("Popraw sie"); break;
        }
    }
}
