#ifndef INCLUDE_HEADERS_DESERTO_H_
#define INCLUDE_HEADERS_DESERTO_H_

#include "Coordinates.h"
#include "MapCells.h"

class Deserto : private Coords {
public:
  Deserto(unsigned int w, unsigned int h);

  Cell &getRandomFreeCell();

  Cell &operator[](Coords);

private:
  unsigned int maxItens;
  vector<Cell> mapa;
};

#endif // INCLUDE_HEADERS_DESERTO_H_
