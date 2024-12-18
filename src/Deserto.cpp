#include "../headers/Deserto.h"

Item::Item(Coords xy, int tv) : pos(xy), tempovida(tv), tipo(rand() % 5) {}

int Item::getTipo() { return tipo; }

void Item::decrTempoVida() { tempovida--; }
