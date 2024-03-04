#include "planeteGUI.h"

void PlaneteGUI::initGUI() {
    auto ly_buttons1 = new QHBoxLayout;
    ly_buttons1->addWidget(sort_by_masa_button);
    ly_buttons1->addWidget(sort_by_diametru_button);

    auto ly_buttons2 = new QHBoxLayout;
    ly_buttons2->addWidget(sort_by_nume_button);
    ly_buttons2->addWidget(exit_button);

    auto textBox = new QFormLayout;
    textBox->addRow("Cod", this->cod);
    textBox->addRow("Nume", this->nume);
    textBox->addRow("Nume sistem", this->nume_sistem);
    textBox->addRow("Masa", this->masa);
    textBox->addRow("Diametru", this->diametru);

    auto ly_right = new QVBoxLayout;
    ly_right->addLayout(textBox);
    ly_right->addLayout(ly_buttons1);
    ly_right->addLayout(ly_buttons2);

    auto ly_left = new QVBoxLayout;
    ly_left->addWidget(lista_planete);

    auto ly_main = new QHBoxLayout;
    ly_main->addLayout(ly_left);
    ly_main->addLayout(ly_right);

    setLayout(ly_main);
}

void PlaneteGUI::loadData(const vector<Planeta> &planete) {
    this->lista_planete->clear();
    for (const auto &planeta: planete) {
        auto item = new QListWidgetItem(QString::number(planeta.get_cod()) + ' ' + QString::fromStdString(planeta.get_nume()));
        item->setData(Qt::UserRole, QString::number(planeta.get_cod()));
        this->lista_planete->addItem(item);
    }
}

void PlaneteGUI::initConnect() {
    QObject::connect(exit_button, &QPushButton::clicked, [&] () {
        auto semnal = QMessageBox::question(this, "Proiect", "Sigur doriti sa iesiti?");
        if (semnal == QMessageBox::Yes) {
            close();
        }
    });

    QObject::connect(lista_planete, &QListWidget::itemSelectionChanged, [&] () {
        auto selectie = lista_planete->selectedItems();
        if (selectie.empty()) {
            this->cod->setText("");
            this->nume->setText("");
            this->nume_sistem->setText("");
            this->masa->setText("");
            this->diametru->setText("");
        }else {
            auto item_selected = selectie.at(0);
            auto cod_planeta = item_selected->data(Qt::UserRole);
            auto planeta = service.search_service(cod_planeta.toInt());
            this->cod->setText(QString::number(planeta.get_cod()));
            this->nume->setText(QString::fromStdString(planeta.get_nume()));
            this->nume_sistem->setText(QString::fromStdString(planeta.get_nume_sistem()));
            this->masa->setText(QString::number(planeta.get_masa()));
            this->diametru->setText(QString::number(planeta.get_diametru()));
        }
    });

    QObject::connect(sort_by_nume_button, &QPushButton::clicked, [&] () {
        loadData(service.sort_by_nume());
    });

    QObject::connect(sort_by_masa_button, &QPushButton::clicked, [&] () {
        loadData(service.sort_by_masa());
    });

    QObject::connect(sort_by_diametru_button, &QPushButton::clicked, [&] () {
        loadData(service.sort_by_diametru());
    });

}
