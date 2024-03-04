#pragma once
#include <string>
#include <utility>
#include <vector>

using std::string;
using std::vector;

class Task {
private:
    int id;
    string descriere;
    vector<string> programatori;
    string stare;
public:
    Task(int id, string descriere, vector<string> programatori, string stare): id {id}, descriere {std::move(descriere)}, programatori {std::move(programatori)}, stare {std::move(stare)}{}

    // returneaza idul unui task
    [[nodiscard]] int get_id() const;

    // returneaza starea unui task
    [[nodiscard]] string get_stare() const;

    // returneaza descrierea unui task
    [[nodiscard]] string get_descriere() const;

    // returneaza programatoriicare au participat la task
    [[nodiscard]] vector<string> get_programatori() const;

};