#include "domain.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

Car* createCar(char* plateNo, char* model, char* type, int rent){
    Car* rez = malloc(sizeof(Car));

    size_t nrC = strlen(plateNo) + 1;
    rez->plateNo = malloc(sizeof(char) * nrC);
    if (rez->plateNo != 0)
        strcpy(rez->plateNo, plateNo);

    nrC = strlen(model) + 1;
    rez->model = malloc(sizeof(char) * nrC);
    if (rez->model != 0)
        strcpy(rez->model, model);

    nrC = strlen(type) + 1;
    rez->type = malloc(sizeof(char) * nrC);
    if (rez->type != 0)
        strcpy(rez->type, type);

    rez->rented = rent;

    return rez;
}

void destroyCar(Car* c){
    free(c->plateNo);
    free(c->type);
    free(c->model);
    free(c);
}

Car* copyCar(Car* p){
    return createCar(p->plateNo, p->model, p->type, p->rented);
}

void testeMasina(){
    Car* p = createCar("NT46DAN", "Skoda", "cazan", 0);
    assert(strcmp(p->plateNo, "NT46DAN") == 0);
    assert(strcmp(p->model, "Skoda") == 0);
    assert(strcmp(p->type, "cazan") == 0);
    assert(p->rented == 0);

    destroyCar(p);
}
