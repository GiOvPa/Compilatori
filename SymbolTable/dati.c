#include "dati.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void insertFascia(struct Fascia **fasce, int tier, float ls, float li, float costo){
    struct Fascia *nw = malloc(sizeof(struct Fascia));
    nw->tier = tier;
    nw->costo_mc = costo;
    nw->limite_inferiore = li;
    nw->limite_superiore = ls;
    nw->next = *fasce;
    *fasce = nw;
}

int checkRegularValue(struct Fascia *fasce, float li, float ls, int t){
    if (fasce == NULL) return 1;
    else{   
        struct Fascia *prev = fasce;
        struct Fascia *nex = fasce;
        while(prev->tier != t-1 && prev->next != NULL) prev = prev->next;
        while(nex->tier != t+1 && nex->next != NULL) nex = nex->next;
        if(prev->tier == t-1){
            if (fabs(prev->limite_superiore - li) < 0.0001) return 1;
            else return 0;
        }if (nex->tier == t+1){
            if (fabs(nex->limite_inferiore - ls) < 0.0001) return 1;
            else return 0;
        }
    }
}

void insertCanoneFognatura(Costi_aggiuntivi **costi_a, float cf){
    if(*costi_a != NULL) (*costi_a)->canone_fognatura = cf;
    else{
        (*costi_a) = malloc(sizeof(Costi_aggiuntivi));
        (*costi_a)->canone_fognatura = cf;
        (*costi_a)->costo_elettricita = 0.0;
        (*costi_a)->iva = 0;
        (*costi_a)->nolo_contatore = 0.0;
    }
}

void insertCostoEnergiaElettrica(Costi_aggiuntivi **costi_a, float ce){
        if(*costi_a != NULL)(*costi_a)->costo_elettricita = ce;
    else{
        (*costi_a) = malloc(sizeof(Costi_aggiuntivi));
        (*costi_a)->canone_fognatura = 0.0;
        (*costi_a)->costo_elettricita = ce;
        (*costi_a)->iva = 0;
        (*costi_a)->nolo_contatore = 0.0;
    }
}
void insertNoloContatore(Costi_aggiuntivi **costi_a, float nc){
        if(*costi_a != NULL)(*costi_a)->nolo_contatore = nc;
    else{
        (*costi_a) = malloc(sizeof(Costi_aggiuntivi));
        (*costi_a)->canone_fognatura = 0.0;
        (*costi_a)->costo_elettricita = 0.0;
        (*costi_a)->iva = 0;
        (*costi_a)->nolo_contatore = nc;
    }
}

void insertIVA(Costi_aggiuntivi **costi_a, float iva){
    if((*costi_a) != NULL)(*costi_a)->iva = iva;
    else{
        (*costi_a) = malloc(sizeof(Costi_aggiuntivi));
        (*costi_a)->canone_fognatura = 0.0;
        (*costi_a)->costo_elettricita = 0.0;
        (*costi_a)->iva = iva;
        (*costi_a)->nolo_contatore = 0.0;
    }
}

void printFasce(struct Fascia *fasce){
    while(fasce != NULL){
        printf("Tier = %d, Lsup = %.2f, Linf = %.2f, Costo = %.2f\n", fasce->tier, fasce->limite_superiore, fasce->limite_inferiore, fasce->costo_mc);
        fasce = fasce->next;
    }
}

void printCosti(Costi_aggiuntivi *costi){
    printf("Fogna = %.2f, Ele = %.2f, IVA = %.2f, Nolo = %.2f\n", costi->canone_fognatura, costi->costo_elettricita, costi->iva, costi->nolo_contatore);
}