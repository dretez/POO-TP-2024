#ifndef INCLUDE_HEADERS_DESERTO_H_
#define INCLUDE_HEADERS_DESERTO_H_

#include "PiecesDeserto.h"

#include <memory>
#include <vector>

using namespace std;

class Deserto {
public:
  Deserto();

private:
  unsigned int maxItens;
  vector<Cell> mapa;
  vector<shared_ptr<Item>> itens;
};

#endif // INCLUDE_HEADERS_DESERTO_H_
