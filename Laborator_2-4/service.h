#pragma once
#include "repo.h"

/**
 * Add an offer to the list of offers
 */
int addOffer(MyList *l, char *type, float area, char *address, float price);

/**
 * Functie care sterge o oferta
 * Returneaza 0 daca oferta a fost stearsa, -1 in caz contrar
 */
int sterge_oferta_service(MyList *list, char *tip, char *adresa);

/**
 * Functia returneaza valoarea 0 daca entitatea a fost gasita si updatata sau valoarea -1 daca entitatea nu exista
 */
int actualizeaza_oferta_service(MyList *l,char *type, char *address, char *new_type, float new_area, char *new_address,
                                 float new_price);

/**
 * Ordoneaza ofertele din lista dupa pret crescator iar in caz ca preturile sunt egale, se ordoneaza dupa tip crescator
 */
MyList sortare_dupa_pret_tip_service(MyList l);

/**
 * Filtreaza ofertele
 */
MyList filtrare_dupa_criteriu_service(MyList l, char filtru[], char param[]);