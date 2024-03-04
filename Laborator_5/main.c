#include "domain.h"
#include "service.h"
#include <stdio.h>
#include <stdlib.h>

void readCar(CarStore* list){
    printf("Plate:");
    char plate[30];
    scanf("%s", plate);

    printf("Model:");
    char model[30];
    scanf("%s", model);

    printf("Type:");
    char type[30];
    scanf("%s", type);

    int error = addCar(list, plate, model, type);
    if (error != 0)
        printf("Invalid.\n");
    else
        printf("Car added.\n");
}

//print toate masinile, cu toate criteriile
void printAllCars (CarList* l){
    printf("Cars:\n");
    for (int i = 0; i < size(l); i++) {
        Car* p = get(l, i);
        printf("plateNo:%s Model:%s Category:%s Rented: %d\n", p->plateNo, p->model, p->type, p->rented);
    }
}

int updateCarUi(CarStore* list){
    char plate[30];
    printf("Plate:");
    scanf("%s", plate);

    char plateUpd[30];
    printf("Updated plate:");
    scanf("%s", plateUpd);

    char modelUpd[30];
    printf("Updated model:");
    scanf("%s", modelUpd);

    char typeUpd[30];
    printf("Updated type:");
    scanf("%s", typeUpd);

    return updateCar(list, plate, plateUpd, modelUpd, typeUpd);
}

int changeRentStatusUi(CarStore* list){
    printf("Plate:");

    char plateNo[30];
    scanf("%s", plateNo);
    return changeRentStatus(list, plateNo);
}

void meniu(){
    printf("1) Add\n");
    printf("2) Update\n");
    printf("3) Rent/return car\n");
    printf("4) Sort by model\n");
    printf("5) Sort by type\n");
    printf("6) Undo\n");
    printf("7) Show all\n");

}

void run_ui(){
    CarStore list = createCarStore();
    CarList *sorted;
    int ruleaza = 1;
    while (ruleaza)
    {
        char aux[30];
        int cmd;
        printf(">>>");
        scanf("%s", aux);
        cmd = strtol(aux, NULL, 10);
        switch (cmd)
        {
            case 1:
                readCar(&list);
                break;
            case 2:
                if(updateCarUi(&list) == -1){
                    printf("Car not found!\n");
                }
                break;
            case 3:
                if(changeRentStatusUi(&list) == -1){
                    printf("Car not found!\n");
                }
                break;
            case 4:
                sorted = sortByModel(&list);
                printAllCars(sorted);
                destroy(sorted);
                break;
            case 5:
                sorted = sortByType(&list);
                printAllCars(sorted);
                destroy(sorted);
                break;
            case 6:
                if (undo(&list) == 1) printf("No more undo!\n");
                break;
            case 7:
                printAllCars(list.allCars);
                break;
            case 0:
                ruleaza = 0;
                break;
            default:
                printf("Comanda invalida! Incercati din nou\n");
        }
    }
    destroyStore(&list);
}

int main(){
    testeService();
    testeMasina();
    testeLista();
    testListeDeListe();
    testUndo();
    meniu();
    run_ui();
    return 0;
}