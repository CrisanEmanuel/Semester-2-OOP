#pragma once

#include "repository.h"

/**
 * Tipul functiei de comparare pentru 2 elemente
 * returneaza: - 0 daca sunt egale,
 *             - 1 daca elem1 > elem2,
 *             - -1 altfel
 */
typedef int(*FunctieComparare)(void* elem1, void* elem2);

/**
 * Sorteaza in place
 * cmpF - relatia dupa care se sorteaza
 */

void sort(CarList* l, FunctieComparare cmpF);