#include "ui.h"

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

void Ui::printUi(const vector<Disciplina> &discipline) {
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

void Ui::createContractUi() {
    if (service.getAll().empty()){
        cout << "Nu exista discipline in aplicatie!\n";
        return;
    }

    if (!service.getAllDisciplineFromContractService().empty()){
        cout << "Goliti contractul curent pentru a creea altul!\n";
        return;
    }

    vector<string> denumiri;
    string denumireDisciplina;

    cout << "Alegeti disciplinele: ";
    cin.get();
    while(cin.peek() != '\n' && cin >> denumireDisciplina){
        denumiri.push_back(denumireDisciplina);
    }

    auto allDiscipline = service.getAll();
    for (const string& den: denumiri) {
        auto it = std::find_if(allDiscipline.begin(), allDiscipline.end(), [den] (const Disciplina& dis) {
            return den == dis.getDenumire();
        });
        if (it == allDiscipline.end()){
            cout << "Ati introdus discipline inexistente!\n";
            return;
        }
    }

    service.addToContractService(denumiri);
    cout << "Contract creat cu succes!\n";
    cout << "Nr discipline contract: ";
    cout << service.nrDisciplineContract() << std::endl;
}

void Ui::emptyContractUi() {
    if (service.getAll().empty()) {
        cout << "Nu exista discipline in aplicatie!\n";
        return;
    }
    service.emptyContractService();
    cout << "Contractul a fost golit.\n";
    cout << "Nr discipline contract: ";
    cout << service.nrDisciplineContract() << std::endl;
}

void Ui::generateContractUi() {
    if (service.getAll().empty()) {
        cout << "Nu exista discipline in aplicatie!\n";
        return;
    }

    cout << "Introduceti numarul de dicipline: ";
    int nrDiscipline;
    cin >> nrDiscipline;
    if (nrDiscipline > service.getAll().size()) {
        cout << "Numar discipline prea mare!\n";
        return;
    }
    service.generateRandomContractService(nrDiscipline);
    cout << "Contract generat cu succes!\n";
    cout << "Nr discipline contract: ";
    cout << service.nrDisciplineContract() << std::endl;
}

void Ui::printContractUi(const vector<Disciplina>& discipline) {
    if (discipline.empty()) cout << "Nu exista discipline in contract!\n";
    else {
        cout << "Contractul este:\n";
        for (const auto& disciplina : discipline) {
            cout << "Denumire: " << disciplina.getDenumire() << ' ';
            cout << "Ore: " << disciplina.getOrePeSaptamana() << ' ';
            cout << "Tip: " << disciplina.getTip() << ' ';
            cout << "Profesor: " << disciplina.getProfesor() << '\n';
        }
    }
    cout << "Nr discipline contract: ";
    cout << service.nrDisciplineContract() << std::endl;
}

void Ui::exportToFileUi() {
    if(service.nrDisciplineContract() == 0){
        cout << "Nu exista discipline in contract!\n";
        return;
    }

    string fileName;
    cout << "Alegeti fisierul: ";
    cin >> fileName;

    if(fileName.substr(fileName.find_last_of('.') + 1) == "csv"){
        service.exportContractToFileCSVService(fileName);
        cout << "Contractul a fost salvat cu succes!\n";
    }
    else if(fileName.substr(fileName.find_last_of('.') + 1) == "html") {
        service.exportContractToFileHTMLService(fileName);
        cout << "Contractul a fost salvat cu succes!\n";
    }
    else{
        cout << "Extensie invalida de fisier!\n";
        return;
    }

    cout << "Nr discipline contract: ";
    cout << service.nrDisciplineContract() << std::endl;
}

void Ui::undoUi() {
    service.undoService();
}

void Ui::funcNoua() {
    auto map = service.funcNoua();
    cout << "Tip Aparitii\n";
    for(const auto& d: map)
    {
        cout << d.first << "       " << d.second << std::endl;
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
    cout << "8.Creare contract\n";
    cout << "9.Golire contract\n";
    cout << "10.Generare contract\n";
    cout << "11.Afisare contract\n";
    cout << "12.Salvare contract in fisier\n";
    cout << "13.Undo\n";
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
                case 8:
                    createContractUi();
                    break;
                case 9:
                    emptyContractUi();
                    break;
                case 10:
                    generateContractUi();
                    break;
                case 11:
                    printContractUi(service.getAllDisciplineFromContractService());
                    break;
                case 12:
                    exportToFileUi();
                    break;
                case 13:
                    undoUi();
                    break;
                case 20:
                    funcNoua();
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
        }catch (ServiceException &ex){
            cout << ex.getMesaj();
        }
    }
}