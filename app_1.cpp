#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Produs.h"
#include "DataCalendaristica.h"
using namespace std;

vector<Produs> citireStoc(const string& numeFile){
    vector<Produs> stoc;
    ifstream fin(numeFile);
    if(!fin){
        cout<<"Eroare: nu s-a putut deschide fisierul "<<numeFile<<endl;
        return stoc;
    }
    int nrProduse;
    fin>>nrProduse;
    for(int i=0; i<nrProduse; i++){
        Produs p;
        string cod_de_bare, denumire;
        int cantitate;;
        double pret;
        fin>>cod_de_bare>>denumire>>cantitate>>pret;
        p.setCodDeBare(cod_de_bare);
        p.setDenumire(denumire);
        p.setCantitate(cantitate);
        p.setPret(pret);
        stoc.push_back(p);
    }
    fin.close();
    return stoc;
}

void vizualizareComenzi(const string& numeFisier) {
    ifstream fin(numeFisier);
    if (!fin) {
        cout << "Eroare: nu s-a putut deschide fisierul " << numeFisier << endl;
        return;
    }

    vector<Produs> stoc = citireStoc("stoc.txt");

    int zi, luna, an;
    string linie;
    while (fin >> zi >> luna >> an) {
        fin.ignore(); 
        getline(fin, linie); 

        try {
            DataCalendaristica data(zi, luna, an);
            cout << "Data comenzii: " << data.toString() << endl;
        } catch (const exception& e) {
            cout << "Eroare data invalida in fisier: " << e.what() << endl;
            continue;
        }

        istringstream ss(linie);
        string cod;
        while (ss >> cod) {
            bool gasit = false;
            for (const auto& p : stoc) {
                if (p.getCodDeBare() == cod) {
                    cout << "  - " << p.getDenumire() << " -> Cod de bare: " << p.getCodDeBare()
                         << "  Cantitate: " << p.getCantitate()
                         << "  Pret: " << p.getPret()  << endl;
                    gasit = true;
                    break;
                }
            }
            if (!gasit) {
                cout << "  - Cod necunoscut: " << cod << " (nu exista in stoc)" << endl;
            }
        }
        cout << "--------------------------------------------" << endl;
    }

    fin.close();
}



int main(int argc, char *argv[]){
    if(argc>1){
        string comanda = argv[1];
        if(comanda=="vizualizare_produse_de_pe_stoc"){
            if(argc!=2){
                cout<<"Sintaxa invalida!"<<endl<<"Sintaxa corecta: ./app_1.exe vizualizare_produs_de_pe_stoc"<<endl;
                return 1;
            }
            vector<Produs> stoc = citireStoc("stoc.txt");
            for(const auto& produs : stoc){
                cout<<produs<<endl;
            }
            }else if(comanda=="adaugare_produs"){
                if(argc!=6){
                    cout<<"Sintaxa invalida!"<<endl<<"Sintaxa corecta: ./app_1.exe adaugare_produs <cod_de_bare> <denumire> <cantitate> <pret>"<<endl;
                    return 1;
                }
            vector<Produs> stoc = citireStoc("stoc.txt");
            Produs p;
            string cod_de_bare, denumire;
            int cantitate;
            double pret;
            cod_de_bare = argv[2];
            denumire = argv[3];
            cantitate = stoi(argv[4]);
            pret = stod(argv[5]);
            p.setCodDeBare(cod_de_bare);
            p.setDenumire(denumire);
            p.setCantitate(cantitate);
            p.setPret(pret);
            stoc.push_back(p);
            ofstream fout("stoc.txt");
            if (!fout) {
                cout << "Eroare: nu s-a putut deschide fisierul pentru scriere." << endl;
                return 1;
            }
            fout << stoc.size() << endl;
            for(const auto& produs : stoc){
                fout<<produs<< endl;
            }
            fout.close();
            cout<<"Produsul "<<denumire<<" a fost adaugat."<<endl;
        }else if(comanda=="stergere_produs"){
            if (argc!=3) {
                cout << "Sintaxa invalida!"<<endl<<"Sintaxa corecta: ./app_1.exe stergere_produs <cod_de_bare>" << endl;
                return 1;
            }
            vector<Produs> stoc = citireStoc("stoc.txt");
            string cod_de_bare = argv[2];
            vector<Produs> stocNou;
            for (const auto& produs : stoc) {
                if (produs.getCodDeBare() != cod_de_bare) {
                    stocNou.push_back(produs);
                }
            }
            ofstream fout("stoc.txt");
            if (!fout) {
                cout << "Eroare: nu s-a putut deschide fisierul pentru scriere." << endl;
                return 1;
            }
            stoc = stocNou;
            fout << stoc.size() << endl;
            for(const auto& produs : stoc){
                fout<<produs<<endl;
            }
            fout.close();
            cout<<"Produsul cu codul de bare "<<cod_de_bare<<" a fost sters."<<endl;
        }else if(comanda=="modificare_produs"){
            if(argc!=4){
                cout<<"Sintaxa invalida!"<<endl<<"Sintaxa corecta: ./app_1.exe modificare_produs <preț/cantitate> <cod_de_bare> <nr. corespunzător preț/nr. corespunzător cantitate>"<<endl;
                return 1;
            }
            vector<Produs> stoc = citireStoc("stoc.txt");
            string modificare = argv[2];
            string cod_de_bare = argv[3];
            if(modificare=="pret"){
                double pret = stod(argv[4]);
                for(auto& produs : stoc){
                    if(produs.getCodDeBare() == cod_de_bare){
                        produs.setPret(pret);
                        break;
                    }
                }
            }
            if(modificare=="cantitate"){
                int cantitate = stoi(argv[4]);
                for(auto& produs : stoc){
                    if(produs.getCodDeBare() == cod_de_bare){
                        produs.setCantitate(cantitate);
                        break;
                    }
                }
            }
        }else if (comanda == "vizualizare_comenzi") {
            if (argc != 2) {
                cout<<"Sintaxa invalida!"<<endl<<"Sintaxa corecta: ./app_1.exe vizualizare_comenzi"<<endl;
                return 1;
            }
            vizualizareComenzi("comenzi.txt");
        }
        else{
            cout<<"Comanda necunoscuta: "<<comanda<<endl;
        }
    } else{
        cout<<"Nu s-a specificat nicio comanda."<<endl;
    }
    return 0;
}