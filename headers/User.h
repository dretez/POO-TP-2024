#ifndef INCLUDE_HEADERS_USER_H_
#define INCLUDE_HEADERS_USER_H_

#include "Caravana.h"
#include "Coordinates.h"
#include "Deserto.h"

#include <vector>

using namespace std;

class User {
public:
  User(Deserto &mapa, int money, vector<Caravana> &cars);

  template <typename T> void buyCaravana(Cidade &cid, int preco = 100);
  void buyTripulante(Caravana &car, unsigned int qtd);
  void buyMercadoria(Caravana &car, unsigned int qtd, int preco = 1);
  void sellMercadoria(Caravana &car, int preco = 2);

private:
  int moedas;
  Deserto &world;
  vector<Caravana> &caravanas;
};

#endif // INCLUDE_HEADERS_USER_H_
