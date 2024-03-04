#include "disciplinaGUI.h"

void DisciplinaGUI::initGUI() {
    auto lyButtons1 = new QHBoxLayout;
    lyButtons1->addWidget(addButton);
    lyButtons1->addWidget(deleteButton);
    lyButtons1->addWidget(updateButton);

    auto lyButtons2 = new QHBoxLayout;
    lyButtons2->addWidget(filterOreButton);
    lyButtons2->addWidget(filterProfButton);

    auto lyButtons3 = new QHBoxLayout;
    lyButtons3->addWidget(sortByDenumireButton);
    lyButtons3->addWidget(sortByNrOreButton);
    lyButtons3->addWidget(sortByTipProfesorButton);

    auto lyButtons4 = new QHBoxLayout;
    lyButtons4->addWidget(clearTextButton);
    lyButtons4->addWidget(showAllDisciplineButton);
    lyButtons4->addWidget(exitButton);

    auto lyButtons5 = new QHBoxLayout;
    lyButtons5->addWidget(undoButton);
    lyButtons5->addWidget(addContractButton);
    lyButtons5->addWidget(contractButton);

    auto lyTextBox = new QFormLayout;
    lyTextBox->addRow("Denumire", textDenumire);
    lyTextBox->addRow("Numar ore", textOre);
    lyTextBox->addRow("Tip", textTip);
    lyTextBox->addRow("Profesor", textProfesor);

    auto lyRight = new QVBoxLayout;
    lyRight->addLayout(lyTextBox);
    lyRight->addLayout(lyButtons1);
    lyRight->addLayout(lyButtons2);
    lyRight->addLayout(lyButtons3);
    lyRight->addLayout(lyButtons5);
    lyRight->addLayout(lyButtons4);
    lyRight->addLayout(lyBtnDy);

    auto lyLeft = new QHBoxLayout;
    lyLeft->addWidget(listDiscipline);

    auto lyMain = new QHBoxLayout;
    lyMain->addLayout(lyLeft);
    lyMain->addLayout(lyRight);

    setLayout(lyMain);
}

void DisciplinaGUI::update() {
    loadData(service.getAll());
}

void DisciplinaGUI::loadData(const std::vector<Disciplina> &discipline) {
    listDiscipline->clear();
    for(const auto& d: discipline){
        auto *item  = new QListWidgetItem(QString::fromStdString(d.getDenumire()));
        item->setData(Qt::UserRole, QString::fromStdString(d.getDenumire()));
        listDiscipline->addItem(item);
    }
}

