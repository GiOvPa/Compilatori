%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "SymbolTable/symboltable.h"
    #include "SymbolTable/dati.h"
    #include <float.h>

    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
    void yyerror(const char *s);

    struct Fascia *fasce = NULL;
    Costi_aggiuntivi *ca = NULL;
%}

%union {
    int ival;
    float fval;
    char *sval;
}

%token <ival> INTEGER
%token <fval> FLOAT
%token <sval> CF NAME

%token SEPARATORE1 SEPARATORE2 SEPARATORE3 ANNO COLON FASCIA FRECCIA COSTO_ELETTRICO CANONE_FOGNATURA NOLO_CONTATORE IVA EURO MC DOT PERCENT COMMA
%start input
%%

input:
    anno SEPARATORE1 prima_fascia SEPARATORE2 costi_aggiuntivi SEPARATORE3 primo_user
    ;
anno:
    ANNO INTEGER
    ;

prima_fascia :
    FASCIA INTEGER COLON INTEGER FRECCIA INTEGER FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, $6, $2) && $6 >= $4) insertFascia(&fasce, $2, $6, $4, $9);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |FASCIA INTEGER COLON FLOAT FRECCIA FLOAT FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, $6, $2) && $6 >= $4) insertFascia(&fasce, $2, $6, $4, $9);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |FASCIA INTEGER COLON FLOAT FRECCIA INTEGER FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, $6, $2) && $6 >= $4) insertFascia(&fasce, $2, $6, $4, $9);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |FASCIA INTEGER COLON INTEGER FRECCIA FLOAT FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, $6, $2) && $6 >= $4) insertFascia(&fasce, $2, $6, $4, $9);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
fasce:
    FASCIA INTEGER COLON INTEGER FRECCIA INTEGER FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, $6, $2) && $6 >= $4) insertFascia(&fasce, $2, $6, $4, $9);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |FASCIA INTEGER COLON FLOAT FRECCIA FLOAT FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, $6, $2) && $6 >= $4) insertFascia(&fasce, $2, $6, $4, $9);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |FASCIA INTEGER COLON FLOAT FRECCIA INTEGER FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, $6, $2) && $6 >= $4) insertFascia(&fasce, $2, $6, $4, $9);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |FASCIA INTEGER COLON INTEGER FRECCIA FLOAT FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, $6, $2) && $6 >= $4) insertFascia(&fasce, $2, $6, $4, $9);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |FASCIA INTEGER COLON INTEGER FRECCIA FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, FLT_MAX, $2) && FLT_MAX >= $4) insertFascia(&fasce, $2, 10000.0, $4, $8);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |FASCIA INTEGER COLON FLOAT FRECCIA FRECCIA EURO FLOAT MC fasce{
        if(checkRegularValue(fasce, $4, FLT_MAX, $2) && FLT_MAX >= $4) insertFascia(&fasce, $2, 10000.0, $4, $8);
        else{
            printf("Valori dei limiti delle fasce non coerenti\n");
            return(-1);
        }
    }
    |
    ;

costi_aggiuntivi:
    COSTO_ELETTRICO COLON EURO FLOAT MC CANONE_FOGNATURA COLON EURO FLOAT MC NOLO_CONTATORE COLON EURO FLOAT DOT IVA COLON INTEGER PERCENT DOT{
        if($18 > 0 && $18 <= 100){
            insertCostoEnergiaElettrica(&ca, $4);
            insertCanoneFognatura(&ca, $9);
            insertNoloContatore(&ca, $14);
            insertIVA(&ca, $18);
        }else{
            printf("Valore IVA non valido\n");
            return (-1);
        }
    }
    |COSTO_ELETTRICO COLON EURO FLOAT MC CANONE_FOGNATURA COLON EURO FLOAT MC NOLO_CONTATORE COLON EURO FLOAT DOT IVA COLON FLOAT PERCENT DOT{
        if($18 > 0 && $18 <= 100){
            insertCostoEnergiaElettrica(&ca, $4);
            insertCanoneFognatura(&ca, $9);
            insertNoloContatore(&ca, $14);
            insertIVA(&ca, $18);
        }else{
            printf("Valore IVA non valido");
            return (-1);
        }
    }
    ;

primo_user: 
    NAME COMMA CF COMMA INTEGER COMMA INTEGER lista_user{
        insert($1, $3, $5, $7);
    }
lista_user:
    NAME COMMA CF COMMA INTEGER COMMA INTEGER lista_user{
        insert($1, $3, $5, $7);
    }
    |
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Errore: %s\n", s);
    freeHashTable();
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }
    yyparse();

    calculate_total(fasce, ca);
    print_total();

    freeHashTable();

    return 0;
}
