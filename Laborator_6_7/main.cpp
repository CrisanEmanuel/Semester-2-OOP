#include "repository.h"
#include "service.h"
#include "ui.h"
#include "tests.h"

int main(){


    Repo repo;
    Service service(repo);
    Ui ui(service);

    Tests::runAllTeste();

    Ui::menu();
    ui.runUi();
    return 0;
}