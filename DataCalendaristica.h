#ifndef __DATACALENDARISTICA_H__
#define __DATACALENDARISTICA_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class DataCalendaristica {
  int zi, luna, an;

public:
  DataCalendaristica(int zi, int luna, int an) {
    if (!dataValida(zi, luna, an)) {
      throw invalid_argument("Data invalida: " + to_string(zi) + "/" +
                             to_string(luna) + "/" + to_string(an));
    }
    this->zi = zi;
    this->luna = luna;
    this->an = an;
  }
  bool esteAnBisect(int) const;
  bool dataValida(int, int, int) const;
  int zileInLuna(int, int) const;
  int getZi() const;
  int getLuna() const;
  int getAn() const;
  void set(int z, int l, int a) {
    if (!dataValida(z, l, a)) {
      throw invalid_argument("Data invalida la setare.");
    }
    zi = z;
    luna = l;
    an = a;
  }

  string toString() const {
    return to_string(zi) + "/" + to_string(luna) + "/" + to_string(an);
  }
};

#endif // __DATACALENDARISTICA_H__