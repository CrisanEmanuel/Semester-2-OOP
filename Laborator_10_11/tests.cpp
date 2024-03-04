#include "tests.h"

using std::cout;

void Tests::runAllTeste() {
    testeDomain();
    testeRepo();
    testeService();
    testeValidare();
    testeCreareContract();
    testeUndo();
    //cout << "Tests passed!\n\n";
}

void Tests::testeDomain() {
    Disciplina d("a", 34, "a", "a");
    assert(d.getDenumire() == "a");
    assert(d.getOrePeSaptamana() == 34);
    assert(d.getTip() == "a");
    assert(d.getProfesor() == "a");

    d.setDenumire("b");
    assert(d.getDenumire() == "b");

    d.setOrePeSaptamana(12);
    assert(d.getOrePeSaptamana() == 12);

    d.setTip("b");
    assert(d.getTip() == "b");

    d.setProfesor("b");
    assert(d.getProfesor() == "b");
}

void Tests::testeRepo() {
    Repo repo;
    Disciplina d("a", 20, "b", "c");
    repo.addRepo(d);
    const auto& discipline = repo.getAll();
    assert(discipline.size() == 1);

    try {
        repo.addRepo(d);
        assert(false);
    }catch(RepoException &e){
        assert(true);
    }
}

void Tests::testeService() {
    RepoFile repo("dateTest.txt");
    Contract contract;
    Service service(repo, contract);

    /// adaugare
    service.addService("a", 20, "a", "a");
    assert(service.getAll().size() == 1);

    service.addService("b", 21, "b", "b");
    assert(service.getAll().size() == 2);

    service.addService("c", 11, "c", "c");
    assert(service.getAll().size() == 3);
    /// adaugare

    /// funcNoua (createMap lab 8)
    auto map = service.funcNoua();
    assert(map["a"] == 1);
    /// funcNoua (createMap lab 8)

    /// stergere
    service.deleteService("b");
    assert(service.getAll().size() == 2);

    service.deleteService("a");
    assert(service.getAll().size() == 1);

    service.deleteService("c");
    assert(service.getAll().empty() == true);

    try {
        service.deleteService("d");
        assert(false);
    }catch(RepoException &ex){
        assert(ex.getMesaj() == "Disciplina inexistenta!\n");
    }
    /// stergere

    /// modificare aka update
    service.addService("a", 20, "a", "a");
    assert(service.getAll().size() == 1);

    service.updateService("a", 2, "c", "c");

    try{
        service.updateService("aa", 12, "d", "d");
        assert(false);
    }catch(RepoException &ex){
        assert(ex.getMesaj() == "Disciplina inexistenta!\n");
    }
    /// modificare aka update

    /// cautare
    assert(service.getAll().size() == 1);
    Disciplina d = service.searchService("a");
    assert(d.getDenumire() == "a");
    service.deleteService("a");
    assert(service.getAll().empty() == true);

    try{
        service.searchService("a");
        assert(false);
    }catch(RepoException &ex){
        assert(ex.getMesaj() == "Disciplina inexistenta!\n");
    }
    /// cautare

    /// filtrare
    service.addService("a", 20, "a", "a");
    service.addService("b", 21, "b", "b");
    service.addService("c", 11, "a", "c");
    service.addService("d", 11, "d", "c");

    assert(service.filterNrOre(20).size() == 1);
    assert(service.filterNrOre(11).size() == 2);
    assert(service.filterNrOre(110).empty() == true);

    assert(service.filterProfesor("a").size() == 1);
    assert(service.filterProfesor("c").size() == 2);
    assert(service.filterProfesor("z").empty() == true);
    /// filtrare

    /// sortare
    auto d1 = service.sortByDenumire()[0];
    assert(d1.getDenumire() == "a");

    auto d2 = service.sortByNrOre()[0];
    assert(d2.getOrePeSaptamana() == 11);

    auto d3 = service.sortByTipProfesor()[0];
    assert(d3.getTip() == "a");
    assert(d3.getProfesor() == "a");
    /// sortare
}

