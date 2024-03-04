#pragma once
#include "repo.h"
#include <exception>
#include <utility>

using std::ostream;

class RepoException:public std::exception {
private:
    string mesaj;
public:
    explicit RepoException(string mesaj): mesaj { std::move(mesaj) }{}

    string get_mesaj();
};
