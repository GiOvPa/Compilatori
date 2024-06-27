#include "symboltable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASH_SIZE 101

static struct SymbolEntry *hashTable[HASH_SIZE];

unsigned int hash(char *code) {
    unsigned hashval;
    for (hashval = 0; *code != '\0'; code++)
        hashval = *code + 31 * hashval;
    return hashval % HASH_SIZE;
}

struct SymbolEntry *lookup(char *code){
    struct SymbolEntry *list = hashTable[hash(code)];
    while (list != NULL && list->info->cf == code) list = list->next;

    return list;
}

int insert(char *name, char *cf, int fr, int lr){
    struct SymbolEntry **list = &(hashTable[hash(cf)]);
    struct SymbolEntry *prev = NULL;

    while (*list != NULL) {
        prev = *list;
        list = &(*list)->next;
    }

    struct SymbolEntry *node = malloc(sizeof(struct SymbolEntry));

    if (prev == NULL) *list = node;
    else prev->next = node;

    node->info = malloc(sizeof(Symbol));
    Symbol *record = node->info;
    record->cf = malloc(sizeof(char) * (strlen(cf) + 1));
    record->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(record->cf, cf);
    strcpy(record->name, name);
    record->total = 0;
    record->first_read = fr;
    record->last_read = lr;
    node->next = NULL;

    return 0;
}

void freeSymbol(Symbol *symb){
    if(symb != NULL){
        free(symb->name);
        free(symb->cf);
        free(symb);
    }
}

void freeSymbolEntry(struct SymbolEntry* entries){
    while(entries != NULL){
        struct SymbolEntry *tmp = entries->next;
        freeSymbol(entries->info);
        free(entries);
        entries = tmp;
    }
}

void freeHashTable(){
    for (size_t i = 0; i < HASH_SIZE; i++){
        if(hashTable[i] != NULL) freeSymbolEntry(hashTable[i]);
    }
    
}

void symbol_table_print() {
    for (int i = 0; i < HASH_SIZE; ++i) {
        if(hashTable[i] != NULL) {
            struct SymbolEntry *tmp = hashTable[i];
            while(tmp != NULL) {
                printf("Name = %s, CF = %s, FirstRead = %d, LastRead = %d, Total = %.2f\n", tmp->info->name, tmp->info->cf, tmp->info->first_read, tmp->info->last_read, tmp->info->total);
                tmp = tmp->next;
            }
        }
    }
}

void calculate_total(struct Fascia *fascie, Costi_aggiuntivi *ca){
    for (int i = 0; i < HASH_SIZE; ++i) {
        if(hashTable[i] != NULL) {
            float tier_cost = 0;
            struct SymbolEntry *tmp = hashTable[i];
            while(tmp != NULL) {
                int tier = tmp->info->last_read - tmp->info->first_read;
                struct Fascia *fcurr = fascie;
                while(fcurr != NULL){
                    if(tier <= fcurr->limite_superiore && tier >= fcurr->limite_inferiore){
                        tier_cost = tier*fcurr->costo_mc;
                    }
                    fcurr = fcurr->next;
                }
                float total = tier_cost + (tier * ca->costo_elettricita) + (tier * ca->canone_fognatura) + ca->nolo_contatore;
                float iva = total*(ca->iva/100.0);
                tmp->info->total = total + iva;
                tmp = tmp->next;
            }
        }
    }
}

void print_total(){
    for (int i = 0; i < HASH_SIZE; ++i) {
        if(hashTable[i] != NULL) {
            struct SymbolEntry *tmp = hashTable[i];
            while(tmp != NULL) {
                printf("%s ->  %.2f\n", tmp->info->name, tmp->info->total);
                tmp = tmp->next;
            }
        }
    }
}