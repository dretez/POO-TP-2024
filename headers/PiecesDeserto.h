#ifndef INCLUDE_HEADERS_PIECESDESERTO_H_
#define INCLUDE_HEADERS_PIECESDESERTO_H_

#include "Caravana.h"
#include "Coordinates.h"

#include <cstdlib>
#include <memory>
#include <vector>

using namespace std;

class Item {
public:
  Item(Coords xy, int tv = 20);

  int getTipo();

  void decrTempoVida();

private:
  int tempovida, tipo;
  Coords pos;
};

class Cidade {
public:
  Cidade(char n);

  char getNome();

  vector<shared_ptr<Caravana>> getCaravanas();
  void addCaravana(int id);
  void remCaravana(int id);

private:
  char nome;
  vector<shared_ptr<Caravana>> cars;
};

class Cell {
public:
  Cell();

private:
};

#endif // INCLUDE_HEADERS_PIECESDESERTO_H_
