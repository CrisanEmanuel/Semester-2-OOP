#pragma once
#include "domain.h"
#include "exceptions.h"
#include <algorithm>

class Repo {
private:
    vector<Task> tasks;
public:
    Repo() = default;

    // functia de adaugare in repo de taskuri
    virtual void add_repo(const Task& task);

    // returneaza toate taskurile
    const vector<Task>& get_all();

    // cauta un task dupa id
    Task cauta_dupa_id_repo(int id);

};
