#include "../headers/MapCells.h"

/********************************* CELL FLAGS *********************************/

CellFlags::CellFlags(uint8_t f) { flags = f; }

void CellFlags::setAll() {
  setStorm();
  setCaravana();
}
void CellFlags::unsetAll() { flags = 0; }
void CellFlags::toggleAll() {
  toggleStorm();
  toggleCaravana();
}
uint8_t CellFlags::getFlags() const { return flags; }

void CellFlags::setStorm() { flags |= STRM_FLAG_BIT; }
void CellFlags::unsetStorm() { flags &= ~STRM_FLAG_BIT; }
void CellFlags::toggleStorm() { flags ^= STRM_FLAG_BIT; }
bool CellFlags::getStorm() const { return flags & STRM_FLAG_BIT; }

void CellFlags::setCaravana() { flags |= CRVN_FLAG_BIT; }
void CellFlags::unsetCaravana() { flags &= ~CRVN_FLAG_BIT; }
void CellFlags::toggleCaravana() { flags ^= CRVN_FLAG_BIT; }
bool CellFlags::getCaravana() const { return flags & CRVN_FLAG_BIT; }

/************************************ CELL ************************************/

Cell::Cell(unsigned short t, Coords p) : CellFlags(0), type(t), pos(p) {}

bool Cell::isValid() const {
  return (type != MOUNT_CELL) && (!getCaravana() | (type == CITY_CELL));
}
