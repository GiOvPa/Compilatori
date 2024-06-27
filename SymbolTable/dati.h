#ifndef DATI_H
#define DATI_H

typedef struct {
    float costo_elettricita;
    float canone_fognatura;
    float nolo_contatore;
    float iva;
} Costi_aggiuntivi;


struct Fascia{
    int tier;
    float limite_inferiore;
    float limite_superiore;
    float costo_mc;
    struct Fascia *next;
};

void insertFascia(struct Fascia **fasce, int tier, float ls, float li, float costo);
void insertCanoneFognatura(Costi_aggiuntivi **costi_a, float cf);
void insertCostoEnergiaElettrica(Costi_aggiuntivi **costi_a, float ce);
void insertNoloContatore(Costi_aggiuntivi **costi_a, float nc);
void insertIVA(Costi_aggiuntivi **costi_a, float iva);
void printFasce(struct Fascia *fasce);
void printCosti(Costi_aggiuntivi *costi);
int checkRegularValue(struct Fascia *fasce, float li, float ls, int t);

#endif 