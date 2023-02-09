#include "additional.h"
#include <stdio.h>

void clear_buffer(){
    char c;
    while ( (c = getchar()) != '\n' && c != EOF ) {}
}
