#include <string>

#include "../headers/Buffer.h"
#include "../headers/Deserto.h"
#include "../headers/Items.h"
#include "../headers/MapCells.h"
#include "../headers/Simulador.h"

Buffer::Buffer(Simulador &s, Deserto &map, unsigned int w, unsigned int h,
               string n)
    : sim(s), world(map), colunas(w), linhas(h), nome(n) {
  alocarBuffer();
  writeItems();
  writeCaravans();
  writeMap();
}

Buffer::~Buffer() { delete[] buffer; }

void Buffer::alocarBuffer() {
  buffer = new char *[linhas];
  for (int i = 0; i < linhas; i++) {
    buffer[i] = new char[colunas];
    for (int j = 0; j < colunas; j++) {
      buffer[i][j] = ' ';
    }
  }
}

void Buffer::liberarBuffer() {
  for (int i = 0; i < linhas; i++) {
    delete[] buffer[i];
  }
  delete[] buffer;
}

void Buffer::limparBuffer() {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      buffer[i][j] = ' ';
    }
  }
}

void Buffer::validarPosicao(int linha, int coluna) const {
  if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
    throw std::out_of_range("A posição é inválida.");
  }
}

void Buffer::moverCursor(Coords pos) { cursor = pos; }
void Buffer::moverCursor(int linha, int coluna) {
  validarPosicao(linha, coluna);
  cursorLinha = linha;
  cursorColuna = coluna;
}

void Buffer::escreverChar(char c) {
  validarPosicao(cursorLinha, cursorColuna);
  buffer[cursorLinha][cursorColuna] = c;
  cursorColuna = (cursorColuna + 1) % colunas;
  if (cursorColuna == 0)
    cursorLinha = (cursorLinha + 1) % linhas;
}

void Buffer::escreverString(const std::string &str) {
  for (char c : str) {
    escreverChar(c);
  }
}

void Buffer::imprimir() const {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      std::cout << buffer[i][j];
    }
    std::cout << std::endl;
  }
};

void Buffer::operator<<(char c) {
  buffer[cursor.getx()][cursor.gety()] = c;
  cursor.setx(cursor.getx() + 1 % colunas);
  cursor.sety(!cursor.getx() ? cursor.gety() + 1 % linhas : cursor.gety());
}
void Buffer::operator<<(const std::string str) {
  for (char c : str)
    *this << c;
}
void Buffer::operator<<(int i) {
  if (i >= 10 || i < 0)
    return;
  *this << std::to_string(i);
}
void Buffer::operator<<(Item i) {
  Coords temp = cursor;
  cursor = i.getPos();
  *this << '?';
  cursor = temp;
}
void Buffer::operator<<(Cell c) {
  Coords temp = cursor;
  cursor = c.getCoords();
  *this << ' ';
  cursor = temp;
}
void Buffer::operator<<(DesertCell c) {
  Coords temp = cursor;
  cursor = c.getCoords();
  *this << '.';
  cursor = temp;
}
void Buffer::operator<<(CityCell c) {
  Coords temp = cursor;
  cursor = c.getCoords();
  for (auto city : world.getCities()) {
    if (!(city.getPos() == cursor)) {
      if (city.getNome() != (*world.getCities().end()).getNome())
        *this << ' ';
      continue;
    }
    *this << city.getNome();
  }
  cursor = temp;
}
void Buffer::operator<<(MountainCell c) {
  Coords temp = cursor;
  cursor = c.getCoords();
  *this << '+';
  cursor = temp;
}
void Buffer::operator<<(Caravana c) {
  Coords temp = cursor;
  cursor = c.getPos();
  *this << c.getId();
  cursor = temp;
}
void Buffer::operator<<(CaravanaComercio c) {
  Coords temp = cursor;
  cursor = c.getPos();
  *this << c.getId();
  cursor = temp;
}
void Buffer::operator<<(CaravanaMilitar c) {
  Coords temp = cursor;
  cursor = c.getPos();
  *this << c.getId();
  cursor = temp;
}
void Buffer::operator<<(CaravanaSecreta c) {
  Coords temp = cursor;
  cursor = c.getPos();
  *this << c.getId();
  cursor = temp;
}
void Buffer::operator<<(CaravanaBarbara c) {
  Coords temp = cursor;
  cursor = c.getPos();
  *this << '!';
  cursor = temp;
}

void Buffer::writeMap() {
  for (int i = 0; i < linhas * colunas; i++)
    *this << *world[cursor];
}

void Buffer::writeCaravans() {
  for (auto uc : sim.getUCars())
    *this << *uc;
  for (auto ec : sim.getECars())
    *this << *ec;
}

void Buffer::writeItems() {
  for (auto uc : sim.getItems())
    *this << *uc;
}
