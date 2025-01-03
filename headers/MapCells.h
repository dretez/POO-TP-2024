#ifndef INCLUDE_HEADERS_MAPCELLS_H_
#define INCLUDE_HEADERS_MAPCELLS_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "Coordinates.h"

class Caravana;
class Item;

#define STRM_FLAG_BIT 0b00000001
#define ITEM_FLAG_BIT 0b00000100

using namespace std;

class CellFlags {
public:
  CellFlags(uint8_t f = 0);

  void setAll();
  void unsetAll();
  void toggleAll();
  uint8_t getFlags() const;

private:
  uint8_t flags;
};

class Cell {
public:
  Cell(Coords p);

  Coords getCoords() const;
  virtual bool isValid() const;
  virtual bool isCity() const;

  bool hasCaravana() const;
  shared_ptr<Caravana> getCaravana() const;
  void setCaravana(shared_ptr<Caravana> &);
  void unsetCaravana();

  bool hasItem() const;
  shared_ptr<Item> getItem() const;
  void setItem(shared_ptr<Item> &);
  void unsetItem();

  bool getStorm() const;
  void setStorm();
  void unsetStorm();
  void toggleStorm();

private:
  char type;
  const Coords pos;
  weak_ptr<Caravana> car;
  weak_ptr<Item> item;
  bool storm;
};

class DesertCell : public Cell {
public:
  DesertCell(Coords);

  virtual bool isValid() const;
};

class CityCell : public Cell {
public:
  CityCell(Coords);

  virtual bool isValid() const;
  virtual bool isCity() const;
};

class MountainCell : public Cell {
public:
  MountainCell(Coords);

  virtual bool isValid() const;
};

#endif // INCLUDE_HEADERS_MAPCELLS_H_
