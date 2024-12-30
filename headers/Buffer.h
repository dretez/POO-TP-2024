#ifndef BUFFER_H
#define BUFFER_H

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Coordinates.h"

class Simulador;
class Deserto;
class Item;
class Cell;
class DesertCell;
class CityCell;
class MountainCell;
class Caravana;
class CaravanaComercio;
class CaravanaMilitar;
class CaravanaSecreta;
class CaravanaBarbara;

class Buffer {
public:
  Buffer(Simulador &, Deserto &, unsigned int w, unsigned int h,
         string nome = "");
  ~Buffer();
  string getNome() const;
  void limparBuffer();
  void moverCursor(int linha, int coluna);
  void moverCursor(Coords);
  void escreverChar(char c);
  void escreverString(const std::string &str);
  void imprimir() const;
  void writeMap();
  void writeCaravans();
  void writeItems();

  void operator<<(char);
  void operator<<(const std::string);
  void operator<<(int);
  void operator<<(Item);
  void operator<<(Cell);
  void operator<<(DesertCell);
  void operator<<(CityCell);
  void operator<<(MountainCell);
  void operator<<(Caravana);
  void operator<<(CaravanaComercio);
  void operator<<(CaravanaMilitar);
  void operator<<(CaravanaSecreta);
  void operator<<(CaravanaBarbara);

private:
  void alocarBuffer();
  void liberarBuffer();
  void validarPosicao(int linha, int coluna) const;

  unsigned int colunas, linhas;
  string nome;

  char **buffer;
  Coords cursor;
  int cursorLinha;
  int cursorColuna;
  Simulador &sim;
  Deserto &world;
};

#endif // BUFFER_H
