#include "tests.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void runAll(){
    testsDomain();
    testsRepo();
    testsService();

    testeActualizareService();

    testeFiltrareService();

    testeSortareService();

    testeStergereService();

    printf("All tests passed!\n");
}

void testsDomain(){
    Offer o = createOffer("casa", 150,"Inului", 120000);
    assert(strcmp(o.type, "casa") == 0);
    assert(strcmp(o.address, "Inului") == 0);
    assert(o.price == 120000);
    assert(o.area == 150);

    destroyOffer(&o);
    assert(o.price = -1);
    assert(o.area = -1);
}

void testsRepo(){
    MyList l1 = createEmpty();
    add(&l1, createOffer("teren",2400,"Ciresului",90000));
    add(&l1, createOffer("apartament",400,"Arghezi",8900));
    MyList l2 = copyList(&l1);
    assert(size(&l1) == 2);
    assert(size(&l2) == 2);

    Offer o =  get(&l1, 0);
    assert(strcmp(o.type,"teren") == 0);

    o = get(&l1, 1);
    assert(strcmp(o.address,"Arghezi") == 0);

    destroy(&l1);
    destroy(&l2);
    assert(size(&l1) == 0);
}

void testeSortareService(){
    MyList l = createEmpty();

    int ok1 = addOffer(&l, "teren", 200, "str1", 200);
    assert(ok1 == 0);
    assert(size(&l) == 1);

    int ok2 = addOffer(&l, "casa", 245, "str2", 2010);
    assert(ok2 == 0);
    assert(size(&l) == 2);

    int ok3 = addOffer(&l, "apartament", 245, "str3", 200);
    assert(ok3 == 0);
    assert(size(&l) == 3);

    MyList sortare = sortare_dupa_pret_tip_service(l);
    assert(eq(sortare.elems[0],l.elems[1]) == 0);
    assert(eq(sortare.elems[1],l.elems[0]) == 1);
    destroy(&sortare);

    destroy(&l);
    assert(size(&l) == 0);
}

void testeFiltrareService(){
    MyList l = createEmpty();

    int ok1 = addOffer(&l, "teren", 200, "str1", 200);
    assert(ok1 == 0);
    assert(size(&l) == 1);

    int ok2 = addOffer(&l, "casa", 245, "str2", 450);
    assert(ok2 == 0);
    assert(size(&l) == 2);

    int ok3 = addOffer(&l, "apartament", 245, "str3", 451);
    assert(ok3 == 0);
    assert(size(&l) == 3);

    MyList filtrare1 = filtrare_dupa_criteriu_service(l, "suprafata", "200");
    assert(size(&filtrare1) == 1);
    destroy(&filtrare1);

    MyList filtrare2 = filtrare_dupa_criteriu_service(l, "tip", "casa");
    assert(size(&filtrare2) == 1);
    destroy(&filtrare2);

    MyList filtrare3 = filtrare_dupa_criteriu_service(l, "pret", "200");
    assert(size(&filtrare3) == 1);
    destroy(&filtrare3);

    destroy(&l);
    assert(size(&l) == 0);
}

void testeActualizareService(){
    MyList l = createEmpty();
    int ok1 = addOffer(&l, "teren", 200, "str1", 200);
    assert(ok1 == 0);
    assert(size(&l) == 1);

    int ver1 = actualizeaza_oferta_service(&l, "teren", "str1", "casa", 400, "str4", 200);
    assert(ver1 == 0);

    int ver2 = actualizeaza_oferta_service(&l, "casa", "str10", "teren", 400, "str4", 120);
    assert(ver2 == -1);

    destroy(&l);
    assert(size(&l) == 0);
}

void testeStergereService(){
    MyList l = createEmpty();

    int ok1 = addOffer(&l, "teren", 200, "str1", 200);
    assert(ok1 == 0);
    assert(size(&l) == 1);

    int ok2 = addOffer(&l, "casa", 245, "str2", 450);
    assert(ok2 == 0);
    assert(size(&l) == 2);

    int ok3 = addOffer(&l, "apartament", 245, "str3", 451);
    assert(ok3 == 0);
    assert(size(&l) == 3);

    int aux1 = sterge_oferta_service(&l, "teren", "str1");
    assert(aux1 == 0);
    assert(size(&l) == 2);

    int aux2 = sterge_oferta_service(&l, "nimic", "str41");
    assert(aux2 == -1);
    assert(size(&l) == 2);

    destroy(&l);
    assert(size(&l) == 0);
}

void testsService(){
    MyList l = createEmpty();
    //try to add invalid offers
    int error = addOffer(&l, "", 120, "strada", 24);
    assert(error != 0);
    assert(size(&l) == 0);

    error = addOffer(&l, "casa", -120, "strada", 24);
    assert(error != 0);
    assert(size(&l) == 0);

    error = addOffer(&l, "casa", 120, "", 24);
    assert(error != 0);
    assert(size(&l) == 0);

    error = addOffer(&l, "casa", 120, "strada", -24);
    assert(error != 0);
    assert(size(&l) == 0);

    destroy(&l);
    assert(size(&l) == 0);
}
