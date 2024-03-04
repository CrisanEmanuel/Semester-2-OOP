#include "service.h"

VectDinNewDeleteT<Disciplina> Service::getAll() {
    return repo.getAll();
}

void Service::addService(const string& denumire, int ore, const string& tip, const string& profesor){
    Disciplina d(denumire, ore, tip, profesor);
    ValidareDisciplina::validate(d);
    repo.addRepo(d);
}

void Service::deleteService(const string& denumire) {
    repo.deleteRepo(denumire);
}

void Service::updateService(const string& denumire, const string& denumireNoua, int nrOreNou, const string& tipNou, const string& profesorNou) {
    Disciplina disciplinaNoua(denumireNoua, nrOreNou, tipNou, profesorNou);
    ValidareDisciplina::validate(disciplinaNoua);
    repo.updateRepo(denumire, disciplinaNoua);
}

Disciplina Service::searchService(const string &denumire) {
    return repo.searchRepo(denumire);
}

VectDinNewDeleteT<Disciplina> Service::filter(const function<bool(const Disciplina&)>& fct){
    VectDinNewDeleteT<Disciplina> rez;
    VectDinNewDeleteT<Disciplina> all = repo.getAll();
    for (int i = 0; i < all.size(); i++){
        if (fct(all.get(i))) {
            rez.push_back(all.get(i));
        }
    }
    return rez;}

VectDinNewDeleteT<Disciplina> Service::filterNrOre(int nrOre) {
    return filter([nrOre](const Disciplina& d) {
        return d.getOrePeSaptamana() == nrOre;
    });
}

VectDinNewDeleteT<Disciplina> Service::filterProfesor(const string& profesor) {
    return filter([profesor](const Disciplina& d) {
        return d.getProfesor() == profesor;
    });
}

VectDinNewDeleteT<Disciplina> Service::generalSort(bool(*fct)(const Disciplina&, const Disciplina&)) {
    VectDinNewDeleteT<Disciplina> v{ repo.getAll() }; //fac o copie
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (!fct(v[i], v[j])) {
                //interschimbam
                Disciplina aux = v[i];
                v[i] = v[j];
                v[j] =  aux;
            }
        }
    }
    return v;}

VectDinNewDeleteT<Disciplina> Service::sortByDenumire(){
    return generalSort(Disciplina::cmpDenumire);
}

VectDinNewDeleteT<Disciplina> Service::sortByNrOre(){
    return generalSort(Disciplina::cmpNrOre);
}

VectDinNewDeleteT<Disciplina> Service::sortByTipProfesor() {
    return generalSort([](const Disciplina& d1, const Disciplina& d2) {
        if (d1.getTip() == d2.getTip()) {
            return d1.getProfesor() < d2.getProfesor();
        }
        return d1.getTip() < d2.getTip();
    });
}


