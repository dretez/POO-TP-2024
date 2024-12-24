#include "../headers/Cidade.h"

/******************************** CIDADE FLAGS ********************************/

CidFlags::CidFlags(uint8_t f) : flags(f) {}

void CidFlags::setAll() {
  flags |= CRVN_COMR_MASK | CRVN_MILT_MASK | CRVN_SCRT_MASK;
}
void CidFlags::unsetAll() { flags = 0; }
uint8_t CidFlags::getFlags() const { return flags; }

void CidFlags::unsetCComercio() { flags &= ~CRVN_COMR_MASK; }
void CidFlags::unsetCMilitar() { flags &= ~CRVN_MILT_MASK; }
void CidFlags::unsetCSecreta() { flags &= ~CRVN_SCRT_MASK; }

bool CidFlags::getCComercio() const { return flags & CRVN_COMR_MASK; }
bool CidFlags::getCMilitar() const { return flags & CRVN_MILT_MASK; }
bool CidFlags::getCSecreta() const { return flags & CRVN_SCRT_MASK; }

/*********************************** CIDADE ***********************************/

Cidade::Cidade(char n) : nome(n) {}

char Cidade::getNome() { return nome; }
