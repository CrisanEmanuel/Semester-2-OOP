#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "domain.h"
#include "service.h"

void meniu(){
    printf("---------- MENIU ----------\n");
    printf("1.Adauga oferta\n");
    printf("2.Actualizeaza oferta\n");
    printf("3.Sterge oferta\n");
    printf("4.Ordonare oferte dupa pret, tip\n");
    printf("5.Filtrare oferte dupa criteriu (suprafata/tip/pret)\n");
}

void adauga_oferta(MyList *l){
    printf("Type:");
    char type[30];
    scanf("%s", type);

    printf("Area:");
    float area;  char aux[30];
    scanf("%s", aux);
    area = strtof(aux, NULL); // strtof transforma stringul citit in float

    printf("Address:");
    char address[30];
    scanf("%s", address);

    printf("Price:");
    float price;
    scanf("%s", aux);
    price = strtof(aux, NULL);

    int error = addOffer(l, type, area, address, price);
    if(error !=0){
        printf("Invalid offer!\n");

    }
    else {
        printf("Offer added!\n");
    }
}

void sterge_oferta(MyList *l) {
    char tip[20], adresa[20];
    printf("Dati tipul ofertei:");
    scanf("%s", tip);
    printf("Dati adresa ofertei:");
    scanf("%s", adresa);
    int ver = sterge_oferta_service(l, tip, adresa);
    if (ver == 0) {
        printf("Oferta stearsa cu succes!\n");
    }else {
        printf("Oferta indicata nu exista!\n");
    }
}

void actualizeaza_oferta(MyList *l){
    char type[30], address[30];

    printf("Alegeti oferta pentru actualizare(tip/adresa)\n");

    printf("Dati tip:");
    scanf("%s", type);

    printf("Dati adresa:");
    scanf("%s", address);

    char new_type[30], new_address[30], aux[30];
    float new_area, new_price;

    printf("Dati tip nou:");
    scanf("%s", new_type);

    printf("Dati suprafata noua:");
    scanf("%s",aux);
    new_area = strtof(aux, NULL);

    printf("Dati adresa noua:");
    scanf("%s", new_address);

    printf("Dati pret nou:");
    scanf("%s", aux);
    new_price = strtof(aux, NULL);

    actualizeaza_oferta_service(l, type, address, new_type, new_area, new_address, new_price);

}

void sortare_dupa_pret_tip(MyList l) {
    MyList lista_sortata = sortare_dupa_pret_tip_service(l);
    printf("Lista ordonata este:\n");
    for(int i = 0; i < lista_sortata.length; i++){
        Offer o = get(&lista_sortata, i);
        printf("%s %.2f %s %.2f\n", o.type, o.area, o.address, o.price);
    }
    destroy(&lista_sortata);
}


void filtrare_dupa_criteriu(MyList l){
    printf("Alegeti criteriul(suprafata/tip/pret):\n");
    char filtru[30];
    scanf("%s", filtru);
    if (strcmp(filtru, "suprafata") != 0 && strcmp(filtru, "tip") != 0 && strcmp(filtru, "pret") != 0){
        printf("Filtru invalid!");
    }

    if(strcmp(filtru, "suprafata") == 0){
        char aux[30];
        printf("Alegeti suprafata:\n");
        scanf("%s", aux);
        MyList lista_filtrata = filtrare_dupa_criteriu_service(l, filtru, aux);

        printf("Lista filtrata dupa %s este:\n", filtru);
        for(int i = 0; i < lista_filtrata.length; i++){
            Offer o = get(&lista_filtrata, i);
            printf("%s %.2f %s %.2f\n", o.type, o.area, o.address, o.price);
        }
        destroy(&lista_filtrata);
    }

    if(strcmp(filtru, "tip") == 0){
        char aux[30];
        printf("Alegeti tipul:\n");
        scanf("%s", aux);
        MyList lista_filtrata = filtrare_dupa_criteriu_service(l, filtru, aux);

        printf("Lista filtrata dupa %s este:\n", filtru);
        for(int i = 0; i < lista_filtrata.length; i++){
            Offer o = get(&lista_filtrata, i);
            printf("%s %.2f %s %.2f\n", o.type, o.area, o.address, o.price);
        }
        destroy(&lista_filtrata);
    }

    if(strcmp(filtru, "pret") == 0){
        char aux[30];
        printf("Alegeti pretul:\n");
        scanf("%s", aux);
        MyList lista_filtrata = filtrare_dupa_criteriu_service(l, filtru, aux);

        printf("Lista filtrata dupa %s este:\n", filtru);
        for(int i = 0; i < lista_filtrata.length; i++){
            Offer o = get(&lista_filtrata, i);
            printf("%s %.2f %s %.2f\n", o.type, o.area, o.address, o.price);
        }
        destroy(&lista_filtrata);
    }
}

void printAllOffers(MyList *l){
    printf("Toate ofertele valabile:\n");\
    for(int i = 0; i < size(l); i++){
        Offer o = get(l, i);
        printf("%s %.2f %s %.2f\n", o.type, o.area, o.address, o.price);
    }
}

void run(){
    MyList  allOffers = createEmpty();
    int ruleaza = 1, comanda;
    char aux[30];
    while(ruleaza){
        printf(">>>");
        scanf("%s", aux);
        comanda = strtol(aux, NULL, 10); // strtol converteste un string in int
        switch(comanda){
            case 1:
                adauga_oferta(&allOffers);
                break;
            case 2:
                actualizeaza_oferta(&allOffers);
                break;
            case 3:
                sterge_oferta(&allOffers);
                break;
            case 4:
                sortare_dupa_pret_tip(allOffers);
                break;
            case 5:
                filtrare_dupa_criteriu(allOffers);
                break;
            case 6:
                printAllOffers(&allOffers);
                break;
            case 0:
                ruleaza = 0;
                break;
            default:
                printf("Comanda invalida!\n");
        }
    }
    destroy(&allOffers);
}