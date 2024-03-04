#pragma once

typedef struct {
    char* plateNo;
    char* model;
    char* type;
    int rented;
} Car;

Car* createCar(char* plateNo, char* model, char* category, int rent);

void destroyCar(Car* p);

Car* copyCar(Car* p);

void testeMasina();
