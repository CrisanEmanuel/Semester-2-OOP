#include "exceptions.h"

string RepoException::getMesaj() {
    return mesaj;
}

ostream& operator << (ostream& out, const ValidateException& ex) {
    for (const auto& msg : ex.mesaje) {
        out << msg << " ";
    }
    return out;
}