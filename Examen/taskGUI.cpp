#include "taskGUI.h"

void TaskGUI::initGUI() {
    auto lyButtons = new QVBoxLayout;
    lyButtons->addWidget(addButton);
    lyButtons->addWidget(searchButton);
    lyButtons->addWidget(ShowAll);

    auto textBox = new QFormLayout;
    textBox->addRow("ID", text_id);
    textBox->addRow("Descriere", text_descriere);
    textBox->addRow("Stare", text_stare);
    textBox->addRow("Numar programatori", text_nr_programator);
    textBox->addRow("Programator 1", text_programator1);
    textBox->addRow("Programator 2", text_programator2);
    textBox->addRow("Programator 3", text_programator3);
    textBox->addRow("Programator 4", text_programator4);

    auto lyLeft = new QVBoxLayout;
    lyLeft->addWidget(table);

    auto lyRight = new QVBoxLayout;
    lyRight->addLayout(textBox);
    lyRight->addLayout(lyButtons);

    auto lyMain = new QHBoxLayout;
    lyMain->addLayout(lyLeft);
    lyMain->addLayout(lyRight);

    setLayout(lyMain);
}

void TaskGUI::initConnect() {
    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        if (table->selectionModel()->selectedIndexes().isEmpty()) {
            text_id->setText("");
            text_descriere->setText("");
            text_nr_programator->setText("");
            text_programator1->setText("");
            text_programator2->setText("");
            text_programator3->setText("");
            text_programator4->setText("");
            text_stare->setText("");
            return;
        }
        int selRow = table->selectionModel()->selectedIndexes().at(0).row();
        auto cel0Index = table->model()->index(selRow, 0);
        auto cel1Index = table->model()->index(selRow, 1);
        auto cel2Index = table->model()->index(selRow, 2);
        auto cel3Index = table->model()->index(selRow, 3);
        auto cellValue= table->model()->data(cel0Index, Qt::DisplayRole).toString();
        text_id->setText(cellValue);
        int id = cellValue.toInt();
        auto t = service.cauta_dupa_id(id);

        text_programator1->setText(QString::fromStdString(t.get_programatori()[0]));
        text_programator2->setText(QString::fromStdString(t.get_programatori()[1]));

        cellValue = table->model()->data(cel1Index, Qt::DisplayRole).toString();
        text_descriere->setText(cellValue);
        cellValue = table->model()->data(cel2Index, Qt::DisplayRole).toString();
        text_stare->setText(cellValue);
        cellValue = table->model()->data(cel3Index, Qt::DisplayRole).toString();
        text_nr_programator->setText(cellValue);
    });

    QObject::connect(addButton, &QPushButton::clicked, [&] () {
        auto id = text_id->text().toInt();
        auto descriere = text_descriere->text().toStdString();
        auto stare = text_stare->text().toStdString();
        auto programator1 = text_programator1->text().toStdString();
        auto programator2 = text_programator1->text().toStdString();
        auto programator3 = text_programator1->text().toStdString();
        auto programator4 = text_programator1->text().toStdString();
        vector<string> programatori_vec;
        if (!programator1.empty()) programatori_vec.push_back(programator1);
        if (!programator2.empty()) programatori_vec.push_back(programator2);
//        if (!programator3.empty()) programatori_vec.push_back(programator3);
//        if (!programator4.empty()) programatori_vec.push_back(programator4);
        try {
            service.add_service(id, descriere, programatori_vec, stare);
            loadData(service.get_all_sorted());
        }catch (ValidateException& ex) {
            std::stringstream sout;
            sout << ex;
            auto mesaj = sout.str();
            QMessageBox::warning(this, "Warning",QString::fromStdString(mesaj));
        } catch (RepoException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
        }
    });

    QObject::connect(searchButton, &QPushButton::clicked, [&] () {
        auto nume = text_programator1->text();
        loadData(service.cauta_programator(nume.toStdString()));
    });

    QObject::connect(ShowAll, &QPushButton::clicked, [&] () {
        loadData(service.get_all_sorted());
    });
}

void TaskGUI::loadData(const vector<Task>& tasks) {
    model->setTasks(tasks);
}
