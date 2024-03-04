#include "tests.h"
#include "exceptions.h"
#include <cassert>
#include <iostream>
#include "domain.h"

using std::cout;

void Tests::runAllTeste() {
    testeDomain();
    testeRepo();
    testeService();
    testeValidare();
    testeVectorDinamicT();
    testeVectorDinamicTdiscipline();
    ///////////////////////////////////////////
    testAll<VectDinNewDeleteT<Disciplina>>();
    ///////////////////////////////////////////
    cout << "Tests passed!\n\n";
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
    Repo repo;
    Service service(repo);

    /// adaugare
    service.addService("a", 20, "a", "a");
    assert(service.getAll().size() == 1);

    service.addService("b", 21, "b", "b");
    assert(service.getAll().size() == 2);

    service.addService("c", 11, "c", "c");
    assert(service.getAll().size() == 3);
    /// adaugare

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

    /// modificare
    service.addService("a", 20, "a", "a");
    assert(service.getAll().size() == 1);

    service.updateService("a", "c", 2, "c", "c");

    try{
        service.updateService("a", "d", 12, "d", "d");
        assert(false);
    }catch(RepoException &ex){
        assert(ex.getMesaj() == "Disciplina inexistenta!\n");
    }
    /// modificare

    /// cautare
    assert(service.getAll().size() == 1);
    Disciplina d = service.searchService("c");
    assert(d.getDenumire() == "c");
    service.deleteService("c");
    assert(service.getAll().empty() == true);

    try{
        service.searchService("c");
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

void Tests:: testeVectorDinamicT() {
    VectDinNewDeleteT<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);

    assert(vector.size() == 4);
    vector.erase(1);
    assert(vector.size() == 3);
    vector.erase(2);
    assert(vector.size() == 2);
    vector.erase(1);
    assert(vector.size() == 1);
    vector.erase(0);
    assert(vector.empty());

    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);

    assert(vector.get(0) == 1);
    vector.insert(3, 5);
    assert(vector.get(3) == 5);

    VectDinNewDeleteT<int> new_vector;
    new_vector = vector;
    assert(new_vector.size() == vector.size());
}

void Tests::testeVectorDinamicTdiscipline() {
    VectDinNewDeleteT<Disciplina> dis;
    Repo repo;
    Disciplina d1("a", 34, "a", "a");
    Disciplina d2("b", 36, "b", "b");
    Disciplina dn("c", 12, "c", "c");
    dis.push_back(d1);
    dis.push_back(d2);
    assert(dis.size() == 2);

    dis.erase(0);
    assert(dis.size() == 1);

    dis.erase(0);
    assert(dis.empty());

    dis.insert(0, d1);
    assert(dis.size() == 1);

    assert(dis.get(0).getDenumire() == d1.getDenumire());

    dis.erase(0);
    assert(dis.empty());

    repo.addRepo(d1);
    repo.addRepo(d2);
    assert(repo.getAll().size() == 2);

    repo.updateRepo(d1.getDenumire(), dn);
    assert(repo.getAll()[0].getDenumire() == dn.getDenumire());


    assert(repo.getAll().size() == 2);
    repo.deleteRepo(dn.getDenumire());
    assert(repo.getAll().size() == 1);
    repo.deleteRepo(d2.getDenumire());
    assert(repo.getAll().empty());
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename MyVector>
MyVector testCopyIterate(MyVector v) {
    int totalOre = 0;
    for (const auto& el: v) {
        totalOre += el.getOrePeSaptamana();
    }
    Disciplina d("a", 45, "a", "a");
    v.push_back(d);
    return v;
}

template<typename MyVector>
void addDiscipline(MyVector &v, int cate) {
    for (int i = 0; i < cate; i++) {
        Disciplina d(std::to_string(i) + "_denumire", i + 10, std::to_string(i) + "_tip", std::to_string(i) + "_profesor");
        v.push_back(d);
    }
}

template<typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addDiscipline(v, 100);
    assert(v.size() == 100);
    assert(v.get(50).getDenumire() == "50_denumire");

    MyVector v2{v};//constructor de copiere
    assert(v2.size() == 100);
    assert(v2.get(50).getDenumire() == "50_denumire");

    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.size() == 100);
    assert(v3.get(50).getDenumire() == "50_denumire");

    auto v4 = testCopyIterate(v3);
    assert(v4.size() == 101);
    assert(v4.get(50).getDenumire() == "50_denumire");
}

template<typename MyVector>
void testMoveConstrAssignment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});
    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(), MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addDiscipline(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.size() == 0);
}

template<typename MyVector>
void testAll() {
    testCreateCopyAssign<MyVector>();
    testMoveConstrAssignment<MyVector>();
    VectDinNewDeleteT<Disciplina> d;
    d.push_back(Disciplina("a", 34, "a", "a"));
    d.push_back(Disciplina("b", 34, "b", "b"));
    testCopyIterate<MyVector>(d);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////