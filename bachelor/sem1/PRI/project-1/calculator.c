#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main( void ){
	srand(time(NULL));

	short int czy_wyjsc=0;
	do{
		puts("Wybierz działanie: \n[1]Dodawanie \n[2]Odejmowanie \n[3]Mnożenie \n[4]Dzielenie \n[0]Wyjdź");

		double choice;
		int a,b;
		int result;

		int is_correct=1;//do sprawdzania czy liczba jest liczba naturalna
		do{
			scanf("%lf",&choice);
			if(choice-(int)choice!=0 || choice<0){
				puts("Błąd, popraw się");
				is_correct=0;
			}
			else{
				is_correct=1;
			}
		}while( !is_correct );
		if(choice==1 || choice==2 || choice==3 || choice==4){
			puts("Podaj pierwszą liczbę:");
			scanf("%o",&a);
			puts("Podaj drugą liczbę:");
			scanf("%o",&b);
		}

		switch((int)choice){
			case(1):
				result=a+b;
				break;
			case(2):
				result=a-b;
				break;
			case(3):
				result=a*b;
				break;
			case(4):
				result=a/b;
				break;
			case(0):
				puts("Wychodzę");
				czy_wyjsc=1;
				break;
			default:
				puts("Wybierz liczbe uwzględnioną w menu!");
				break;
		}

		if(choice==1 || choice==2 || choice==3 || choice==4){
			int random;
			random =rand();
			if(random%2==0)
				printf("Wynik: %o \n", result);
			else
				printf("Wynik: %o \n", random);
		}

	}while(!czy_wyjsc);

return 0;
}
