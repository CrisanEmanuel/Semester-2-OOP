#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

class Planeta {
private:
    int cod{};
    string nume;
    string nume_sistem;
    int masa{};
    int diametru{};

public:
    Planeta(int cod, string nume, string nume_sistem, int masa, int diametru): cod{ cod }, nume{ std::move(nume) }, nume_sistem{ std::move(nume_sistem) }, masa{ masa }, diametru{ diametru }{}

    [[nodiscard]] int get_cod() const;
    [[nodiscard]] int get_masa() const;
    [[nodiscard]] int get_diametru() const;
    [[nodiscard]] string get_nume() const;
    [[nodiscard]] string get_nume_sistem() const;
};
