#include "teste.h"
#include <iostream>
void Tests::test_all() {
    test_repo();
    test_domain();
    test_service();
    test_validare();
}

void Tests::test_repo() {
    Repo repo;
    vector<string> nume = {"Ion", "Mircea", "Marius"};
    Task t(1, "descriere", nume, "open");
    assert(repo.get_all().empty());
    repo.add_repo(t);
    assert(repo.get_all().size() == 1);

    assert(repo.cauta_dupa_id_repo(1).get_id() == 1);
}

void Tests::test_domain() {
    vector<string> nume = {"Ion", "Mircea", "Marius"};
    Task t1(1, "descriere", nume, "open");
    assert(t1.get_id() == 1);
    assert(t1.get_stare() == "open");
    assert(t1.get_descriere() == "descriere");
    assert(t1.get_programatori().size() == 3);
}

void Tests::test_service() {
    Repo repo;
    Service service(repo);
    vector<string> nume = {"Ion", "Mircea", "Marius"};
    Task t1(1, "descriere1", nume, "open");
    Task t2(2, "descriere2", nume, "closed");
    Task t3(3, "descriere3", nume, "inprogress");

    service.add_service(1, "descriere1", nume, "open");
    service.add_service(2, "descriere2", nume, "closed");
    service.add_service(3, "descriere3", nume, "inprogress");

    assert(service.get_all_service().size() == 3);

    assert(service.get_all_sorted()[0].get_id() == 2);

    assert(service.cauta_dupa_id(1).get_id() == 1);

    assert(service.cauta_programator("Ion").size() == 3);
}

void Tests::test_validare() {
    vector<string> nume = {"Ion", "Mircea", "Marius", "in plus", "in plus"};
    Task t1(1, "", nume, "nimic");
    try {
        Validare::validate(t1);
        assert(false);
    }catch(ValidateException& ex){
        assert(true);
    }
}
