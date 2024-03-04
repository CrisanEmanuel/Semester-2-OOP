#include "ContractGUI.h"

void ContractGUI::initContractGUI() {
    auto *lyButtons1 = new QHBoxLayout;
    lyButtons1->addWidget(generateContractButton);
    lyButtons1->addWidget(emptyContractButton);
    lyButtons1->addWidget(exitButton);

    auto *lyButtons2 = new QHBoxLayout;
    lyButtons2->addWidget(fileCSV);
    lyButtons2->addWidget(exportToCSVButton);

    auto *lyButtons3 = new QHBoxLayout;
    lyButtons2->addWidget(fileHTML);
    lyButtons2->addWidget(exportToHTMLButton);

    auto *lyList = new QHBoxLayout;
    lyList->addWidget(listContract);

    auto *lyTable = new QHBoxLayout;
    lyTable->addWidget(tableContract);

    auto *lyRight = new QVBoxLayout;
    lyRight->addLayout(lyButtons3);
    lyRight->addLayout(lyButtons2);
    lyRight->addLayout(lyButtons1);

    auto *lyMain = new QHBoxLayout;
    lyMain->addLayout(lyTable);
    //lyMain->addLayout(lyList);
    lyMain->addLayout(lyRight);

    setLayout(lyMain);
}

void ContractGUI::loadData(const vector<Disciplina> &discipline) {
//    listContract->clear();
//    for (const auto &d: discipline) {
//        auto denumire = QString::fromStdString(d.getDenumire());
//        auto ore = QString::fromStdString(std::to_string(d.getOrePeSaptamana()));
//        auto tip = QString::fromStdString(d.getTip());
//        auto profesor = QString::fromStdString(d.getProfesor());
//        listContract->addItem(denumire + ' ' + ore + ' ' + tip + ' ' + ' ' + profesor);
//    }
    tableContract->clearContents();
    int row = 0;
    int rowCount = int(discipline.size());
    tableContract->setRowCount(rowCount);
    tableContract->setColumnCount(4);
    for (const auto &d: discipline) {
        auto *denumire = new QTableWidgetItem(QString::fromStdString(d.getDenumire()));
        auto *ore = new QTableWidgetItem(QString::fromStdString(std::to_string(d.getOrePeSaptamana())));
        auto *tip = new QTableWidgetItem( QString::fromStdString(d.getTip()));
        auto *profesor = new QTableWidgetItem(QString::fromStdString(d.getProfesor()));
        tableContract->setItem(row, 0, denumire);
        tableContract->setItem(row, 1, ore);
        tableContract->setItem(row, 2, tip);
        tableContract->setItem(row, 3, profesor);
        row++;
    }
}

void ContractGUI::initConnect() {
    /// buton exit
    QObject::connect(exitButton, &QPushButton::clicked, [&] () {
        close();
    });
    /// buton exit

    /// buton golire contract
    QObject::connect(emptyContractButton, &QPushButton::clicked, [&] () {
        service.emptyContractService();
        loadData(service.getAllDisciplineFromContractService());
    });
    /// buton golire contract

    /// buton generare contract
    QObject::connect(generateContractButton, &QPushButton::clicked, [&] () {
        if(!service.getAll().empty()) {
            std::mt19937 mt{std::random_device{}()};
            std::uniform_int_distribution<> dist(0, int(service.getAll().size()) - 1);
            service.generateRandomContractService(dist(mt));
            loadData(service.getAllDisciplineFromContractService());
        }
        else {
            QMessageBox::warning(this, "Warning", "Nu exista discipline in aplicatie!\n");
        }
    });
    /// buton generare contract

    /// buton export to CSV
    QObject::connect(exportToCSVButton, &QPushButton::clicked, [&] () {
        auto fileName = fileCSV->text().toStdString();
        if(!fileName.empty()) {
            auto file = fileName + ".csv";
            try {
                service.exportContractToFileCSVService(file);
                auto text = "Contract salvat in " + file;
                QMessageBox::information(this, "Info", QString::fromStdString(text));
            } catch (RepoException &ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
            }
        }
    });
    /// buton export to CSV

    /// buton export to HTML
    QObject::connect(exportToHTMLButton, &QPushButton::clicked, [&] () {
        auto fileName = fileHTML->text().toStdString();
        if(!fileName.empty()) {
            auto file = fileName + ".html";
            try {
                service.exportContractToFileHTMLService(file);
                auto text = "Contract salvat in " + file;
                QMessageBox::information(this, "Info", QString::fromStdString(text));
            } catch (RepoException &ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
            }
        }
    });
    /// buton export to HTML
}
