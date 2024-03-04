#pragma once
#include "ContractGUI.h"
#include "observer.h"

class DisciplinaGUI:public QWidget, public Observer {
public:

    Service &service;

    explicit DisciplinaGUI(Service &service): service{ service } {
        initGUI();
        loadData(service.getAll());
        initConnect();
    }
private:
    QPushButton *addButton = new QPushButton("&Add");
    QPushButton *deleteButton = new QPushButton("&Delete");
    QPushButton *updateButton = new QPushButton("&Update");
    QPushButton *filterOreButton = new QPushButton("&FilterByOre");
    QPushButton *filterProfButton = new QPushButton("&FilterByProf");
    QPushButton *sortByDenumireButton = new QPushButton("&SortByDenumire");
    QPushButton *sortByNrOreButton = new QPushButton("&SortByNrOre");
    QPushButton *sortByTipProfesorButton = new QPushButton("&SortByTip+Profesor");
    QPushButton *undoButton = new QPushButton("&Undo");
    QPushButton *contractButton = new QPushButton("&Contract");
    QPushButton *addContractButton = new QPushButton("&AddToContract");
    QPushButton *showAllDisciplineButton = new QPushButton("&Show All");
    QPushButton *clearTextButton = new QPushButton("&Clear");
    QPushButton *exitButton = new QPushButton("&Exit");

    QLineEdit *textDenumire = new QLineEdit;
    QLineEdit *textOre = new QLineEdit;
    QLineEdit *textTip = new QLineEdit;
    QLineEdit *textProfesor = new QLineEdit;

    QListWidget *listDiscipline = new QListWidget;

    QVBoxLayout *lyBtnDy = new QVBoxLayout;

    void initGUI();
    void loadData(const std::vector<Disciplina> &discipline);
    void initConnect();
    void addButtons();
    void update() override;
};