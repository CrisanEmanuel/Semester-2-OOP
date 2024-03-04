#pragma once
#include "repository.h"
#include "service.h"

class Tests {

public:

    static void runAllTeste();

    static void testeDomain();

    static void testeRepo();

    static void testeService();

    static void testeValidare();

    static void testeVectorDinamicT();

    static void testeVectorDinamicTdiscipline();
};

template<typename MyVector>
void testAll();
