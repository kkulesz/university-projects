#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "kid.h"
#include "list.h"
#include "additional.h"

DDL* init_list(){
    DDL* list = malloc( sizeof(DDL) );
    list->head = NULL;
    list->tail = NULL;
    list->elements=0;
    return list;
}

void addKid(DDL* list){
    Preschooler* new_kid = malloc( sizeof(Preschooler) );
    giveName(new_kid->name, "imie");
    giveName(new_kid->surname, "nazwisko");
    giveBirthdate(new_kid->birth_date);
    giveTelephone(new_kid->parent_telephone);
    chooseDiet(new_kid);
    chooseGroup(new_kid);
    pushBack(list, new_kid);
    return;
}

void pushBack(DDL* list, Preschooler* new_element){
    if( NULL == list->head){
        list->head=new_element;
        list->tail=new_element;
        new_element->next = NULL;
        new_element->prev = NULL;

        ++list->elements;
        new_element->kid_id = list->elements;
        return;
    }
    new_element->next = list->head;
    list->head->prev = new_element;
    list->head = new_element;
    new_element->prev = NULL;


    ++list->elements;
    new_element->kid_id = list->elements;
    return;
}

void removeElement(DDL* list, Preschooler* kid){
    if( NULL == list || NULL == kid ){
        return;
    }
    if(list->head==kid){
        list->head = list->head->next;
    }
    if(list->tail==kid){
        list->tail = list->tail->prev;
    }

    if( kid->next!=NULL ){
        kid->next->prev = kid->prev;
    }

    if( kid->prev!=NULL ){
        kid->prev->next = kid->next;
    }

    free(kid);
}

void removeAll(DDL* list){
    if( NULL == list || NULL == list->head){
        puts("Lista jest pusta");
        return;
    }

    Preschooler* temp = list->head;
    while(temp){
        free(temp);
        temp=temp->next;
    }
    list->head = NULL;
    list->tail = NULL;
    puts("Lista usunieta");
}

void printList(DDL* list){
    if( NULL == list || NULL == list->head ){
        puts("Brak elementow");
        return;
    }
    Preschooler* temp = list->head;
    puts("id: nazwisko imie --- data urodzenia --- telefon rodzica --- dieta --- grupa");
    while(temp != NULL){
        printElement(temp);
        temp = temp->next;
    }
}

void printElement(Preschooler* kid){
    if( kid == NULL){
        return;
    }
    printf("%d: %s %s --- %s --- %s --- ", kid->kid_id, kid->surname, kid->name, kid->birth_date, kid->parent_telephone);
    if(kid->diet == BEZ_ZASTRZEZEN)     { printf("%s --- ", BEZ_ZASTRZEZEN_STRING); }
    else if(kid->diet == WEGETARIANSKA) { printf("%s --- ", WEGETARIANSKA_STRING); }
    else if(kid->diet == BEZGLUTENOWA)  { printf("%s --- ", BEZGLUTENOWA_STRING); }

    if(kid->group == BIEDRONKI)         { printf("%s\n", BIEDRONKI_STRING); }
    else if(kid->group == SKRZATY)      { printf("%s\n", SKRZATY_STRING); }
    else if(kid->group == KRASNOLUDKI)  { printf("%s\n", KRASNOLUDKI_STRING); }


}



void sortAlphaDate(DDL* list, const char* key){
    if( NULL==list->head ){
        return;
    }
    Preschooler* temp = list->tail;

    for( bool swapped = true;swapped; temp=list->tail){
        swapped = false;
        for( ;NULL != temp->prev; temp=temp->prev ){
            if( compareAlphaDate(temp, temp->prev, key)){
                swap(temp, temp->prev);
                swapped=true;
            }
        }
    }
    puts("Lista posortowana");
    temp = NULL;
    free(temp);
}

bool compareAlphaDate(Preschooler* first, Preschooler* second, const char* key){
    int result;
    if( !strcmp(key, SURNAME_KEY) ){
        result = strcmp(first->surname, second->surname);
    }else if ( !strcmp(key, BIRTHDATE_KEY) ){
        result = strcmp(first->birth_date, second->birth_date);
        if(!result){
            return false;//gdy sa takie same daty
        }
    }

    if( result > 0 ){
        return false;
    }
    else if( result < 0){
        return true;
    }//koniec porownywania dat

    result = strcmp( first->name, second->name);
    if( result > 0 ){
        return false;
    }
    else if( result < 0){
        return true;
    }
//imiona i nazwiska sa takie same
    return false;
}

void swap(Preschooler* first, Preschooler* second){
    Preschooler* temp = malloc( sizeof(Preschooler) );

    copy(temp, first);
    copy(first, second);
    copy(second, temp);

    temp=NULL;
    free(temp);
}

void copy( Preschooler* into, Preschooler* from){
    into->kid_id = from->kid_id;
    into->diet = from->diet;
    into->group = from->group;
    strcpy(into->surname, from->surname);
    strcpy(into->name, from->name);
    strcpy(into->birth_date, from->birth_date);
    strcpy(into->parent_telephone, from->parent_telephone);
}

void findId(DDL* list, const int i){
    Preschooler* temp = list->head;
    while( NULL != temp ){
        if(temp->kid_id == i){
                printElement(temp);

                temp = NULL;
                free(temp);
                return;
        }
        temp=temp->next;
    }
    puts("Brak elementu");
    temp = NULL;
    free(temp);
}

void findSurname(DDL* list, const char* surname){
    bool found = false;
    Preschooler* temp = list->head;
    while(NULL != temp){
        if( !strcmp(temp->surname, surname) ){
            printElement(temp);
            found = true;
        }
        temp = temp->next;
    }
    if( !found ){
        puts("Brak elementu");
    }
    temp = NULL;
    free(temp);
}

void printDiet(DDL* list){
    Preschooler checker;
    chooseDiet(&checker);

    Preschooler* temp = list->head;
    bool found = false;
    while(NULL != temp){
        if( temp->diet == checker.diet ){
            printElement(temp);
            found = true;
        }
        temp = temp->next;
    }
    if( !found ){
        puts("Brak elementu");
    }
    temp = NULL;
    free(temp);
}

void printGroup(DDL* list){
    Preschooler checker;
    chooseGroup(&checker);

    Preschooler* temp = list->head;
    bool found = false;
    while(NULL != temp){
        if( temp->group == checker.group ){
            printElement(temp);
            found = true;
        }
        temp = temp->next;
    }
    if( !found ){
        puts("Brak elementu");
    }
    temp = NULL;
    free(temp);
}
