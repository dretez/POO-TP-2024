#include "../headers/SimComponents.h"

Deserto::Deserto(unsigned int w, unsigned int h) : Coords(0, 0) {
  setWorldDimensions(w, h);
}

Cell &Deserto::operator[](Coords xy) {
  int idx = 0;
  idx += xy.getx() % width;
  idx += (xy.gety() % height) * width;

  return mapa.at(idx);
}
