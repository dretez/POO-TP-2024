#include "../headers/Deserto.h"

#include <cstdlib>

Deserto::Deserto(unsigned int w, unsigned int h) : Coords(0, 0) {
  setWorldDimensions(w, h);
}

shared_ptr<Cell> Deserto::getRandomFreeCell() {
  shared_ptr<Cell> r;
  do {
    r = mapa.at(rand() % mapa.size());
  } while (!r->isValid());
  return r;
}

shared_ptr<Cell> Deserto::operator[](Coords xy) {
  int idx = 0;
  idx += xy.getx() % width;
  idx += (xy.gety() % height) * width;

  return mapa.at(idx);
}
