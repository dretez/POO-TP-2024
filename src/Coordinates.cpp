#include "../headers/Coordinates.h"

Coords::Coords(int xx, int yy) : x(xx), y(yy) {}

int Coords::getx() const { return x; }
int Coords::gety() const { return y; }
void Coords::setx(int xx) { x = xx; }
void Coords::sety(int yy) { y = yy; }

int Coords::distance(Coords target) const {
  Coords vec = *this - target;
  /* Não queremos saber a distância literal até uma coordenada, mas sim o número
   * mínimo de movimentos necessários para atingir essa coordenada.
   * Dado que podem ser feitos movimentos diagonais, só precisamos de saber
   * quantos movimentos precisamos de fazer no eixo com maior diferença, visto
   * um movimento diagonal percorrer ambos os eixos ao mesmo tempo. */
  return vec.x > vec.y ? vec.x : vec.y;
}

Coords Coords::normalize() const {
  if (distance(Coords(0, 0)) <= 1)
    return *this;
  int dx = x / distance(Coords(0, y));
  int dy = y / distance(Coords(x, 0));
  return Coords(dx, dy);
}

Coords Coords::operator+(Coords c) const { return Coords(x + c.x, y + c.y); }
Coords Coords::operator-(Coords c) const { return Coords(x - c.x, y - c.y); }
Coords Coords::operator=(Coords c) {
  x = c.x;
  y = c.y;
  return *this;
}
bool Coords::operator==(Coords c) const { return x == c.x && y == c.y; }
