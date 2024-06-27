#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "dati.h"

typedef struct Symbol {
    char *name;
    char *cf;
    int first_read;
    int last_read;
    float total;
} Symbol;

struct SymbolEntry {
    struct SymbolEntry *next;
    Symbol *info;
};

unsigned int hash(char *code);
struct SymbolEntry *lookup(char *code);
int insert(char *name, char *cf, int fr, int lr);
void symbol_table_print();
void calculate_total(struct Fascia *fascie, Costi_aggiuntivi *ca);
void freeSymbol(Symbol *symb);
void freeSymbolEntry(struct SymbolEntry* entries);
void freeHashTable();
void print_total();

#endif
    