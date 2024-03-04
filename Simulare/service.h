#pragma once
#include "repo.h"

class Service {
private:
    Repo &repo;
public:
    explicit Service(Repo &repo): repo{ repo }{}

    //adauga o planeta
    void add_service(int cod, const string &nume, const string &nume_sistem, int masa, int diametru);

    //cauta planeta dupa cod
    Planeta search_service(int cod);

    //returneaza toate planetele din aplicatie
    vector<Planeta> get_all_service();

    //sorteaza planetele dupa masa
    vector<Planeta> sort_by_masa();

    //sorteaza planetele dupa diametru
    vector<Planeta> sort_by_diametru();

    //sorteaza planetele dupa nume
    vector<Planeta> sort_by_nume();
};
