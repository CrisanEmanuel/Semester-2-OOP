#include "exceptions.h"

string RepoException::get_mesaj() {
    return this->mesaj;
}

ostream& operator << (ostream& out, const ValidateException& ex) {
    for (const auto& msg : ex.mesaje) {
        out << msg << " ";
    }
    return out;
}