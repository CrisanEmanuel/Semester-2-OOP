#include "service.h"

vector<Planeta> Service::get_all_service() {
    return repo.get_all_repo();
}

vector<Planeta> Service::sort_by_masa() {
    auto planete = repo.get_all_repo();
    vector<Planeta> rez;
    std::copy(planete.begin(), planete.end(), std::back_inserter(rez));
    std::sort(rez.begin(), rez.end(), [&] (const Planeta &p1, const Planeta &p2) {
        return p1.get_masa() < p2.get_masa();
    });
    return rez;
}

vector<Planeta> Service::sort_by_diametru() {
    auto planete = repo.get_all_repo();
    vector<Planeta> rez;
    std::copy(planete.begin(), planete.end(), std::back_inserter(rez));
    std::sort(rez.begin(), rez.end(), [&] (const Planeta &p1, const Planeta &p2) {
        return p1.get_diametru() < p2.get_diametru();
    });
    return rez;
}

vector<Planeta> Service::sort_by_nume() {
    auto planete = repo.get_all_repo();
    vector<Planeta> rez;
    std::copy(planete.begin(), planete.end(), std::back_inserter(rez));
    std::sort(rez.begin(), rez.end(), [&] (const Planeta &p1, const Planeta &p2) {
        return p1.get_nume() < p2.get_nume();
    });
    return rez;
}

void Service::add_service(int cod, const string &nume, const string &nume_sistem, int masa, int diametru) {
    Planeta planeta(cod, nume, nume_sistem, masa, diametru);
    repo.add_repo(planeta);
}

Planeta Service::search_service(int cod) {
    auto planete = repo.get_all_repo();
    auto it = std::find_if(planete.begin(), planete.end(), [&] (const Planeta &p) {
        return p.get_cod() == cod;
    });

    if (it != planete.end()) {
        return *it;
    }
    throw RepoException("Planeta inexistenta!\n");
}