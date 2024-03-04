#include "teste.h"

void Teste::test_domain() {
    Planeta p(1234, "Pluto", "Solar", 555, 9999);
    assert(p.get_cod() ==  1234);
    assert(p.get_nume() == "Pluto");
    assert(p.get_nume_sistem() == "Solar");
    assert(p.get_masa() == 555);
    assert(p.get_diametru() == 9999);
}

void Teste::test_service() {
    Repo repo;
    Service service(repo);

    Planeta p1(1234, "c", "Solar", 555, 459);
    Planeta p2(1434, "b", "Solar", 5255, 93499);
    Planeta p3(234, "a", "Solar", 785, 9944);
    Planeta p4(134, "z", "Solar", 9955, 999);
    Planeta p5(144, "g", "Solar", 5125, 139);

    service.add_service(1234, "b", "Solar", 555, 459);
    service.add_service(1434, "c", "Solar", 5255, 93499);
    service.add_service(234, "a", "Solar", 785, 9944);
    service.add_service(134, "z", "Solar", 9955, 999);
    service.add_service(144, "g", "Solar", 5125, 139);

    try {
        service.add_service(1234, "Pluto", "Solar", 555, 459);
        assert(false);
    } catch (RepoException &ex) {
        assert(ex.get_mesaj() == "Planeta deja existenta!\n");
    }

    assert(service.get_all_service().size() == 5);

    assert(service.search_service(134).get_nume() == "z");

    try {
        service.search_service(0);
        assert(false);
    }catch (RepoException &ex) {
        assert(true);
    }

    assert(service.sort_by_diametru()[0].get_cod() == 144);
    assert(service.sort_by_masa()[0].get_cod() == 1234);
    assert(service.sort_by_nume()[0].get_cod() == 234);
}


void Teste::test_all() {
    test_domain();
    test_service();
    //std::cout << "Passed!";
}
