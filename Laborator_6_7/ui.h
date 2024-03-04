#pragma once
#include "service.h"

class Ui {
    Service &service;

    void addUi();

    void deleteUi();

    void updateUi();

    static void printUi(const VectDinNewDeleteT<Disciplina> &discipline);

    void searchUi();

    void filterUi();

    void sortUi();

public:
    explicit Ui(Service &service) :service { service }{}

    static void menu();

    void runUi();
};