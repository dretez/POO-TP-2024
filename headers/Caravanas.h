#ifndef INCLUDE_HEADERS_CARAVANAS_H_
#define INCLUDE_HEADERS_CARAVANAS_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Coordinates.h"

#define MOV_USR 0
#define MOV_AUTO 1
#define MOV_EMPTY 2
#define MOV_RUN 3

class Caravana;
class CaravanaBarbara;
class Item;

class RandCaravanGenerator {
public:
  static void gen(vector<shared_ptr<Caravana>> &to, Coords);
};

class Caravana {
public:
  Caravana(Coords xy, int trip, unsigned int capT, unsigned int capC,
           unsigned int capA, unsigned int lifetime);

  int getId();
  string info() const;
  virtual string getTipo() const;

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
  int changeMerc(int qtd);

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
  virtual void mvAuto(const vector<shared_ptr<Caravana>> &usr,
                      const vector<shared_ptr<Caravana>> &enemy,
                      const vector<shared_ptr<Item>> &);

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

  virtual string getTipo() const;

  virtual void mvEmpty();
  virtual void mvAuto(const vector<shared_ptr<Caravana>> &usr,
                      const vector<shared_ptr<Caravana>> &enemy,
                      const vector<shared_ptr<Item>> &);
};

class CaravanaMilitar : public Caravana {
public:
  CaravanaMilitar(Coords xy);

  virtual string getTipo() const;

  virtual void mvEmpty();
  virtual void mvAuto(const vector<shared_ptr<Caravana>> &usr,
                      const vector<shared_ptr<Caravana>> &enemy,
                      const vector<shared_ptr<Item>> &);
};

class CaravanaSecreta : public Caravana {
public:
  CaravanaSecreta(Coords xy);

  virtual string getTipo() const;

  virtual void mvEmpty();
  virtual void mvAuto(const vector<shared_ptr<Caravana>> &usr,
                      const vector<shared_ptr<Caravana>> &enemy,
                      const vector<shared_ptr<Item>> &);
};

class CaravanaBarbara : public Caravana {
public:
  CaravanaBarbara(Coords xy, unsigned int lt = 60);

  virtual string getTipo() const;

  virtual void mvEmpty();
  virtual void mvAuto(const vector<shared_ptr<Caravana>> &usr,
                      const vector<shared_ptr<Caravana>> &enemy,
                      const vector<shared_ptr<Item>> &);
};

#endif // INCLUDE_HEADERS_CARAVANAS_H_
