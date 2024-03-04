#include "domain.h"


string Disciplina::getDenumire() const{
    return denumire;
}

int Disciplina::getOrePeSaptamana() const{
    return ore;
}

string Disciplina::getTip() const{
    return tip;
}

string Disciplina::getProfesor() const {
    return profesor;
}

void Disciplina::setDenumire(const string& denumireNoua) {
    denumire = denumireNoua;
}

void Disciplina::setOrePeSaptamana(int nrOreNou){
    ore = nrOreNou;
}

void Disciplina::setTip(const string& tipNou){
    tip = tipNou;
}

void Disciplina::setProfesor(const string& profesorNou){
    profesor = profesorNou;
}

bool Disciplina::cmpDenumire(const Disciplina& d1, const Disciplina& d2) {
    return d1.getDenumire() < d2.getDenumire();
}

bool Disciplina::cmpNrOre(const Disciplina& d1, const Disciplina& d2) {
    return d1.getOrePeSaptamana() < d2.getOrePeSaptamana();
}