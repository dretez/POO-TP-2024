#ifndef INCLUDE_HEADERS_ITEM_H_
#define INCLUDE_HEADERS_ITEM_H_

#include "Coordinates.h"

#define ITEM_PANDORA 0
#define ITEM_TESOURO 1
#define ITEM_JAULA 2
#define ITEM_MINA 3
#define ITEM_SURPRESA 4

class Item {
public:
  Item(Coords xy, int tv = 20);

  int getTipo();

  void decrTempoVida();

private:
  int tempovida, tipo;
  Coords pos;
};

#endif // INCLUDE_HEADERS_ITEM_H_
