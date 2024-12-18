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

  int getAgua();
  void usaAgua(unsigned int qtd);
  void refillAgua();

  int getTripulantes();
  void setTripulantes(unsigned int n);

  void apanhaItem(Item i);

private:
  int id;
  Coords pos;
  unsigned int capTrip, capMerc, capAgua;
  int tripulantes, mercadoria, agua;
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
