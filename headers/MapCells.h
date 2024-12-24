#ifndef INCLUDE_HEADERS_MAPCELLS_H_
#define INCLUDE_HEADERS_MAPCELLS_H_

#include <cstdint>

#include "Coordinates.h"

#define STRM_FLAG_BIT 0b00000001
#define CRVN_FLAG_BIT 0b00000010

using namespace std;

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
  uint8_t flags;
};

#define DESERT_CELL 0
#define MOUNT_CELL 1
#define CITY_CELL 2

class Cell : public CellFlags {
public:
  Cell(unsigned short type, Coords p);

  unsigned short getType() const;
  Coords getCoords() const;
  bool isValid() const;

private:
  unsigned short type;
  const Coords pos;
};

#endif // INCLUDE_HEADERS_MAPCELLS_H_
