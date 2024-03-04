#include "domain.h"
#include "repository.h"
#include <stdlib.h>
#include <assert.h>

//creare lista goala
CarList* createEmpty(DestroyFunction destf){
    CarList* rez = malloc(sizeof(CarList));
    rez->lg = 0;
    rez->cap = 2;
    rez->elems = malloc(sizeof(Car) * rez->cap);
    rez->destf = destf;
    return rez;
}

void destroy(CarList* l){
    for (int i = 0; i < l->lg; i++){
        l->destf(l->elems[i]);
    }
    free(l->elems);
    free(l);
}

ElemType get(CarList* l, int poz){
    return l->elems[poz];
}

ElemType set(CarList* l, int poz, Car* c){
    ElemType rez = l->elems[poz];
    l->elems[poz] = c;
    return rez;
}

int size(CarList* l){
    return l->lg;
}

//asigurare capacitate, 0 daca nu exista spatiu si 1 altfel
void ensureCapacity(CarList* l){
    if (l->lg < l->cap) return;

    //alocare memorie
    ElemType* nElems = malloc(sizeof(ElemType) * (l->cap + 2));

    //copiere elemente
    for (int i = 0; i < l->lg; i++)
        nElems[i] = l->elems[i];

    //dealocare tablou vechi
    free(l->elems);
    l->elems = nElems;
    l->cap += 2;
}

//adauga masina la lista
void add(CarList* l, ElemType el){
    ensureCapacity(l);
    l->elems[l->lg] = el;
    l->lg++;
}

CarList* copyList(CarList* l, CopyFunction cf) {
    CarList* rez = createEmpty(l->destf);
    for (int i = 0; i < size(l); i++){
        ElemType c = get(l, i);
        add(rez, cf(c));
    }
    return rez;
}

ElemType removeLast(CarList* l){
    ElemType rez = l->elems[l->lg - 1];
    l->lg -= 1;
    return rez;
}

void testeLista() {
    CarList* store = createEmpty((DestroyFunction) destroyCar);
    CarList* l = createEmpty((DestroyFunction) destroyCar);
    assert(size(l) == 0);
    add(store, createCar("B100LYA", "Ford", "Break", 0));
    assert(size(store) == 1);
    destroy(store);
    destroy(l);
}

void testListeDeListe() {
    CarList* myCars1 = createEmpty((DestroyFunction) destroyCar);
    add(myCars1, createCar("ab45rtl", "aaa", "dfgh", 0) );
    add(myCars1, createCar("ab55der", "bbb", "qwer", 0) );

    CarList* myCars2 = createEmpty((DestroyFunction) destroyCar);
    CarList* undoL = createEmpty((DestroyFunction) destroyCar);

    add(undoL, myCars1);
    assert(size(undoL) == 1);

    add(undoL, myCars2);
    assert(size(undoL) == 2);

    destroy(myCars1);
    destroy(myCars2);
}

