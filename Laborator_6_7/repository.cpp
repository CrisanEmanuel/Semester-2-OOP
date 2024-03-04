#include "repository.h"
#include "exceptions.h"

void Repo::addRepo(const Disciplina& disciplina) {
    for (const auto& d: discipline) {
        if (d.getDenumire() == disciplina.getDenumire()) {
            throw RepoException("Disciplina deja existenta!\n");
        }
    }
    discipline.push_back(disciplina);
}

void Repo::deleteRepo(const string& denumire) {
    int poz = -1;
    for (const auto& d : discipline) {
        poz++;
        if (d.getDenumire() == denumire) {
                discipline.erase(poz);
                return;
        }
    }
    throw RepoException("Disciplina inexistenta!\n");
}

void Repo::updateRepo(const string& denumire, const Disciplina& disciplinaNoua){
    int poz = -1;
    for (const auto& d : discipline) {
        poz++;
        if (d.getDenumire() == denumire){
            discipline.insert(poz, disciplinaNoua);
            return;
        }
    }
    throw RepoException("Disciplina inexistenta!\n");
}

Disciplina Repo::searchRepo(const std::string &denumire) {
    for (const auto& d: discipline){
        if (d.getDenumire() == denumire){
            return d;
        }
    }
    throw RepoException("Disciplina inexistenta!\n");
}
