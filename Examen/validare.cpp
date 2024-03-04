#include "validare.h"

void Validare::validate(const Task &task) {
    vector<string> errors;
    if (task.get_id() < 0) errors.emplace_back("Id invalid!\n");
    if (task.get_descriere().empty()) errors.emplace_back("Descriere vida!\n");
    if (task.get_programatori().empty() || task.get_programatori().size() > 4) errors.emplace_back("Numar programatori prea mare!\n");
    if (task.get_stare() != "open" && task.get_stare() != "inprogress" && task.get_stare() != "closed")
        errors.emplace_back("Stare invalida!\n");
    if (!errors.empty())
        throw ValidateException(errors);
}
