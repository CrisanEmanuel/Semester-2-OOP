#include "domain.h"

int Task::get_id() const {
    return this->id;
}

string Task::get_stare() const {
    return this->stare;
}

string Task::get_descriere() const {
    return this->descriere;
}

vector<string> Task::get_programatori() const {
    return this->programatori;
}
