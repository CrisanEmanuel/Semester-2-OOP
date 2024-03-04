#include "service.h"
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QBoxLayout>
#include <QString>
#include <QMessageBox>
#include <QTableView>
#include <utility>
#include <QTableWidget>
#include "model_view.h"
#include <QTableView>
#include <QAbstractTableModel>


class TaskGUI: public QWidget {
public:
    Service &service;
    explicit TaskGUI(Service& service): service { service } {
        initGUI();
        model = new MyTableModel(service.get_all_sorted());
        table->setModel(model);
        initConnect();
        loadData(service.get_all_sorted());
    }

private:
    QTableView *table = new QTableView;
    MyTableModel *model;

    QPushButton *addButton = new QPushButton("&Add");
    QPushButton *searchButton = new QPushButton("&Search");
    QPushButton *ShowAll = new QPushButton("&Show All");

    QLineEdit *text_id = new QLineEdit;
    QLineEdit *text_descriere = new QLineEdit;
    QLineEdit *text_programator1 = new QLineEdit;
    QLineEdit *text_programator2 = new QLineEdit;
    QLineEdit *text_programator3 = new QLineEdit;
    QLineEdit *text_programator4 = new QLineEdit;
    QLineEdit *text_nr_programator = new QLineEdit;
    QLineEdit *text_stare = new QLineEdit;

    // initializeaza fereastra
    void initGUI();
    // conecteaza butoanele la semnale
    void initConnect();
    // se incarca datele din aplicatie in tabel
    void loadData(const vector<Task>& tasks);
};