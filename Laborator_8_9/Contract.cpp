#include "Contract.h"

void Contract::addToContract(const Disciplina& disciplina) {
    contract.push_back(disciplina);
}

void Contract::emptyContract(){
    contract.clear();
}

void Contract::generateContract(int nrDiscipline,  const vector<Disciplina>& allDiscipline) {
    contract.clear();
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, int(allDiscipline.size()) - 1);
    vector<int> freq;

    int randomNumber = dist(mt);
    freq.push_back(randomNumber);

    for (int i = 0 ; i < nrDiscipline - 1; i++) {
        randomNumber = dist(mt);
        auto it = std::find(freq.begin(), freq.end(), randomNumber);
        if (it != freq.end()) {
            i--;
        }else { freq.push_back(randomNumber); }
    }

    for (const int& i: freq){
        contract.push_back(allDiscipline[i]);
    }
}

const vector<Disciplina>& Contract::getAll(){
    return contract;
}

void Contract::deleteDisciplinaDinContract(const string& denumire) {
    auto it = find_if(contract.begin(), contract.end(), [denumire] (const Disciplina& d) {
       return d.getDenumire() == denumire;
    });
    if(it != contract.end()){
        contract.erase(it);
    }
}

void Contract::updateDisciplinaDinContract(const string& denumire, const Disciplina& disciplinaNoua) {
    auto it = find_if(contract.begin(), contract.end(), [denumire] (const Disciplina& d) {
       return d.getDenumire() == denumire;
    });
    if(it != contract.end()){
        contract.erase(it);
        contract.insert(it, disciplinaNoua);
    }
}

void Contract::exportContractToFileCSV(const string& fileName) {
    std::ofstream out(fileName, std::ios::trunc);
    if (!out.is_open()) {
        throw RepoException("Nu se poate deschide: " + fileName);
    }

    for(const Disciplina& d: contract){
        out << d.getDenumire() << ',' << d.getOrePeSaptamana() << ',';
        out << d.getTip() << ',' << d.getProfesor() << '\n';
    }
    out.close();
}

void Contract::exportContractToFileHTML(const string& fileName) {
    std::ofstream out(fileName, std::ios::trunc);
    if (!out.is_open()) {
        throw RepoException("Nu se poate deschide: " + fileName);
    }
    out << "<html><body>" << std::endl;
    out << R"(<table border="1" style="width:100%">)" << std::endl;
    for (const auto& d : contract) {
        out << "<tr>" << std::endl;
        out << "<td>" << d.getDenumire() << "</td>"<<std::endl;
        out << "<td>" << d.getOrePeSaptamana() << "</td>" << std::endl;
        out << "<td>" << d.getTip() << "</td>" << std::endl;
        out << "<td>" << d.getProfesor() << "</td>" << std::endl;
        out << "</tr>" << std::endl;
    }
    out << "</table>" << std::endl;
    out << "</body></html>" << std::endl;
    out.close();
}