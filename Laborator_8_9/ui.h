#pragma once
#include "service.h"
#include "exceptions.h"
#include <iostream>
#include <algorithm>

class Ui {
    Service &service;

    void addUi();

    void deleteUi();

    void updateUi();

    static void printUi(const vector<Disciplina>& discipline);

    void searchUi();

    void filterUi();

    void sortUi();

public:
    explicit Ui(Service &service) :service { service }{}

    static void menu();

    void runUi();

    void createContractUi();

    void emptyContractUi();

    void generateContractUi();

    void printContractUi(const vector<Disciplina>& discipline);

    void funcNoua();

    void exportToFileUi();

    void undoUi();
};