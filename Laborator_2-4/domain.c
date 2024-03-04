#include "domain.h"
#include <stdlib.h>
#include <string.h>

Offer createOffer(char *type, float area, char *address, float price){
    Offer rez;

    unsigned long long nr_caractere = strlen(type) + 1;
    rez.type = malloc(nr_caractere * sizeof(char));
    strcpy(rez.type, type);

    rez.area = area;

    nr_caractere = strlen(address) + 1;
    rez.address = malloc(nr_caractere * sizeof(char));
    strcpy(rez.address, address);

    rez.price = price;

    
    return rez;
}

void destroyOffer(Offer *o){
    free(o -> type);
    free(o -> address);
    //no memory is allocated on the heap
    //nothing to deallocate
    //mark that offer is destroyed, avoid accidental use after destroy
    o -> area = -1;
    o -> price = -1;
}

int eq(Offer o, Offer other){
    if(strcmp(o.type, other.type) == 0 && strcmp(o.address, other.address) == 0 && (o.price == other.price) && (o.area == other.area))
        return 1;
    return 0;
}