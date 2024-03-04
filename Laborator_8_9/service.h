#pragma once
#include <string>
#include "repository.h"
#include <functional>
#include "validare.h"
#include <algorithm>
#include "Contract.h"
#include <map>
#include "undo.h"
#include "exceptions.h"
#include <memory>

using std::string;
using std::function;
using std::vector;
using std::map;
using std::unique_ptr;

class Service {

    vector<Disciplina> filter(const function<bool(const Disciplina&)>& fct);

    vector<Disciplina> generalSort(bool (*fct)(const Disciplina&, const Disciplina&));

public:
    Repo& repo;

    Contract& contract;

    std::vector<unique_ptr<ActiuneUndo>> undoActions;

    explicit Service(Repo& repo, Contract& contract) :repo{ repo }, contract{ contract }{}

    Service(const Service& ot) = delete;

    vector<Disciplina> getAll();

    void addService(const string& denumire, int ore, const string& tip, const string& profesor);

    void deleteService(const string& denumire);

    void updateService(const string& denumire, const string& denumireNoua, int nrOreNou, const string& tipNou, const string& profesorNou);

    Disciplina searchService(const string& denumire);

    vector<Disciplina> filterNrOre(int nrOre);

    vector<Disciplina> filterProfesor(const string& profesor);

    vector<Disciplina> sortByDenumire();

    vector<Disciplina> sortByNrOre();

    vector<Disciplina> sortByTipProfesor();

    /// functii pentru contract
    void addToContractService(const vector<string>& denumiri);

    void emptyContractService();

    vector<Disciplina> getAllDisciplineFromContractService();

    void generateRandomContractService(int nrDiscipline);

    int nrDisciplineContract();

    void exportContractToFileCSVService(const string& fileName);

    void exportContractToFileHTMLService(const string& fileName);
    /// functii pentru contract

    map<string, int> funcNoua(); /// pt labul 8 (create map)

    void undoService();
};

