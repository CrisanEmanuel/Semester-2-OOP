#include "service.h"

vector<Disciplina> Service::getAll() {
    return repo.getAll();
}

void Service::addService(const string& denumire, int ore, const string& tip, const string& profesor){
    Disciplina d(denumire, ore, tip, profesor);
    ValidareDisciplina::validate(d);
    /// pentru undo
    undoActions.push_back(std::make_unique<UndoAdauga>(repo, d));
    /// pentru undo
    repo.addRepo(d);
    notify();
}

void Service::deleteService(const string& denumire) {
    /// pentru undo
    auto d = searchService(denumire);
    undoActions.push_back(std::make_unique<UndoSterge>(repo, d));
    /// pentru undo
    repo.deleteRepo(denumire);
    contract.deleteDisciplinaDinContract(denumire);
    notify();
}

void Service::updateService(const string& denumire, int nrOreNou, const string& tipNou, const string& profesorNou) {
    Disciplina disciplinaNoua(denumire, nrOreNou, tipNou, profesorNou);
    ValidareDisciplina::validate(disciplinaNoua);
    /// pentru undo
    auto disciplinaVeche = searchService(denumire);
    undoActions.push_back(std::make_unique<UndoModifica>(repo, disciplinaNoua, disciplinaVeche));
    /// pentru undo
    repo.updateRepo(denumire, disciplinaNoua);
    contract.updateDisciplinaDinContract(denumire, disciplinaNoua);
    notify();
}

Disciplina Service::searchService(const string &denumire) {
    return repo.searchRepo(denumire);
}

vector<Disciplina> Service::filter(const function<bool(const Disciplina&)>& fct) {
    vector<Disciplina> all = repo.getAll();
    vector<Disciplina> rez;
    std::copy_if(all.begin(), all.end(), std::back_inserter(rez), fct);
    return rez;
}

vector<Disciplina> Service::filterNrOre(int nrOre) {
    return filter([nrOre](const Disciplina& d) {
        return d.getOrePeSaptamana() == nrOre;
    });
}

vector<Disciplina> Service::filterProfesor(const string& profesor) {
    return filter([profesor](const Disciplina& d) {
        return d.getProfesor() == profesor;
    });
}

vector<Disciplina> Service::generalSort(bool(*fct)(const Disciplina&, const Disciplina&)) {
    vector<Disciplina> rez;
    vector<Disciplina> all = repo.getAll();
    std::copy(all.begin(), all.end(), std::back_inserter(rez)); // fac o copie
    sort(rez.begin(), rez.end(), fct);
    return rez;
}

vector<Disciplina> Service::sortByDenumire(){
    return generalSort(Disciplina::cmpDenumire);
}

vector<Disciplina> Service::sortByNrOre(){
    return generalSort(Disciplina::cmpNrOre);
}

vector<Disciplina> Service::sortByTipProfesor() {
    return generalSort([](const Disciplina& d1, const Disciplina& d2) {
        if (d1.getTip() == d2.getTip()) {
            return d1.getProfesor() < d2.getProfesor();
        }
        return d1.getTip() < d2.getTip();
    });
}

void Service::addToContractService(const vector<std::string>& denumiri) {
    auto all = repo.getAll();
    for (const auto& i: denumiri){
        auto it = std::find_if(all.begin(), all.end(), [i] (const Disciplina& d) {
            return i == d.getDenumire();
        });
        if(it != all.end()){
            contract.addToContract(*it);
        }
    }
}

void Service::emptyContractService() {
    contract.emptyContract();
}

vector<Disciplina> Service::getAllDisciplineFromContractService() {
    return contract.getAll();
}

void Service::generateRandomContractService(int nrDiscipline) {
    contract.generateContract(nrDiscipline, repo.getAll());
}

int Service::nrDisciplineContract() {
    return int(contract.getAll().size());
}

void Service::exportContractToFileCSVService(const string& fileName) {
    contract.exportContractToFileCSV(fileName);
}

void Service::exportContractToFileHTMLService(const string& fileName) {
    contract.exportContractToFileHTML(fileName);
}

map<string, int> Service::funcNoua() { /// pt labul 8 (create map)
    map<string, int> rez;
    vector<Disciplina> all = repo.getAll();
    for(const auto& d: all) {
        rez[d.getTip()] += 1;
    }
    return rez;
}

void Service::undoService() {
    if (undoActions.empty()){
        throw ServiceException("Nu se mai poate da undo!\n");
    }
    undoActions.back()->doUndo();
    undoActions.pop_back();
    notify();
}