#pragma once
#include <string>
#include "repository.h"
#include <functional>
#include "validare.h"

using std::string;
using std::function;

class Service {

    VectDinNewDeleteT<Disciplina> filter(const function<bool(const Disciplina&)>& fct);

    VectDinNewDeleteT<Disciplina> generalSort(bool (*fct)(const Disciplina&, const Disciplina&));

public:
    Repo &repo;

    explicit Service(Repo& repo) :repo{ repo }{}

    Service(const Service& ot) = delete;

    VectDinNewDeleteT<Disciplina> getAll();

    void addService(const string& denumire, int ore, const string& tip, const string& profesor);

    void deleteService(const string& denumire);

    void updateService(const string& denumire, const string& denumireNoua, int nrOreNou, const string& tipNou, const string& profesorNou);

    Disciplina searchService(const string& denumire);

    VectDinNewDeleteT<Disciplina> filterNrOre(int nrOre);

    VectDinNewDeleteT<Disciplina> filterProfesor(const string& profesor);

    VectDinNewDeleteT<Disciplina> sortByDenumire();

    VectDinNewDeleteT<Disciplina> sortByNrOre();

    VectDinNewDeleteT<Disciplina> sortByTipProfesor();
};

