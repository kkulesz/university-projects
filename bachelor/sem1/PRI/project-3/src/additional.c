#include <stdio.h>
#include "additional.h"

void clear_buffer(){
    char c;
    while ( (c = getchar()) != '\n' && c != EOF ) {}
}
