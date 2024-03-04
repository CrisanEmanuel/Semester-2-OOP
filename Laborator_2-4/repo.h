#pragma once
#include "domain.h"

typedef Offer ElemType;

typedef struct {
    ElemType* elems;
    int length;
    int capacitate;
}MyList;

/**
 * Create an empty list
 */
MyList createEmpty();

/**
 * Destroy list
 */
void destroy(MyList *l);

/**
 * get an element from the list
 * poz - position of the element
 * return element on the given position
 */
ElemType get(MyList *l, int poz);

/**
 * Inocuieste in lista l de oferte, oferta de pe pozitia poz cu noul element, el
 */
ElemType set(MyList *l, int poz, ElemType el);


/**
 * Return the number of elements in the list
 */
int size(MyList *l);

Offer copyOffer(Offer *o);

/**
 * Add element into the list
 * Post: element is added to the end of the list
 */
void add(MyList *l, ElemType el);

/**
 * Make a shallow copy of the list
 * return MyList containing the same elements as l
*/
MyList copyList(MyList *l);

/**
 * Sterge o oferta
 */
int sterge_oferta_repo(MyList *list, char *tip, char *adresa);

/**
 * Functie care face update la o oferta. Primeste un pointer la oferta cu caracteristicile actualizate, distruge oferta
 veche si o pune pe cea actualizata
*/
int actualizeaza_oferta_repo(MyList *l, char *type, char *address, ElemType el);