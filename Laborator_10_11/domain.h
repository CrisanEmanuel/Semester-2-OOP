#pragma once
#include <string>
#include <utility>
#include <iostream>

using std::string;

class Disciplina {

private:
    string denumire;
    int ore{};
    string tip;
    string profesor;

public:

    Disciplina(string denumire, int orePeSaptamana, string tip, string profesor) :denumire{ std::move(denumire) }, ore{ orePeSaptamana }, tip{ std::move(tip) }, profesor{ std::move(profesor) } {}

    Disciplina(const Disciplina& d):denumire{ d.getDenumire() }, ore { d.ore }, tip { d.tip }, profesor { d.profesor }{
    }

    Disciplina() = default;

    virtual ~Disciplina() = default;

    [[nodiscard]] int getOrePeSaptamana() const;

    [[nodiscard]] string getDenumire() const;

    [[nodiscard]] string getTip() const;

    [[nodiscard]] string getProfesor() const;

    void setDenumire(const string& denumireNoua);

    void setOrePeSaptamana(int nrOreNou);

    void setTip(const string& tipNou);

    void setProfesor(const string& profesorNou);

    static bool cmpDenumire(const Disciplina& d1, const Disciplina& d2);

    static bool cmpNrOre(const Disciplina& d1, const Disciplina& d2);
};