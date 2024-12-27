#ifndef INCLUDE_HEADERS_CARAVANAS_H_
#define INCLUDE_HEADERS_CARAVANAS_H_

#include <map>
#include <vector>

#include "Coordinates.h"

#define MOV_USR 0
#define MOV_AUTO 1
#define MOV_EMPTY 2
#define MOV_RUN 3

class CaravanaBarbara;
class Item;

class Caravana {
public:
  Caravana(Coords xy, int trip, unsigned int capT, unsigned int capC,
           unsigned int capA, unsigned int lifetime);

  void setPos(Coords pos);
  Coords getPos();

  bool ownedByUsr();

  unsigned int getMaxAgua();
  unsigned int getAgua();
  void usaAgua(unsigned int qtd);
  int changeAgua(int qtd);
  void refillAgua();

  unsigned int getMaxMerc();
  unsigned int getMerc();
  void setMerc(unsigned int n);
  void changeMerc(int qtd);

  unsigned int getMaxTripulantes();
  unsigned int getTripulantes();
  void setTripulantes(unsigned int n);
  int changeTripulantes(int n);

  unsigned int getLifetime();
  void setMvMode(unsigned int mode);
  unsigned int getMvMode();
  map<unsigned int, Coords> &getTargetPath();
  void resetTargetPath();
  void mv(Coords dir);
  virtual void mvEmpty();
  virtual void mvAuto(const vector<Caravana> &usr,
                      const vector<CaravanaBarbara> &enemy,
                      const vector<Item> &);

  unsigned int attack();

protected:
  unsigned int getMaxMvs();

  unsigned int mvMode, maxTargPathSize;
  unsigned int lifetime;

private:
  int id;
  Coords pos;
  map<unsigned int, Coords> targetPath;
  unsigned int capTrip, capMerc, capAgua;
  unsigned int tripulantes, mercadoria, agua;
  bool superSpeed, userOwned;
};

class CaravanaComercio : public Caravana {
public:
  CaravanaComercio(Coords xy);

  virtual void mvEmpty();
  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);
};

class CaravanaMilitar : public Caravana {
public:
  CaravanaMilitar(Coords xy);

  virtual void mvEmpty();
  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);
};

class CaravanaSecreta : public Caravana {
public:
  CaravanaSecreta(Coords xy);

  virtual void mvEmpty();
  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);
};

class CaravanaBarbara : public Caravana {
public:
  CaravanaBarbara(Coords xy, unsigned int lt = 60);

  virtual void mvEmpty();
  virtual void mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &);
};

#endif // INCLUDE_HEADERS_CARAVANAS_H_
