#include <stdio.h>
#include <stdlib.h>
#include "dati.h"
#include "symboltable.h"

int main(int argc, char const *argv[]){

    struct Fascia *fasce = NULL;
    if(checkRegularValue(fasce, 58.01, 10000.0, 3)) insertFascia(&fasce, 3, 10000.0, 58.01, 2.5);
        else{
            printf("FROCIO\n");
            return(-1);
        }
    if(checkRegularValue(fasce, 46.01, 58.01, 2)) insertFascia(&fasce, 2, 58.01, 46.01, 0.8);
        else{
            printf("FROCIO\n");
            return(-1);
        }
    if(checkRegularValue(fasce, 0, 46.02, 1)) insertFascia(&fasce, 1, 46.01, 0, 0.3);
        else{
            printf("FROCIO\n");
            return(-1);
        }
    printFasce(fasce);
}
