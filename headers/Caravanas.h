#ifndef INCLUDE_HEADERS_CARAVANAS_H_
#define INCLUDE_HEADERS_CARAVANAS_H_

#include "SimComponents.h"

class CaravanaComercio : public Caravana {
public:
  CaravanaComercio(Coords xy);

  virtual void mvEmpty();
  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);

private:
  unsigned int lifetime;
};

class CaravanaMilitar : public Caravana {
public:
  CaravanaMilitar(Coords xy);

  virtual void mvEmpty();
  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);

private:
};

class CaravanaSecreta : public Caravana {
public:
  CaravanaSecreta(Coords xy);

  virtual void mvEmpty();
  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);

private:
};

class CaravanaBarbara : public Caravana {
public:
  CaravanaBarbara(Coords xy, unsigned int tv = 60);

  virtual void mvEmpty();
  virtual void mvAuto(vector<Caravana> &usr);

private:
  unsigned int tempovida;
};

#endif // INCLUDE_HEADERS_CARAVANAS_H_
