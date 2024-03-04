#pragma once
#include "repository.h"
#include <fstream>

class RepoFile: public Repo {
private:
    void writeToFile();
    string fileName;
public:
    [[maybe_unused]] explicit RepoFile(string fileName): Repo(), fileName { std::move(fileName) }{};

    void addRepo(const Disciplina& disciplina) override;

    void deleteRepo(const string& denumire) override;

    void updateRepo(const string& denumire, const Disciplina& disciplinaNoua) override;

};