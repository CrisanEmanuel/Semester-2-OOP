#pragma once
#include "domain.h"

typedef void* ElemType;

typedef void(*DestroyFunction) (ElemType);

typedef ElemType (*CopyFunction) (ElemType);

typedef struct
{
    ElemType* elems;
    int lg; //length
    int cap; //capacity
    DestroyFunction destf;
}CarList;


CarList* createEmpty(DestroyFunction destf);

//distruge lista
void destroy(CarList* l);

void add(CarList* l, ElemType el);

CarList* copyList(CarList* l, CopyFunction cp);

void ensureCapacity(CarList* l);

ElemType removeLast(CarList* l);

ElemType get(CarList* l, int poz);

/**
  Modifica elementul de pe poz data
  Se returneaza elementul nou
*/
ElemType set(CarList* l, int poz, Car* c);

int size(CarList* l);

void testeLista();

void testListeDeListe();