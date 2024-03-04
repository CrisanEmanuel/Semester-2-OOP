#include "planeteGUI.h"
#include "service.h"
#include "repo_file.h"
#include "teste.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoFile repoFile("planete.txt");
    Service service(repoFile);

    {
        QApplication a(argc, argv);
        PlaneteGUI gui(service);
        gui.resize(900, 300);
        gui.show();
        QApplication::exec();
    }
}
