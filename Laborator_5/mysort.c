#include "mysort.h"

void sort(CarList* l, FunctieComparare cmpF){
    for(int i = 0; i < size(l); i++){
        for(int j = i + 1; j < size(l); j++){
            void* elem1 = get(l,i);
            void* elem2 = get(l, j);
            if(cmpF(elem1, elem2) > 0){
                set(l, i, elem2);
                set(l, j, elem1);
            }
        }
    }
}