#pragma once
#include "service.h"
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QBoxLayout>
#include <QListWidget>
#include <QString>
#include <QMessageBox>
#include <QTableWidget>

class PlaneteGUI: public QWidget {
public:
    Service &service;
    explicit PlaneteGUI(Service &service): service { service }{
        initGUI();
        loadData(service.get_all_service());
        initConnect();
    }

private:

    QPushButton *sort_by_masa_button = new QPushButton("&SortByMasa");
    QPushButton *sort_by_nume_button = new QPushButton("&SortByNume");
    QPushButton *sort_by_diametru_button = new QPushButton("&SortByDiametru");
    QPushButton *exit_button = new QPushButton("&Exit");

    QListWidget *lista_planete = new QListWidget;

    QLineEdit *cod = new QLineEdit;
    QLineEdit *nume = new QLineEdit;
    QLineEdit *nume_sistem = new QLineEdit;
    QLineEdit *masa = new QLineEdit;
    QLineEdit *diametru = new QLineEdit;

    //functie de initializare a ferestri gui
    void initGUI();
    //funstie de populare
    void loadData(const vector<Planeta> &planete);
    //functie de conectare butoane
    void initConnect();

};

