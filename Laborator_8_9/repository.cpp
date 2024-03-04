#include "repository.h"

void Repo::addRepo(const Disciplina& disciplina) {
    for (const auto& d: discipline) {
        if (d.getDenumire() == disciplina.getDenumire()) {
            throw RepoException("Disciplina deja existenta!\n");
        }
    }
    discipline.push_back(disciplina);
}

void Repo::deleteRepo(const string& denumire) {
    auto it = std::find_if(discipline.begin(), discipline.end(), [&] (const Disciplina& d) {
        return d.getDenumire() == denumire;
    });
    if(it != discipline.end()){
        discipline.erase(it);
        return;
    }
    throw RepoException("Disciplina inexistenta!\n");

}

void Repo::updateRepo(const string& denumire, const Disciplina& disciplinaNoua) {
    auto it = std::find_if(discipline.begin(), discipline.end(), [&](const Disciplina &d) {
        return d.getDenumire() == denumire;
    });

    if (it != discipline.end()) {
        discipline.erase(it);
        discipline.insert(it, disciplinaNoua);
        return;
    }
    throw RepoException("Disciplina inexistenta!\n");

}

Disciplina Repo::searchRepo(const std::string &denumire) {
    auto it = std::find_if(discipline.begin(), discipline.end(), [&] (const Disciplina& d) {
        return d.getDenumire() == denumire;
    });
    if(it != discipline.end())
    {
        Disciplina d = *it;
        return d;
    }
    throw RepoException("Disciplina inexistenta!\n");
}
