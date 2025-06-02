#ifndef __PRODUS_H__
#define __PRODUS_H__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Produs{
    string cod_de_bare;
    string denumire;
    int cantitate;
    double pret;
public:
    string getCodDeBare() const;
    string getDenumire() const;
    int getCantitate() const;
    double getPret() const;
    void setCodDeBare(const string&);
    void setDenumire(const string&);
    void setCantitate(int);
    void setPret(double);
    friend ostream& operator<<(ostream&, const Produs&);
};


#endif // __PRODUS_H__