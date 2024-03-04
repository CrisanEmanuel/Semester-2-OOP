#pragma once
#include "domain.h"
#include "repository.h"
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

using std::vector;

class Contract {
private:
    vector<Disciplina> contract;
public:
    Contract() = default;

    Contract(const Contract& ot) = delete;

    void addToContract(const Disciplina& disciplina);

    virtual void emptyContract();

    void generateContract(int nrDiscipline, const vector<Disciplina>& allDiscipline);

    const vector<Disciplina>& getAll();

    void deleteDisciplinaDinContract(const string& denumire);

    void updateDisciplinaDinContract(const string& denumire, const Disciplina& disciplinaNoua);

    void exportContractToFileCSV(const string& fileName);

    void exportContractToFileHTML(const string& fileName);
};