#include "repo_file.h"

void RepoFile::read_from_file() {
    ifstream read(file_name);
    if(!read.is_open())
        throw RepoException("Nu se poate deschide: " + file_name + '\n');

    while(!read.eof()) {
        int id;
        read >> id;

        string descriere;
        read >> descriere;

        vector<string> programatori;
        string nume;
        read >> nume;
        programatori.push_back(nume);
        read >> nume;
        programatori.push_back(nume);

        string stare;
        read >> stare;

        Task t(id, descriere, programatori, stare);

        if (read.eof()) break;

        Repo::add_repo(t);
    }
    read.close();
}

void RepoFile::write_to_file() {
    ofstream write(file_name);
    if(!write.is_open())
        throw RepoException("Nu se poate deschide: " + file_name + '\n');

    vector<Task> tasks = Repo::get_all();
    for (const auto& t: tasks){
        write << t.get_id() << ' ' << t.get_descriere() << ' ';
        for (const auto& nume: t.get_programatori())
            write << nume << ' ';
        write << t.get_stare() << std::endl;
    }
    write.close();
}

void RepoFile::add_repo(const Task &task) {
    Repo::add_repo(task);
    write_to_file();
}
