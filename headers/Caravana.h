#ifndef INCLUDE_HEADERS_CARAVANA_H_
#define INCLUDE_HEADERS_CARAVANA_H_

#include "Coordinates.h"
#include "Item.h"

class Caravana {
public:
  Caravana(Coords xy, int trip, unsigned int capT, unsigned int capC,
           unsigned int capA);

  Coords getPos();

  void mov();
  void movAuto();
  void movEmpty();

  unsigned int getMaxAgua();
  unsigned int getAgua();
  void usaAgua(unsigned int qtd);
  void refillAgua();

  unsigned int getMaxMerc();
  unsigned int getMerc();
  void setMerc(unsigned int n);
  void changeMerc(int qtd);

  unsigned int getMaxTripulantes();
  unsigned int getTripulantes();
  void setTripulantes(unsigned int n);
  void changeTripulantes(int n);

  void apanhaItem(Item i);

  int attack();

private:
  int id;
  Coords pos;
  unsigned int capTrip, capMerc, capAgua;
  unsigned int tripulantes, mercadoria, agua;
  int modoDesloc;
};

class CaravanaComercio : public Caravana {
public:
  CaravanaComercio(Coords xy);
};

class CaravanaMilitar : public Caravana {
public:
  CaravanaMilitar(Coords xy);
};

class CaravanaSecreta : public Caravana {
public:
  CaravanaSecreta(Coords xy);
};

class CaravanaBarbara : public Caravana {
public:
  CaravanaBarbara(Coords xy, unsigned int tv = 60);

private:
  unsigned int tempovida;
};

#endif // INCLUDE_HEADERS_CARAVANA_H_
