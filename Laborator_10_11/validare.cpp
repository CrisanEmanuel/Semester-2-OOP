#include "validare.h"

using std::vector;

void  ValidareDisciplina::validate(const Disciplina& d) {
    vector<string> msgs;
    if (d.getDenumire().empty()) msgs.emplace_back("Denumire invalida!\n");
    if (d.getOrePeSaptamana() < 0) msgs.emplace_back("Numar ore negativ!\n");
    if (d.getOrePeSaptamana() == 0) msgs.emplace_back("Numar ore invalid!\n");
    if (d.getTip().empty()) msgs.emplace_back("Tip invalid!\n");
    if (d.getProfesor().empty()) msgs.emplace_back("Profesor invalid!\n");
    if (!msgs.empty()) {
        throw ValidateException(msgs);
    }
}