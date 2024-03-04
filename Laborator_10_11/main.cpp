#include "service.h"
#include "tests.h"
#include "Contract.h"
#include "repositoryFile.h"
#include "disciplinaGUI.h"

int main(int argc, char *argv[]){

    RepoFile repoFile("discipline.txt");
    Contract contract;
    Service service(repoFile, contract);
    Tests::runAllTeste();

    {
        QApplication a(argc, argv);

        DisciplinaGUI ui1(service);
        ui1.resize(900, 400);
        ui1.show();

        DisciplinaGUI ui2(service);
        ui2.resize(900, 400);
        ui2.show();

        QApplication::exec();
    }
    return 0;
}