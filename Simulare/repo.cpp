#include "repo.h"

vector<Planeta> &Repo::get_all_repo() {
    return this->planete;
}

void Repo::add_repo(const Planeta &planeta) {
    auto it = std::find_if(this->planete.begin(), this->planete.end(), [&] (const Planeta &p) {
        return p.get_cod() == planeta.get_cod();
    });

    if (it != this->planete.end()) {
        throw RepoException("Planeta deja existenta!\n");
    }
    this->planete.push_back(planeta);
}


