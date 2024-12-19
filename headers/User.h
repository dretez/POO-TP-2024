#ifndef INCLUDE_HEADERS_USER_H_
#define INCLUDE_HEADERS_USER_H_

#include "Caravana.h"
#include "Coordinates.h"
#include "Deserto.h"

#include <memory>
#include <vector>

using namespace std;

class User {
public:
  User(Deserto &mapa, int money);

  template <typename T> void buyCaravana(Cidade &cid, int preco = 100);
  void buyTripulante(Caravana &car, unsigned int qtd);
  void buyMercadoria(Caravana &car, unsigned int qtd, int preco = 1);
  void sellMercadoria(Caravana &car, int preco = 2);

private:
  int moedas;
  Deserto &world;
  vector<shared_ptr<Caravana>> caravanas;
};

#endif // INCLUDE_HEADERS_USER_H_
