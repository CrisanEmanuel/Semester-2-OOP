#pragma once
#include "domain.h"
#include "VectorDinamicTemplate.h"


class Repo {

private:
    VectDinNewDeleteT<Disciplina> discipline;
public:

    Repo(const Repo& ot) = delete;
    Repo() = default;

    const VectDinNewDeleteT<Disciplina>& getAll(){
        return discipline;
    }

    void addRepo(const Disciplina& disciplina);

    void deleteRepo(const string& denumire);

    void updateRepo(const string& denumire, const Disciplina& disciplinaNoua);

    Disciplina searchRepo(const string& denumire);
};
