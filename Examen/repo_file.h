#pragma once
#include "repo.h"
#include <fstream>
#include <utility>

using std::ifstream;
using std::ofstream;

class RepoFile: public Repo {
private:
    string file_name;
    // citeste datele din fisier
    void read_from_file();
    // pune datele in fisier
    void write_to_file();
public:
    explicit RepoFile(string file_name):Repo(), file_name { std::move(file_name) }{
        read_from_file();
    }

    // adauga in repe taskul task si modifica si in fisier
    void add_repo(const Task& task) override;
};
