#pragma once
#include "domain.h"
#include "exceptions.h"

class Validare {
public:
    // valideaza un task
    static void validate(const Task& task);
};
