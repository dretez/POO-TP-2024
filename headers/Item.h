#ifndef INCLUDE_HEADERS_ITEM_H_
#define INCLUDE_HEADERS_ITEM_H_

#include "Coordinates.h"

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
