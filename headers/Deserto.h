#ifndef INCLUDE_HEADERS_DESERTO_H_
#define INCLUDE_HEADERS_DESERTO_H_

#include "Caravana.h"
#include "Coordinates.h"
#include "Item.h"

#include <array>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>

#define DESERT_CELL 0
#define MOUNT_CELL 1
#define CITY_CELL 2

#define STRM_FLAG_BIT (unsigned)1 << 0
#define CRVN_FLAG_BIT (unsigned)1 << 1

using namespace std;

class Cidade {
public:
  Cidade(char n);

  char getNome();

  vector<weak_ptr<Caravana>> getCaravanas();
  template <typename T> shared_ptr<Caravana> sellCaravana();

private:
  char nome;
  array<shared_ptr<Caravana>, 3> caravanasForSale;
};

class CellFlags {
public:
  CellFlags(uint8_t f = 0);

  void setAll();
  void unsetAll();
  void toggleAll();
  uint8_t getFlags() const;

  void setStorm();
  void unsetStorm();
  void toggleStorm();
  bool getStorm() const;

  void setCaravana();
  void unsetCaravana();
  void toggleCaravana();
  bool getCaravana() const;

private:
  union {
    uint8_t all;
    uint8_t storm;
    uint8_t caravana;
  } flags;
};

class Cell : public CellFlags {
public:
  Cell(unsigned short type);

  unsigned short getType() const;

private:
  unsigned short type;
};

class Deserto {
public:
  Deserto(unsigned int w, unsigned int h);

  Cell &operator[](Coords);

private:
  unsigned int width, height;
  unsigned int maxItens;
  vector<Cell> mapa;
  vector<shared_ptr<Item>> itens;
};

#endif // INCLUDE_HEADERS_DESERTO_H_
