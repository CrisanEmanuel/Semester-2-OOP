#pragma once
#include "repository.h"

typedef struct {
    CarList* allCars;
    CarList* undoList;
} CarStore;

CarStore createCarStore();

void destroyStore(CarStore* store);

int addCar(CarStore* store, char* plateNo, char* model, char* category);

/**
* Se modifica statutul masinii (inchiriat/disponibil)
* Se returneaza un nou obiect tip Car
*/
int changeRentStatus(CarStore* l, char* plateNo);

int undo(CarStore* list);

CarList* sortByModel(CarStore* list);

CarList* sortByType(CarStore* list);

int cmpType(Car* c1, Car* c2);

int cmpModel(Car* c1, Car* c2);

int updateCar(CarStore* list, char* plate, char* plateUpd, char* modelUpd, char* typeUpd);

void testeService();

void testUndo();
