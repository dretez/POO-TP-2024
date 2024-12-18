#include "../headers/Deserto.h"

/********************************* CELL FLAGS *********************************/

CellFlags::CellFlags(uint8_t f) { flags.all = f; }

void CellFlags::setAll() {
  setStorm();
  setCaravana();
}
void CellFlags::unsetAll() { flags.all = 0; }
void CellFlags::toggleAll() {
  toggleStorm();
  toggleCaravana();
}
uint8_t CellFlags::getFlags() const { return flags.all; }

void CellFlags::setStorm() { flags.storm |= STRM_FLAG_BIT; }
void CellFlags::unsetStorm() { flags.storm &= ~STRM_FLAG_BIT; }
void CellFlags::toggleStorm() { flags.storm ^= STRM_FLAG_BIT; }
bool CellFlags::getStorm() const { return flags.storm & STRM_FLAG_BIT; }

void CellFlags::setCaravana() { flags.caravana |= CRVN_FLAG_BIT; }
void CellFlags::unsetCaravana() { flags.caravana &= ~CRVN_FLAG_BIT; }
void CellFlags::toggleCaravana() { flags.caravana ^= CRVN_FLAG_BIT; }
bool CellFlags::getCaravana() const { return flags.caravana & CRVN_FLAG_BIT; }

/************************************ CELL ************************************/

Cell::Cell(unsigned short t) : CellFlags(0), type(t) {}
