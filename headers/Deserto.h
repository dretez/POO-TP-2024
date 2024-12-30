#ifndef INCLUDE_HEADERS_DESERTO_H_
#define INCLUDE_HEADERS_DESERTO_H_

#include <memory>
#include <vector>

#include "Cidade.h"
#include "Coordinates.h"
#include "MapCells.h"

class Deserto : private Coords {
public:
  Deserto(unsigned int w, unsigned int h);

  shared_ptr<Cell> getRandomFreeCell();
  vector<Cidade> getCities();

  shared_ptr<Cell> operator[](Coords);

private:
  unsigned int maxItens;
  vector<shared_ptr<Cell>> mapa;
  vector<Cidade> cities;
};

#endif // INCLUDE_HEADERS_DESERTO_H_
