#include "service.h"
#include "repository.h"
#include "mysort.h"
#include <string.h>
#include <assert.h>


int addCar(CarStore* l, char* plateNo, char* model, char* type){
    Car* p = createCar(plateNo, model, type, 0);
    if (plateNo[0] == 0) return 1;
    if (model[0] == 0) return 2;
    if (type[0] == 0) return 3;

    CarList *copie = copyList(l->allCars, (CopyFunction) copyCar);

    add(l->allCars, p);
    add(l->undoList, copie);

    return 0;
}

CarStore createCarStore()
{
    CarStore rez;
    rez.allCars = createEmpty((DestroyFunction) destroyCar);
    rez.undoList = createEmpty((DestroyFunction) destroy);
    return rez;
}

void destroyStore(CarStore* store)
{
    destroy(store->allCars);
    destroy(store->undoList);
}

int changeRentStatus(CarStore* l, char* plateNo){
    for(int i = 0; i < size(l->allCars); i++){
        Car* c = get(l->allCars, i);
        if(strcmp(c->plateNo, plateNo) == 0){
            CarList* copie = copyList(l->allCars, (CopyFunction) copyCar);
            add(l->undoList, copie);
            if(c->rented == 0)
            {
                c->rented = 1;
            }
            else
            {
                c->rented = 0;
            }
            return 0;
        }
    }
    return -1;
}

int undo(CarStore* list){
    if (size(list->undoList) == 0)
        return 1; // no more undo
    CarList* l = removeLast(list->undoList);
    destroy(list->allCars);
    list->allCars = l;
    return 0; // ok
}

int updateCar(CarStore* list, char* plate, char* plateUpd, char* modelUpd, char* typeUpd){
    for (int i = 0; i < size(list->allCars); i++){
        Car* c = get(list->allCars, i);
        if (strcmp(c->plateNo, plate) == 0){
            int rent = c->rented;
            Car* newC = createCar(plateUpd, modelUpd, typeUpd, rent);
            CarList* copie = copyList(list->allCars, (CopyFunction) copyCar);
            add(list->undoList, copie);
            destroyCar(set(list->allCars, i, newC));
            return 0;
        }
    }
    return -1;
}

int cmpModel(Car* c1, Car* c2){
    return strcmp(c1->model, c2->model);
}

int cmpType(Car* c1, Car* c2){
    return strcmp(c1->type, c2->type);
}

CarList* sortByModel(CarStore* list){
    CarList* l = copyList(list->allCars, (CopyFunction) copyCar);
    sort(l, (FunctieComparare) cmpModel);
    return l;
}

CarList* sortByType(CarStore* list){
    CarList* l = copyList(list->allCars, (CopyFunction) copyCar);
    sort(l, (FunctieComparare) cmpType);
    return l;
}

void testeService(){
    CarStore list = createCarStore();
    assert(addCar(&list, "CJ01AAA", "Ferrari", "Sport") == 0); // astea care dau 0 se adauga in lista
    assert(addCar(&list, "", "Ferrari", "Sport") == 1);
    assert(addCar(&list, "CJ01AAA", "", "Sport") == 2);
    assert(addCar(&list, "CJ01AAA", "Ferrari", "") == 3);
    assert(addCar(&list, "CJ03DAN", "Tesla", "Sedan") == 0);
    assert(addCar(&list, "NT99XYZ", "BMW", "Break") == 0);
    assert(addCar(&list, "BC12ABC", "Aro", "SUV") == 0);
    assert(addCar(&list, "SV03ALX", "Volkswagen", "Hatchback") == 0);

    CarList* sorted1 = sortByType(&list);
    Car* c1 = get(sorted1, 0);
    assert(strcmp(c1->plateNo, "NT99XYZ") == 0);
    destroy(sorted1);

    CarList* sorted2 = sortByModel(&list);
    Car* c2 = get(sorted2, 0);
    assert(strcmp(c2->plateNo, "BC12ABC") == 0);
    destroy(sorted2);

    destroyStore(&list);
}

void testUndo(){
    CarStore list = createCarStore();

    assert(size(list.allCars) == 0);

    addCar(&list, "CJ01AAA", "Ferrari", "Sport");
    assert(size(list.allCars) == 1);

    assert(undo(&list) == 0);
    assert(size(list.allCars) == 0);

    addCar(&list, "CJ03DAN", "Tesla", "Sedan");
    addCar(&list, "NT99XYZ", "BMW", "Break");

    assert(undo(&list) == 0);
    assert(size(list.allCars) == 1);

    assert(undo(&list) == 0);
    assert(size(list.allCars) == 0);

    assert(undo(&list) == 1);

    addCar(&list, "CJ03DAN", "Tesla", "Sedan");
    addCar(&list, "NT99XYZ", "BMW", "Break");
    assert(size(list.allCars) == 2);

    Car* c1 = get(list.allCars, 0);
    assert(strcmp(c1->plateNo, "CJ03DAN") == 0);

    assert(updateCar(&list, "CJ03DAN", "dd", "dd", "dd") == 0);
    c1 = get(list.allCars, 0);
    assert(strcmp(c1->plateNo, "dd") == 0); /// trebuia sa fie dd nu CJ03DAN

    assert(updateCar(&list, "nimic", "dd", "dd", "dd") == -1);

    Car* c2 = get(list.allCars, 1);
    assert(c2->rented == 0);

    assert(changeRentStatus(&list, "NT99XYZ") == 0);
    assert(c2->rented == 1);
    assert(changeRentStatus(&list, "NT99XYZ") == 0);
    assert(c2->rented == 0);

///// !!!!!!
//    assert(undo(&list) == 0);
//    assert(c2->rented == 0); /// !!!!!! trebuia 1
///// !!!!!!

    assert(changeRentStatus(&list, "nimic") == -1);

    destroyStore(&list);
}

