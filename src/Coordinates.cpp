#include <bitset>
#include <cmath>

#include "../headers/Coordinates.h"

Coords::Coords(int xx, int yy, bool inbounds) : x(xx), y(yy) {
  if (inbounds)
    *this = (*this).inbounds();
}

void Coords::setWorldDimensions(int w, int h) {
  width = w;
  height = h;
}

int Coords::getx() const { return x; }
int Coords::gety() const { return y; }
void Coords::setx(int xx) { x = xx; }
void Coords::sety(int yy) { y = yy; }

int Coords::distance(Coords target) const {
  target = target.inbounds();
  Coords aux(width / 2, height / 2);
  Coords vec = *this - target;
  return vec.x > vec.y ? x : y;
  /* Não queremos saber a distância literal até uma coordenada, mas sim o número
   * mínimo de movimentos necessários para atingir essa coordenada.
   * Dado que podem ser feitos movimentos diagonais, só precisamos de saber
   * quantos movimentos precisamos de fazer no eixo com maior diferença, visto
   * um movimento diagonal percorrer ambos os eixos ao mesmo tempo. */
}

Coords Coords::normalize() const {
  if (distance(Coords(0, 0)) <= 1)
    return *this;
  int dx = x / distance(Coords(0, y));
  int dy = y / distance(Coords(x, 0));
  return Coords(dx, dy);
}

array<Coords, 4> Coords::getAdjacent() const {
  array<Coords, 4> adj;
  for (unsigned int i = 0; i < 4; i++) {
    bitset<2> bs = i;
    int xx = x + ((1 * bs[0]) * (1 - 2 * bs[1]));
    int yy = y + ((1 * !bs[0]) * (1 - 2 * bs[1]));
    adj[i] = Coords(xx, yy);
  }
  return adj;
}
bool Coords::isAdjacent(Coords target) const {
  target = target.inbounds();
  Coords aux = (*this - target).normalize();
  return (distance(target) == 1) && (!aux.x != !aux.y);
  /* Fazemos o XOR entre os eixos do vetor entre as duas coordenadas porque uma
   * coordenada só é adjacente da outra se um dos eixos for igual e o outro for
   * diferente. */
}

Coords Coords::inbounds() const {
  int xx = x % width;
  int yy = y % height;
  xx = x < 0 ? width - x : x;
  yy = y < 0 ? height - y : y;
  return Coords(xx, yy);
}

Coords Coords::abs() const { return Coords(x < 0 ? -x : x, y < 0 ? -y : y); }

int Coords::vecLen() const {
  Coords aux = (*this).abs();
  return aux.x > aux.y ? aux.x : aux.y;
}

Coords Coords::operator+(Coords c) const {
  c = c.inbounds();
  return Coords(x + c.x, y + c.y).inbounds();
}
Coords Coords::operator-(Coords c) const {
  c = c.inbounds();
  Coords aux(width / 2, height / 2);
  Coords vec1(x - c.x, y - c.y);
  Coords vec2 = (*this + aux).inbounds();
  c = (c + aux).inbounds();
  vec2.x -= c.x;
  vec2.y -= c.y;
  return vec2.vecLen() < vec1.vecLen() ? vec2 : vec1;
  /* É possível que haja um caminho mais curto se dermos a volta pelo "outro
   * lado" do Deserto. Sendo assim, criamos um novo vetor que representa a
   * diferença das mesmas coordenadas, deslocadas "meio Deserto" em ambos os
   * eixos de forma a obter uma nova "perspetiva" da posição relativa entre as
   * duas coordenadas.
   * Por fim devolvemos o vetor que tiver o menor tamanho. */
}
Coords Coords::operator*(int factor) const {
  return Coords(x * factor, y * factor);
}
Coords Coords::operator=(Coords c) {
  c = c.inbounds();
  x = c.x;
  y = c.y;
  return *this;
}
Coords Coords::operator+=(Coords c) {
  c = c.inbounds();
  x += c.x;
  y += c.y;
  *this = (*this).inbounds();
  return *this;
}
bool Coords::operator==(Coords c) const {
  c = c.inbounds();
  return x == c.x && y == c.y;
}
