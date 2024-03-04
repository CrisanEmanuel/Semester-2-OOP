#include "service.h"

vector<Task> Service::get_all_service() {
    return repo.get_all();
}

vector<Task> Service::get_all_sorted() {
    auto rez = repo.get_all();
    vector<Task> sorted;
    std::copy(rez.begin(), rez.end(), std::back_inserter(sorted));
    std::sort(sorted.begin(), sorted.end(), [&] (const Task& t1, const Task& t2) {
        return t1.get_stare() < t2.get_stare();
    });
    return sorted;
}

void Service::add_service(int id, const string& descriere, const vector<string>& programatori, const string& stare) {
    Task t(id, descriere, programatori, stare);
    Validare::validate(t);
    repo.add_repo(t);
}

Task Service::cauta_dupa_id(int id) {
    return repo.cauta_dupa_id_repo(id);
}

vector<Task> Service::cauta_programator(const string& nume) {
    vector<Task> rez; int ok ;
    vector<Task> all = repo.get_all();
    for (auto const& el: all) {
        ok = 0;
        auto vec = el.get_programatori();
        for (int i = 0; i < vec.size() && ok == 0; i++){
            if (vec[i] == nume) {
                rez.push_back(el);
                ok = 1;
            }
        }
    }
    return rez;
}
