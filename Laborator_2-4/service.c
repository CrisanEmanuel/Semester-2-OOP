#include "service.h"
#include "validate.h"
#include <string.h>
#include <stdlib.h>

/**
 * Create and validate an offer, if is valid, the offer will be added to the list
 */
int addOffer(MyList *l, char *type, float area, char *address, float price){
    Offer o = createOffer(type, area, address, price);

    int var = validate(o);
    if (var != 0) {
        destroyOffer(&o);
        return var;
    }

    add(l, o);
    return 0; // all ok
}
/**
 * Functie care sterge o oferta
 * Returneaza 0 daca oferta a fost stearsa, -1 in caz contrar
 */
int sterge_oferta_service(MyList *list, char *tip, char *adresa) {
    return sterge_oferta_repo(list, tip, adresa);
}

/**
 * Functia returneaza valoarea 0 daca entitatea a fost gasita si updatata sau valoarea -1 daca entitatea nu exista
 */
int actualizeaza_oferta_service(MyList *l,char *type, char *address, char *new_type, float new_area, char *new_address, float new_price){
    int var;
    ElemType el = createOffer(new_type, new_area, new_address, new_price);
    var = actualizeaza_oferta_repo(l, type, address, el);

    if (var == 0){
        return var;
    }else {
        destroyOffer(&el);
        return var;
    }
}

/**
 * Ordoneaza ofertele din lista dupa pret crescator iar in caz ca preturile sunt egale, se ordoneaza dupa tip crescator
 */
MyList sortare_dupa_pret_tip_service(MyList L){
    MyList l = copyList(&L);
    for(int i = 0; i < l.length - 1; i++) {
        for (int j = i+1; j < l.length; j++) {
            Offer o1 = get(&l, i);
            Offer o2 = get(&l, j);
            if(o1.price > o2.price){
                set(&l,i,o2);
                set(&l,j,o1);
            }else if(o1.price == o2.price){
                if(strcmp(o1.type, o2.type) >= 0){
                    set(&l,i,o2);
                    set(&l,j,o1);
                }
            }
        }
    }
    return l;
}

MyList filtrare_dupa_criteriu_service(MyList l, char filtru[], char param[]){
    MyList lista_filtrata = createEmpty();
    if (strcmp(filtru, "tip") == 0){
        for (int i = 0; i < l.length; i++){
            Offer o = get(&l, i);
            if (strstr(o.type, param) != NULL){
                Offer new = copyOffer(&o);
                add(&lista_filtrata, new);
            }
        }
    }else if (strcmp(filtru, "suprafata") == 0){
        float suprafata = strtof(param, NULL);
        for (int i = 0; i < l.length; i++){
            Offer  o = get(&l, i);
            if (o.area == suprafata){
                Offer new = copyOffer(&o);
                add(&lista_filtrata, new);
            }
        }
    }else if (strcmp(filtru, "pret") == 0){
        float pret = strtof(param, NULL);
        for (int i = 0; i < l.length; i++){
            Offer o = get(&l, i);
            if (o.price == pret){
                Offer new = copyOffer(&o);
                add(&lista_filtrata, new);
            }
        }
    }
    return lista_filtrata;
}