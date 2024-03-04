#include "repo_file.h"

void RepoFile::read_from_file() {
    std::ifstream in(file_name);
    if(!in.is_open()) {
        throw RepoException("Nu s-a putut deschide " + file_name);
    }
    while(!in.eof()) {
        int cod;
        in >> cod;

        string nume;
        in >> nume;

        string nume_sistem;
        in >> nume_sistem;

        int masa;
        in >> masa;

        int diametru;
        in >> diametru;

        if(in.eof()) break;

        Repo::add_repo(Planeta(cod, nume, nume_sistem, masa, diametru));
    }
    in.close();
}
