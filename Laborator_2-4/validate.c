#include "validate.h"
#include "domain.h"
#include <string.h>

int validate(Offer o){
    if(strlen(o.type) == 0){
        return 1;
    }
    if(o.area < 0){
        return 2;
    }
    if(strlen(o.address) == 0){
        return 3;
    }
    if(o.price < 0){
        return 4;
    }
    return 0;
}
