#include "repo.h"
#include <stdlib.h>
#include <string.h>

MyList createEmpty(){
    MyList rez;
    rez.capacitate = 1;
    rez.elems = malloc(sizeof(Offer) * rez.capacitate);
    rez.length = 0;
    return rez;
}

void destroy(MyList *l){
    for (int i = 0; i < l -> length; i++){
        ElemType o = l -> elems[i];
        destroyOffer(&o);
    }
    //nothing to deallocate for now
    l -> length = 0;
    free(l -> elems);
}

ElemType get(MyList *l, int poz){
    return l -> elems[poz];
}

ElemType set(MyList *l, int poz, ElemType el) {
    ElemType rez = l -> elems[poz];
    l -> elems[poz] = el;
    return rez;
}

int size(MyList *l){
    return l -> length;
}

Offer copyOffer(Offer *o){
    return createOffer(o->type, o->area, o->address, o->price);
}

void add(MyList *l, ElemType el){
    if (l -> capacitate <= l -> length){
        //sa alocam un spatiu mai mare
        ElemType* aux = malloc(sizeof(ElemType) * (l -> capacitate + 1));
        //copiem elementele
        for (int i = 0; i < l -> length; i++){
            aux[i] = l -> elems[i];
        }
        free(l -> elems);
        l -> elems = aux;
        l -> capacitate += 1;
    }
    l -> elems[l -> length] = el;
    l -> length++;
}


MyList copyList(MyList* l) {
    MyList rez = createEmpty();
    for (int i = 0; i < size(l); i++) {
        ElemType o = get(l, i);
        add(&rez, createOffer(o.type, o.area, o.address, o.price));
    }
    return rez;
}

int sterge_oferta_repo(MyList *l, char *tip, char *adresa){
    int i = 0;
    while(i < l -> length){
        Offer o = get(l, i);
        if (strcmp(tip, o.type) == 0 && strcmp(adresa, o.address) == 0) {
                destroyOffer(&o);
                for (int j = i; j < l -> length - 1; j++)
                    l -> elems[j] = l -> elems[j + 1];
                l -> length -= 1;
                return 0;
        }
        i++;
    }
    return -1;
}

int actualizeaza_oferta_repo(MyList *l, char *type, char *address, ElemType el){
    for (int i = 0; i < l -> length; i++) {
        Offer o = get(l, i);
        if (strcmp(type, o.type) == 0 && strcmp(address, o.address) == 0){
            Offer rez = set(l,i,el);
            destroyOffer(&rez);
            return 0;
        }
    }
    return -1;
}