void DisciplinaGUI::initConnect() {
    service.addObserver(this);
    /// buton de exit
    QObject::connect(exitButton, &QPushButton::clicked, [&] () {
        auto ret = QMessageBox::question(this, "Proiect", "Doriti sa parasiti aplicatia?");
        if(ret == QMessageBox::Yes) {
            close();
        }
    });
    /// buton de exit

    /// buton de clear text
    QObject::connect(clearTextButton, &QPushButton::clicked, [&] () {
        textDenumire->clear();
        textOre->clear();
        textTip->clear();
        textProfesor->clear();
    });
    /// buton de clear text

    /// buton de aratat toate disciplinele
    QObject::connect(showAllDisciplineButton, &QPushButton::clicked, [&] () {
        loadData(service.getAll());
    });
    /// buton de aratat toate disciplinele

    /// buton de adaugare
    QObject::connect(addButton, &QPushButton::clicked, [&] () {
        auto denumire = textDenumire->text();
        auto nrOre = textOre->text();
        auto tip = textTip->text();
        auto profesor = textProfesor->text();
        try {
            service.addService(denumire.toStdString(), nrOre.toInt(), tip.toStdString(), profesor.toStdString());
            textDenumire->clear();
            textOre->clear();
            textTip->clear();
            textProfesor->clear();
        }catch (ValidateException &ex) {
            std::stringstream sout;
            sout << ex;
            auto mesaj = sout.str();
            QMessageBox::warning(this, "Warning", QString::fromStdString(mesaj));
        }catch (RepoException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
        }
        loadData(service.getAll());
        //addButtons();
    });
    /// buton de adaugare

    ///buton de stergere
    QObject::connect(deleteButton, &QPushButton::clicked, [&] () {
        auto denumire = textDenumire->text();
        try {
            service.deleteService(denumire.toStdString());
        }catch (RepoException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
        }
        textDenumire->clear();
        textOre->clear();
        textTip->clear();
        textProfesor->clear();
        loadData(service.getAll());
    });
    ///buton de stergere

    /// buton de modificare aka update
    QObject::connect(updateButton, &QPushButton::clicked, [&] () {
        auto denumire = textDenumire->text().toStdString();
        auto nrOreNou = textOre->text().toInt();
        auto tipNou = textTip->text().toStdString();
        auto profesorNou = textProfesor->text().toStdString();
        try {
            service.updateService(denumire, nrOreNou, tipNou, profesorNou);
            loadData(service.getAll());
        } catch (RepoException &ex){
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
        } catch (ValidateException &ex) {
            std::stringstream sout;
            sout << ex;
            auto mesaj = sout.str();
            QMessageBox::warning(this, "Warning", QString::fromStdString(mesaj));
        }
    });
    /// buton de modificare aka update

    /// buton filtrare dupa ore
    QObject::connect(filterOreButton, &QPushButton::clicked, [&] () {
        auto oreFilter = textOre->text();
        loadData(service.filterNrOre(oreFilter.toInt()));
    });
    /// buton filtrare dupa ore

    /// buton filtrare dupa profesor
    QObject::connect(filterProfButton, &QPushButton::clicked, [&] () {
        auto profesorFilter = textProfesor->text();
        loadData(service.filterProfesor(profesorFilter.toStdString()));
    });
    /// buton filtrare dupa profesor

    /// buton sortare dupa denumire
    QObject::connect(sortByDenumireButton, &QPushButton::clicked, [&] () {
        loadData(service.sortByDenumire());
    });
    /// buton sortare dupa denumire

    /// buton sortare dupa ore
    QObject::connect(sortByNrOreButton, &QPushButton::clicked, [&] () {
        loadData(service.sortByNrOre());
    });
    /// buton sortare dupa ore

    /// buton sortare dupa tip+profesor
    QObject::connect(sortByTipProfesorButton, &QPushButton::clicked, [&] () {
        loadData(service.sortByTipProfesor());
    });
    /// buton sortare dupa tip+profesor

    /// buton undo
    QObject::connect(undoButton, &QPushButton::clicked, [&] () {
        try {
            service.undoService();
            loadData(service.getAll());
        }catch (ServiceException &ex){
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
        }
    });
    /// buton undo

    /// selectie lista
    QObject::connect(listDiscipline, &QListWidget::itemSelectionChanged, [&] () {
       auto selectie = listDiscipline->selectedItems();
       if (selectie.isEmpty()) {
           textDenumire->setText("");
           textOre->setText("");
           textTip->setText("");
           textProfesor->setText("");
       }
       else {
           auto itemSelected = selectie.at(0);
           auto denumire = itemSelected->text();
           auto disciplina = service.searchService(denumire.toStdString());
           textDenumire->setText(denumire);
           textOre->setText(QString::number(disciplina.getOrePeSaptamana()));
           textTip->setText(QString::fromStdString(disciplina.getTip()));
           textProfesor->setText(QString::fromStdString(disciplina.getProfesor()));
       }
    });
    /// selectie lista

    /// buton adaugare disciplina la contract
    QObject::connect(addContractButton, &QPushButton::clicked, [&] () {
        vector<string> denumiri;
        auto denumire = textDenumire->text().toStdString();
        if(!denumire.empty()) {
            denumiri.push_back(denumire);
            try {
                service.addToContractService(denumiri);
            }catch (RepoException &ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
            }
        }
    });
    /// buton adaugare disciplina la contract

    /// buton intrare contract
    QObject::connect(contractButton, &QPushButton::clicked, [&] () {
            auto contractGUI = new ContractGUI(service);
            contractGUI->resize(850, 200);
            contractGUI->show();
    });
    /// buton intrare contract
}

void DisciplinaGUI::addButtons() {
    auto map = service.funcNoua();
    for(const auto &c: map){
        if(c.second > 0) {
            auto btn = new QPushButton{QString::fromStdString(c.first)};
            lyBtnDy->addWidget(btn);
            QObject::connect(btn, &QPushButton::clicked, [this, btn, c]() {
                QMessageBox::information(nullptr, "Info", QString::number(c.second));
                delete btn;
            });
        }
    }
}