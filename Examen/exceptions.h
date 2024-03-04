#pragma once
#include <exception>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

using std::ostream;
using std::string;
using std::vector;

class RepoException: public std::exception {
    string mesaj;
public:
    explicit RepoException(string mesaj): mesaj {std::move(mesaj)}{}

    // returneaza mesajul de eroare
    string get_mesaj();
};

class ValidateException: public std::exception {
    vector<string> mesaje;
public:
    explicit ValidateException(vector<string>& errors): mesaje {errors} {};

    friend ostream& operator << (ostream& out, const ValidateException& ex);
};

ostream& operator << (ostream& out, const ValidateException& ex);
