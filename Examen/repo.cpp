#include "repo.h"

void Repo::add_repo(const Task& task) {
    for (auto & i : tasks) {
        if (task.get_id() == i.get_id())
            throw RepoException("Task deja existent!\n");
    }
    tasks.push_back(task);
}

const vector<Task> &Repo::get_all() {
    return tasks;
}

Task Repo::cauta_dupa_id_repo(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&] (const Task& task) {
        return task.get_id() == id;
    });

    if (it != tasks.end()) {
        return *it;
    }
    throw RepoException("Task inexistent!\n");
}
