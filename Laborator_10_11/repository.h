#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include "exceptions.h"

using std::vector;


class Repo {

private:
    vector<Disciplina> discipline;
public:

    Repo(const Repo& ot) = delete;
    Repo() = default;

    const vector<Disciplina>& getAll(){
        return discipline;
    }

    virtual void addRepo(const Disciplina& disciplina);

    virtual void deleteRepo(const string& denumire);

    virtual void updateRepo(const string& denumire, const Disciplina& disciplinaNoua);

    Disciplina searchRepo(const string& denumire);
};