void Tests:: testeValidare() {
    Disciplina d("", 0, "a", "a");
    try {
        ValidareDisciplina::validate(d);
    }catch (const ValidateException& ex) {
        std::stringstream sout;
        sout << ex;
        auto mesaj = sout.str();
        assert(mesaj.find("invalid") < mesaj.size());
    }
}

void Tests::testeCreareContract() {
    Repo repo;
    Contract contract;
    Service service(repo, contract);

    assert(service.getAll().empty());

    service.addService("a", 24, "a", "a");
    service.addService("b", 14, "b", "b");
    service.addService("c", 34, "c", "c");
    service.addService("d", 56, "d", "d");
    service.addService("e", 41, "e", "e");

    assert(service.getAll().size() == 5);
    assert(service.getAllDisciplineFromContractService().empty());

    vector<string> denumiri;
    denumiri.emplace_back("a");
    denumiri.emplace_back("b");
    denumiri.emplace_back("c");
    denumiri.emplace_back("e");

    service.addToContractService(denumiri);
    assert(service.nrDisciplineContract() == 4);

    vector<string> aceasiDenumire;
    aceasiDenumire.emplace_back("a");
    try {
        service.addToContractService(aceasiDenumire);
        assert(false);
    }catch (RepoException &ex) {
        assert(ex.getMesaj() == "Disciplina deja existenta in contract!\n");
    }

    vector<Disciplina> vec = service.getAllDisciplineFromContractService();
    assert(vec[0].getDenumire() == "a");
    assert(vec[1].getDenumire() == "b");
    assert(vec[2].getDenumire() == "c");
    assert(vec[3].getDenumire() == "e");

    assert(service.nrDisciplineContract() == 4);

    service.deleteService("a");
    assert(service.getAll().size() == 4);
    assert(service.nrDisciplineContract() == 3);

    service.updateService("b", 44, "zz", "zz");
    try{
        service.searchService("bb");
        assert(false);
    }catch(RepoException& ex){
        assert(ex.getMesaj() == "Disciplina inexistenta!\n");
    }
    assert(service.getAllDisciplineFromContractService()[0].getTip() == "zz");

    assert(service.nrDisciplineContract() == 3);
    service.generateRandomContractService(2);
    assert(service.nrDisciplineContract() == 2);

    string invalidFile = " ";
    service.exportContractToFileCSVService("dateTest.csv");
    service.exportContractToFileHTMLService("dateTest.html");
    try {
        service.exportContractToFileCSVService(invalidFile);
        assert(false);
    }catch(RepoException &ex) {
        assert(ex.getMesaj() == "Nu se poate deschide: " + invalidFile);
    }
    try {
        service.exportContractToFileHTMLService(invalidFile);
        assert(false);
    }catch(RepoException &ex) {
        assert(ex.getMesaj() == "Nu se poate deschide: " + invalidFile);
    }
    service.emptyContractService();
    assert(service.getAllDisciplineFromContractService().empty());
}

void Tests::testeUndo() {
    Repo repo;
    Contract contract;
    Service service(repo, contract);

    try {
        service.undoService();
        assert(false);
    }catch(ServiceException &ex){
        assert(ex.getMesaj() == "Nu se mai poate da undo!\n");
    }

    service.addService("a", 24, "a", "a");
    service.addService("b", 14, "b", "b");
    service.addService("c", 34, "c", "c");

    assert(service.getAll().size() == 3);

    service.undoService();
    assert(service.getAll().size() == 2);

    service.deleteService("b");
    assert(service.getAll().size() == 1);

    service.undoService();
    assert(service.getAll().size() == 2);

    service.updateService("b", 312, "bb", "bb");
    assert(service.getAll()[1].getTip() == "bb");

    service.undoService();
    assert(service.getAll()[1].getTip() == "b");

    service.updateService("b", 312, "bb", "bb");
    service.updateService("a", 123, "aa", "aa");
    service.deleteService("b");
    service.updateService("a", 1234, "aaa", "aaa");

    service.undoService();
    assert(service.getAll()[0].getTip() == "aa");
    service.undoService();
    assert(service.getAll().size() == 2);
    service.undoService();
    assert(service.getAll()[0].getTip() == "a");
    service.undoService();
    assert(service.getAll()[1].getTip() == "b");
}