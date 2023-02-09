#include "kid.h"
#include "list.h"
#include "file.h"
#include "menu.h"
#include "additional.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>


void menu(DDL* list){
    char option;
    while(1){
        showMenu();
        scanf("%c", &option);
        clear_buffer();
        switch(option){
            case('1'): addKid(list); break;
            case('2'): chooseSearch(list); break;
            case('3'): choosePrint(list); break;
            case('4'): chooseSort(list); break;
            case('5'): chooseSave(list); break;
            case('6'): chooseRead(list); break;
            case('7'): chooseElementToRemove(list); break;
            case('8'): removeAll(list); break;
            case('0'): end(list); return;
        }
    }
}

void showMenu(){
    puts("[1]Dodaj dziecko\n"
         "[2]Wyszukaj dziecko\n"
         "[3]Wypisz liste\n"
         "[4]Posortuj liste\n"
         "[5]Zapisz liste do pliku\n"
         "[6]Wczytaj liste z pliku\n"
         "[7]Usun element\n"
         "[8]Usun cala list\n"
         "[0]Zakoncz");
}

void chooseSearch(DDL* list){
    puts("Wybierz jaki element chcesz wyszukac:\n"
         "[1]Nazwisko \t[2]Id");
    char option;
    while(1){
        scanf("%c", &option);
        clear_buffer();
        if( '1' == option ){
            puts("Podaj naziwsko do wyszukania");
            char surname[NAME_LENGTH];
            scanf("%s", surname);
            clear_buffer();
            findSurname(list, surname);
            return;
        }else if( '2' == option ){
            puts("Podaj id, ktore chcesz wyszukac");
            int id;
            char input[NAME_LENGTH];
            scanf("%s", input);
            id = strtol(input, NULL, 10);
            clear_buffer();
            findId(list, id);
            return;

        }
        puts("Popraw sie");
    }
}

void choosePrint(DDL* list){
    puts("Ktore elemnty chcesz wypisac?\n"
         "[1]Wszystkie\t [2]Grupe\t [3]Wg diety");
    char option;
    while(1){
        scanf("%c", &option);
        clear_buffer();
        if( '1'==option ){
            printList(list);
            return;
        }
        else if( '2' == option ){
            printGroup(list);
            return;
        }
        else if( '3' == option ){
            printDiet(list);
            return;
        }
        puts("Nie ma takiej opcji, popraw sie");
    }

}

void chooseSort(DDL* list){
    puts("Wybierz wedlug jakiego elementu chcesz posorowac:\n"
         "[1]Alfabetycznie \t[2]Data urodzin");
    char option;
    while(1){
        scanf("%c", &option);
        clear_buffer();
        if( '1' == option ){
            sortAlphaDate(list, SURNAME_KEY);
            return;
        }
        else if( '2' == option ){
            sortAlphaDate(list, BIRTHDATE_KEY);
            return;
        }
    }
}

bool chooseFile(){
    puts("[1]Binarnie\t [2]Tekstowo");
    char option;
    while(1){
        scanf("%c", &option);
        clear_buffer();
        if( '1' == option ){
            return true;
        }
        else if( '2' == option ){
            return false;
        }
        puts("Nie ma takiej opcji, popraw sie");
    }
}

void chooseSave(DDL* list){
    if( chooseFile() ){
        saveBinaryFile(list);
    }else{
        saveTextFile(list);
    }
}

void chooseRead(DDL* list){
    if( chooseFile() ){
        readBinaryFile(list);
    }else{
        readTextFile(list);
    }
}
void chooseElementToRemove(DDL* list){
    puts("Podaj id elementu, ktory chcesz usunac"
         "Wpisz 'anuluj', aby anulowac");
    char input[NAME_LENGTH];
    while(1){
        scanf("%s", input);
        clear_buffer();
        if( !strcmp(input, "anuluj") ){
            return;
        }
        int id_to_remove = strtol(input, NULL, 10);
        Preschooler* temp = list->head;
        while(1){
            if(NULL == temp){
                puts("brak elementu");
                return;
            }
            if( temp->kid_id == id_to_remove){
                removeElement(list, temp);
                puts("usunieto element");
                return;
            }
            temp = temp->next;
        }
        puts("Popraw sie");
    }
}
void end(DDL* list){
    if( NULL == list->head){
        return;
    }
    puts("Zapisac liste przed zamknieciem?\n"
         "[1]Tak\t [2]Nie");
    char option;
    while(1){
        scanf("%c", &option);
        clear_buffer();
        if( '1' == option){
            chooseSave(list);
            return;
        }
        else if( '2' == option ){
            return;
        }
        puts("Nie ma takiej opcji, popraw sie");
    }

}
