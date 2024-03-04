#pragma once
#include "repo.h"
#include "service.h"

void meniu();

void adauga_oferta(MyList *l);

/**
 * Sterge oferta identificata dupa tip si adresa
 */
void sterge_oferta(MyList *l);

/**
 * Actualizeaza oferta identificata dupa tip si adresa
 */
void actualizeaza_oferta(MyList *l);


/**
 * Sorteaza ofertele dupa pret, in caz de egalitate la pret sorteaza dupa tip
 */
void sortare_dupa_pret_tip(MyList l);


/**
 * Filtreaza lista de oferte dupa un criteriu
 */
void filtrare_dupa_criteriu(MyList l);

void printAllOffers(MyList *l);

void run();
