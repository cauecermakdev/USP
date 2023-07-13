#include <time.h>
#include <stdio.h>
#include "time_function.h"


void fim(clock_t inicio){
    clock_t fim;
    fim = clock();
    printf("%lf",((fim - inicio)/CLOCKS_PER_SEC));
}