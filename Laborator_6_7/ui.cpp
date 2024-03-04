#include "ui.h"
#include "exceptions.h"
#include <iostream>

using std::cin;
using std::cout;
using std::string;

void Ui::addUi() {
    string denumire, tip, profesor, character;
    int ore;

    cout << "Denumire: ";
    cin >> denumire;

    cout << "Numar ore: ";
    cin >> ore;

    cout << "Tip: ";
    cin >> tip;

    cout << "Profesor: ";
    cin >> profesor;

    service.addService(denumire, ore, tip, profesor);
    cout << "Disciplina adaugata!\n";
}

void Ui::deleteUi() {
    string denumire;
    cout << "Denumire: ";
    cin >> denumire;
    service.deleteService(denumire);
    cout << "Disciplina stearsa cu succes!\n";
}

void Ui::updateUi() {
    string denumire, denumireNoua, tipNou, profesorNou;
    int nrOreNou;

    cout << "Denumire: ";
    cin >> denumire;

    cout << "Denumire noua: ";
    cin >> denumireNoua;

    cout << "Numar ore nou: ";
    cin >> nrOreNou;

    cout << "Tip nou: ";
    cin >> tipNou;

    cout << "Profesor nou: ";
    cin >> profesorNou;

    service.updateService(denumire, denumireNoua, nrOreNou, tipNou, profesorNou);
    cout << "Disciplina modificata cu succes!\n";
}

void Ui::printUi(const VectDinNewDeleteT<Disciplina> &discipline) {
    if (discipline.empty()) cout << "Nu existe discipline in aplicatie!\n";
    else {
        cout << "Disciplinele sunt:\n";
        for (const auto& disciplina : discipline) {
            cout << "Denumire: " << disciplina.getDenumire() << ' ';
            cout << "Ore: " << disciplina.getOrePeSaptamana() << ' ';
            cout << "Tip: " << disciplina.getTip() << ' ';
            cout << "Profesor: " << disciplina.getProfesor() << '\n';
        }
        cout << "Sfarsit lista\n";
    }
}

void Ui::searchUi(){
    string denumire;
    cout << "Denumire: ";
    cin >> denumire;

    Disciplina disciplinaCautata = service.searchService(denumire);

    cout << "Denumire: " << disciplinaCautata.getDenumire() << ' ';
    cout << "Ore: " << disciplinaCautata.getOrePeSaptamana() << ' ';
    cout << "Tip: " << disciplinaCautata.getTip() << ' ';
    cout << "Profesor: " << disciplinaCautata.getProfesor() << '\n';
}

void Ui::filterUi(){
    string criteriu;
    cout << "Filtrare dupa ore(o)/ profesor(p): ";
    cin >> criteriu;
    if(criteriu == "o"){
        int nrOre;
        cout << "Numar ore: ";
        cin >> nrOre;
        if (service.filterNrOre(nrOre).empty())
            cout << "Nu exista discipline cautate!\n";
        else printUi(service.filterNrOre(nrOre));
    }else if(criteriu == "p") {
            string profesor;
            cout << "Profesor: ";
            cin >> profesor;
            if (service.filterProfesor(profesor).empty())
                cout << "Nu exista discipline cautate!\n";
            else printUi(service.filterProfesor(profesor));
        }
    else {
        cout << "Criteriu invalid!\n";
    }
}

void Ui::sortUi() {
    string criteriu;
    cout << "Sortare dupa denumire(d)/ ore(o)/ tip+profesor(tp): ";
    cin >> criteriu;
    if (criteriu == "d"){
        printUi(service.sortByDenumire());
    }else if (criteriu == "o"){
        printUi(service.sortByNrOre());
    }else if (criteriu == "tp"){
        printUi(service.sortByTipProfesor());
    }else{
        cout << "Criteriu invalid!\n";
    }
}

void Ui::menu() {
    cout << "_________ MENIU _________\n";
    cout << "1.Adaugare\n";
    cout << "2.Stergere\n";
    cout << "3.Modificare\n";
    cout << "4.Afisare\n";
    cout << "5.Cautare\n";
    cout << "6.Filtrare\n";
    cout << "7.Sortare\n";
    cout << "_________________________\n";
}

void Ui::runUi() {
    while(true){
        int cmd = 0;
        cout << ">>>";
        cin >> cmd;
        if (cmd == 0){
            break;
        }
        try {
            switch (cmd) {
                case 1:
                    addUi();
                    break;
                case 2:
                    deleteUi();
                    break;
                case 3:
                    updateUi();
                    break;
                case 4:
                    printUi(service.getAll());
                    break;
                case 5:
                    searchUi();
                    break;
                case 6:
                    filterUi();
                    break;
                case 7:
                    sortUi();
                    break;
                case 0:
                    return;
                default:
                    cout << "Comanda invalida!\n";
            }
        }catch (RepoException &ex){
            cout << ex.getMesaj();
        }catch (ValidateException& ex){
            cout << ex;
            cout << "\n";
        }
    }
}