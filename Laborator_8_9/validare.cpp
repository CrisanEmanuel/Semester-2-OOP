#include "validare.h"

using std::vector;

void  ValidareDisciplina::validate(const Disciplina& d) {
    vector<string> msgs;
    if (d.getDenumire().empty()) msgs.emplace_back("Denumire invalida!");
    if (d.getOrePeSaptamana() < 0) msgs.emplace_back("Numar ore negativ!");
    if (d.getOrePeSaptamana() == 0) msgs.emplace_back("Numar ore invalid!");
    if (d.getTip().empty()) msgs.emplace_back("Tip invalid!");
    if (d.getProfesor().empty()) msgs.emplace_back("Profesor invalid!");
    if (!msgs.empty()) {
        throw ValidateException(msgs);
    }
}