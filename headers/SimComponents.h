#ifndef INCLUDE_HEADERS_CARAVANA_H_
#define INCLUDE_HEADERS_CARAVANA_H_

#include <cstdlib>
#include <map>
#include <memory>
#include <vector>

#include "Cidade.h"
#include "Coordinates.h"
#include "MapCells.h"

using namespace std;

class User;
class Deserto;
class Item;
class Caravana;
class CaravanaBarbara;

class User {
public:
  User(Deserto &mapa, int money, vector<Caravana> &cars);

  void buyCaravana(Cidade &cid, int preco = 100);
  void buyTripulante(Caravana &car, unsigned int qtd);
  void buyMercadoria(Caravana &car, unsigned int qtd, int preco = 1);
  void sellMercadoria(Caravana &car, int preco = 2);

  int getMoedas();
  void setMoedas(int);
  void changeMoedas(int);

private:
  int moedas;
  Deserto &world;
  vector<Caravana> &caravanas;
};

class Deserto : private Coords {
public:
  Deserto(unsigned int w, unsigned int h);

  Cell &getRandomFreeCell();
  vector<Item> &getAllItems();

  Cell &operator[](Coords);

private:
  unsigned int maxItens;
  vector<Cell> mapa;
  vector<Item> itens;
};

#define ITEM_PANDORA 0
#define ITEM_TESOURO 1
#define ITEM_JAULA 2
#define ITEM_MINA 3
#define ITEM_SURPRESA 4

class Item {
public:
  Item(Coords xy, int tv = 20);

  int getTipo();
  Coords getPos();
  void decrTempoVida();

private:
  int tempovida, tipo;
  Coords pos;
};

#define MOV_USR 0
#define MOV_AUTO 1
#define MOV_EMPTY 2
#define MOV_RUN 3

class Caravana {
public:
  Caravana(Coords xy, int trip, unsigned int capT, unsigned int capC,
           unsigned int capA);

  void setPos(Coords pos);
  Coords getPos();

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

  void setMvMode(unsigned int mode);
  unsigned int getMvMode();
  map<unsigned int, Coords> getTargetPath();
  void resetTargetPath();
  void mv(Coords dir);
  virtual void mvEmpty();
  virtual void mvAuto(const vector<Caravana> &usr,
                      const vector<CaravanaBarbara> &enemy,
                      const vector<Item> &);

  int attack();
  int apanhaItem(vector<Item> &, vector<Item>::iterator &, User &);

protected:
  unsigned int mvMode, maxTargPathSize;

private:
  int id;
  Coords pos;
  map<unsigned int, Coords> targetPath;
  unsigned int capTrip, capMerc, capAgua;
  unsigned int tripulantes, mercadoria, agua;
};

#endif // INCLUDE_HEADERS_CARAVANA_H_
