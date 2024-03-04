#pragma once
#include "repository.h"
#include "service.h"
#include "exceptions.h"
#include <cassert>
#include <iostream>
#include "domain.h"

class Tests {

public:

    static void runAllTeste();

    static void testeDomain();

    static void testeRepo();

    static void testeService();

    static void testeValidare();

    static void testeCreareContract();

    static void testeUndo();
};

