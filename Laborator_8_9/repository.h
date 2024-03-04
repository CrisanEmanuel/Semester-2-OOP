#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include "exceptions.h"

using std::vector;

class RepoAbstract {
private:
    vector<Disciplina> discipline;
public:

    virtual const vector<Disciplina>& getAll() = 0;

    virtual void addRepo(const Disciplina& disciplina) = 0;

    virtual void deleteRepo(const string& denumire) = 0;

    virtual void updateRepo(const string& denumire, const Disciplina& disciplinaNoua) = 0;

    virtual Disciplina searchRepo(const string& denumire) = 0;
};

class Repo:public RepoAbstract {

private:
    vector<Disciplina> discipline;
public:

    Repo(const Repo& ot) = delete;
    Repo() = default;

    const vector<Disciplina>& getAll() override{
        return discipline;
    }

    void addRepo(const Disciplina& disciplina) override;

    void deleteRepo(const string& denumire) override;

    void updateRepo(const string& denumire, const Disciplina& disciplinaNoua) override;

    Disciplina searchRepo(const string& denumire) override;
};
