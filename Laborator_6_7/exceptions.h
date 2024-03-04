#pragma once
#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::ostream;

using std::string;

class RepoException:public std::exception{
    string mesaj;
public:
    explicit RepoException(string mesaj): mesaj { std::move(mesaj) }{}

    string getMesaj();
};

class ValidateException:public std::exception {
    vector<string> mesaje;
public:
    explicit ValidateException(const vector<string>& errors) :mesaje{ errors } {}
    // functie friend (vreau sa folosesc membru privat mesaje)
    friend ostream& operator << (ostream& out, const ValidateException& ex);
};

ostream& operator << (ostream& out, const ValidateException& ex);