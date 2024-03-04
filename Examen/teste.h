#pragma once
#include <cassert>
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validare.h"
class Tests {
public:
    // se apeleaza toate testele
    static void test_all();

    // se testeaza metodele din repository
    static void test_repo();

    // se testeaza  metodele din domain
    static void test_domain();

    // se testeaza metodele din service
    static void test_service();

    // se testeaza validarea
    static void test_validare();
};