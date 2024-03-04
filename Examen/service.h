#pragma once
#include "repo.h"
#include <algorithm>
#include "validare.h"

class Service {
public:
    Repo &repo;

    explicit Service(Repo& repo): repo {repo}{}

    // returneaza toate taskurile existente
    vector<Task> get_all_service();

    // returneaza toate taskurire sortate
    vector<Task> get_all_sorted();

    // adauga un task in aplicatie
    void add_service(int id, const string& descriere, const vector<string>& programatori, const string& stare);

    // cauta si returneaza un task dupa id
    Task cauta_dupa_id(int id);

    // cauta si returneaza taskurile la care a lucrat programatorul cu numele nume
    vector<Task> cauta_programator(const string& nume);
};