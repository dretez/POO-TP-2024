#ifndef INCLUDE_HEADERS_CARAVANA_H_
#define INCLUDE_HEADERS_CARAVANA_H_

#include "Coordinates.h"
#include "Item.h"

#include <cstdlib>
#include <memory>
#include <vector>

#define MOV_USR 0
#define MOV_AUTO 1
#define MOV_EMPTY 2
#define MOV_RUN 3

using namespace std;

class CaravanaBarbara;

class Caravana {
public:
  Caravana(Coords xy, int trip, unsigned int capT, unsigned int capC,
           unsigned int capA);

  Coords getPos();

  void setPos(Coords pos);
  Coords getPos(Coords pos);

  void resetQueuedMoves();

  void setMvMode(unsigned int mode);
  unsigned int getMvMode();

  virtual void mvUsr(Coords dir);
  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);
  virtual void mvEmpty();

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

protected:
  unsigned int mvMode, mvQueue, maxMvQueue;

private:
  int id;
  Coords pos;
  vector<Coords> targetpos;
  unsigned int capTrip, capMerc, capAgua;
  unsigned int tripulantes, mercadoria, agua;
};

class CaravanaComercio : public Caravana {
public:
  CaravanaComercio(Coords xy);

  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);
  virtual void mvEmpty();

private:
  unsigned int lifetime;
};

class CaravanaMilitar : public Caravana {
public:
  CaravanaMilitar(Coords xy);

  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);
  virtual void mvEmpty();
};

class CaravanaSecreta : public Caravana {
public:
  CaravanaSecreta(Coords xy);

  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);
  virtual void mvEmpty();
};

class CaravanaBarbara : public Caravana {
public:
  CaravanaBarbara(Coords xy, unsigned int tv = 60);

  virtual void mvAuto(vector<Caravana> &usr);
  virtual void mvEmpty();

private:
  unsigned int tempovida;
};

#endif // INCLUDE_HEADERS_CARAVANA_H_
