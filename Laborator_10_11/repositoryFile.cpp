#include "repositoryFile.h"

void RepoFile::writeToFile() {
    std::ofstream out(fileName);
    if (!out.is_open()) {
        throw RepoException("Nu se poate deschide: " + fileName);
    }
    auto discipline = Repo::getAll();
    for(const auto &d: discipline){
        out << d.getDenumire() << ',' << d.getOrePeSaptamana() << ',';
        out << d.getTip() << ',' << d.getProfesor() << std::endl;
    }
    out.close();
}

void RepoFile::addRepo(const Disciplina &disciplina) {
    Repo::addRepo(disciplina);
    writeToFile();
}

void RepoFile::deleteRepo(const string &denumire) {
    Repo::deleteRepo(denumire);
    writeToFile();
}

void RepoFile::updateRepo(const string &denumire, const Disciplina &disciplinaNoua) {
    Repo::updateRepo(denumire, disciplinaNoua);
    writeToFile();
}

