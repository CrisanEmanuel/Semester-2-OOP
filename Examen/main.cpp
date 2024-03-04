#include <QApplication>
#include "teste.h"
#include "repo_file.h"
#include "service.h"
#include "taskGUI.h"

int main(int argc, char *argv[]) {

    Tests::test_all();
    RepoFile repoFile("file.txt");
    Service service(repoFile);

    {
        QApplication a(argc, argv);
        TaskGUI gui(service);
        gui.resize(900, 300);
        gui.show();
        QApplication::exec();
    }
}
