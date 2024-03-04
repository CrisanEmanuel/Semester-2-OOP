#pragma once
#include "Contract.h"
#include "service.h"
#include <vector>
#include <string>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QBoxLayout>
#include <QApplication>
#include <QListWidget>
#include <QString>
#include <QMessageBox>
#include <QTableWidget>

class ContractGUI: public QWidget {
public:
    Service &service;

    explicit ContractGUI(Service &service): service { service }{
        initContractGUI();
        loadData(service.getAllDisciplineFromContractService());
        initConnect();
    }
private:
    QPushButton *generateContractButton = new QPushButton("&Generate Random");
    QPushButton *emptyContractButton = new QPushButton("&Empty");
    QPushButton *exportToCSVButton = new QPushButton("&.csv");
    QPushButton *exportToHTMLButton = new QPushButton("&.html");
    QPushButton *exitButton = new QPushButton("&Exit");

    QLineEdit *fileCSV = new QLineEdit;
    QLineEdit *fileHTML = new QLineEdit;

    QListWidget *listContract = new QListWidget;
    QTableWidget *tableContract = new QTableWidget;

    void initContractGUI();
    void loadData(const vector<Disciplina> &discipline);
    void initConnect();
};