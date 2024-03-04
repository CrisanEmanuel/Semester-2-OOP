#include "repository.h"
#include "service.h"
#include "ui.h"
#include "tests.h"
#include "Contract.h"
#include "repositoryFile.h"

int main(){

    Repo repo;
    RepoFile repoFile("discipline.txt");
    Contract contract;
    Service service(repoFile, contract);
    Ui ui(service);

    Tests::runAllTeste();

    Ui::menu();
    ui.runUi();
    return 0;
}