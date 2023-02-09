#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 100
#define TAB_SIZE 512

typedef struct Country{
    char name[MAX_CHARS];
    int population;

    struct Country* next;
} Country;

typedef struct HashTable{
    int size;

    Country** table;
} HashTable;

void show_menu();
void menu( HashTable* );

//PIERWSZE CZESC ZADANIA
HashTable* init_table( int );
void add_element( HashTable* );
void print_list( HashTable* );
void find_element( HashTable* );
void delete_element( HashTable* );

//DRUGA CZESC ZADANIA
void check_colisions( HashTable* );
int hash_function( char[] );

void add_existing_element( HashTable*, char* );
void file_input( HashTable* );

extern inline void clear_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main()
{
    HashTable *countries = init_table(TAB_SIZE);
    menu(countries);
    return 0;
}

void show_menu(){
    printf(//"Pierwsza czesc zadania:\n"
            "[1]Dodaj element\n"
            "[2]Wypisz\n"
            "[3]Wyszukaj\n"
            "[4]Usun element\n"
            //"Druga czesc zadania:\n"
            "[5]Sprawdz kolizje\n"
            "[6]Wczytaj z pliku\n"
            "[0]Wyjdz\n");
}

void menu( HashTable* ht){
    show_menu();
    while(1){
        puts("Wybierz opcje:");
        int option;
        scanf("%d", &option);
        //system("cls");
        //NIE DZIALA
        switch(option){
            case(1):
                add_element(ht);
                break;
            case(2):
                print_list(ht);
                show_menu();
                break;
            case(3):
                find_element(ht);
                break;
            case(4):
                delete_element(ht);
                break;
            case(5):
                check_colisions(ht);
                show_menu();
                break;
            case(6):
                clear_buffer();
                file_input(ht);
                printf("Udalo sie wczytac dane z pliku\n");
                break;
            case(0):
                return;
        }
    }
}

HashTable* init_table( int size){
    if( size < 1 ){
        return NULL;
    }

    HashTable* hash_table = malloc( sizeof(HashTable) );
    hash_table->table = malloc( sizeof(Country*)*size );

    for( int i=0; i<size; ++i){
        hash_table->table[i]=NULL;
    }

    hash_table->size = size;

    return hash_table;

}

void add_element( HashTable* ht){
    Country* new_element = malloc( sizeof(Country) );

    puts("Podaj nazwe kraju:");
    char tmp[MAX_CHARS];
    scanf("%s", tmp);
    strcpy( new_element->name, tmp);

    puts("Podaj populacje");
    scanf("%d", &new_element->population);

    int number = hash_function( new_element->name );
    if( NULL == ht->table[number] ){
        ht->table[number] = new_element;
    }else{
        Country* temp = ht->table[number];
        while(1){
            if(NULL == temp->next ){
                temp->next = new_element;
                new_element->next = NULL;
                return;
            }
            temp = temp->next;
        }
    }
}

void print_list( HashTable* ht){
    puts("Numer:Kraj\t Populacja");
    puts("-----------");
    for(int i=0; i<TAB_SIZE; ++i){
        if(ht->table[i]){
            printf("%d:%s\t%d\n", i, ht->table[i]->name, ht->table[i]->population);
            Country* temp = ht->table[i];
            while(1){
                temp = temp->next;
                if( temp ){
                    printf("%d:%s\t%d\n", i, temp->name, temp->population);
                }else{
                    break;
                }
            }
        }
    }
    puts("-----------");
}

void find_element(HashTable* ht){
    puts("Podaj nazwe kraju, ktory chcesz znalezc:");
    char name[MAX_CHARS];
    clear_buffer();
    scanf("%[^\n]s ",name);
    int number = hash_function(name);
    Country* temp = ht->table[number];
    while(1){
            if(temp){
                if( !strcmp( name, temp->name) ){
                    printf("%d:%s---%d\n", number, temp->name, temp->population);
                    return;
                }
            }
            else{
                puts("Nie ma takiego elementu");
                return;
            }
            temp=temp->next;

    }

}

void delete_element( HashTable* ht){
    puts("Podaj nazwe kraju, ktory chcesz usunac z listy:");
    char name[MAX_CHARS];
    clear_buffer();
    scanf("%[^\n]s ",name);
    int number = hash_function(name);
    Country* temp = ht->table[number], *prev=NULL;
    while(1){
            if(temp){
                if( !strcmp( name, temp->name) ){
                    if( prev ){
                        prev->next = temp->next;
                    }
                    else{
                        ht->table[number]= temp->next;
                    }
                    free(temp);
                    printf("Udalo sie usunac element\n");
                    return;
                }
            }
            else{
                puts("Nie ma takiego elementu");
                return;
            }
            prev = temp;
            temp=temp->next;
    }
}

void file_input(HashTable* ht){
    FILE *fPointer;
    fPointer = fopen("countries.txt", "r" );
    if( NULL == fPointer){
        puts("Blad podczas otwierania pliku");
        return;
    }else{
        char name[MAX_CHARS];
        while( !feof(fPointer) ){
            //clear_buffer();
            //fscanf (fPointer, name );
            fgets( name, MAX_CHARS, fPointer );
            for(int i=0;;++i){
                if( name[i]=='\n'){
                    name[i]='\0';
                    break;
                }

            }
            add_existing_element(ht, name);
        }
    }
    fclose(fPointer);

}

int hash_function( char string[] ){
    int length = strlen( string );
    int hash=0;
    for( int i=0; i<length; ++i){
        hash+=string[i]*11;
    }
    return hash%TAB_SIZE;
}

void add_existing_element( HashTable* ht, char* name){
    Country* new_element = malloc( sizeof(Country) );
    strcpy( new_element->name, name);
    int number = hash_function( new_element->name );
    if( NULL == ht->table[number] ){
        ht->table[number] = new_element;
    }else{
        Country* temp = ht->table[number];
        while(1){
            if(NULL == temp->next ){
                temp->next = new_element;
                new_element->next = NULL;
                return;
            }
            temp = temp->next;
        }
    }
}

void check_colisions( HashTable* ht ){
    int number_of_colisons=0;
    const int ESTIMATED=5;
    int colisions[ESTIMATED];
    for(int i=0; i<ESTIMATED; ++i){
        colisions[i]=0;
    }
    for(int i=0; i<TAB_SIZE; ++i){
        int colision_rate=0;
        int rate=-1;
        if(ht->table[i]){
            Country* temp = ht->table[i];
            while(1){
                ++rate;
                ++colisions[rate];
                if( rate>=2 ){
                    --colisions[rate-1];
                }
                temp = temp->next;
                if( temp ){
                    ++number_of_colisons;
                    ++colision_rate;
                }else{
                    break;
                }
            }
        }
    }
    printf("Ilosc kolizji:%d\n", number_of_colisons);
    for(int i=1; i<ESTIMATED; ++i){
        printf("Ilosc kolizji %d stopnia:%d\n", i, colisions[i]);
    }
}
