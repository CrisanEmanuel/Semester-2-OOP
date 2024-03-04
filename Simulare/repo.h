#pragma once
#include "domain.h"
#include <algorithm>
#include "exceptions.h"
#include <string>

using std::string;

class Repo {
private:
    vector<Planeta> planete;
public:
    Repo() = default;

    //returneaza toate planetele din aplicatie
    vector<Planeta> &get_all_repo();

    //adauga planeta , in caz ca aceasta mai exista arunca exceptie
    virtual void add_repo(const Planeta &planeta);
};
