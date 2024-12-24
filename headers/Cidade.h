#ifndef INCLUDE_HEADERS_CIDADE_H_
#define INCLUDE_HEADERS_CIDADE_H_

#include <cstdint>

#define CRVN_COMR_MASK 0b00000001
#define CRVN_MILT_MASK 0b00000010
#define CRVN_SCRT_MASK 0b00000100

class CidFlags {
public:
  CidFlags(uint8_t f = CRVN_COMR_MASK | CRVN_MILT_MASK | CRVN_SCRT_MASK);

  void setAll();
  void unsetAll();
  uint8_t getFlags() const;

  void unsetCComercio();
  bool getCComercio() const;
  void unsetCMilitar();
  bool getCMilitar() const;
  void unsetCSecreta();
  bool getCSecreta() const;

private:
  uint8_t flags;
};

class Cidade : public CidFlags {
public:
  Cidade(char n);

  char getNome();

private:
  char nome;
};

#endif // INCLUDE_HEADERS_CIDADE_H_
