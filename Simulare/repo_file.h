#pragma once
#include "repo.h"
#include <fstream>

class RepoFile:public Repo{
private:
    string file_name;
    void read_from_file();
public:
    explicit RepoFile(string file_name):Repo(), file_name { std::move(file_name) }{
        read_from_file();
    }
};