#include "../headers/SimComponents.h"

Item::Item(Coords xy, int tv) : pos(xy), tempovida(tv), tipo(rand() % 5) {}

int Item::getTipo() { return tipo; }

Coords Item::getPos() { return pos; }

void Item::decrTempoVida() { tempovida--; }

Deserto::Deserto(unsigned int w, unsigned int h) : Coords(0, 0) {
  setWorldDimensions(w, h);
}

Cell &Deserto::operator[](Coords xy) {
  int idx = 0;
  idx += xy.getx() % width;
  idx += (xy.gety() % height) * width;

  return mapa.at(idx);
}
