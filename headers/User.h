#ifndef INCLUDE_HEADERS_USER_H_
#define INCLUDE_HEADERS_USER_H_

#include "Caravana.h"
#include "Deserto.h"

#include <memory>
#include <vector>

using namespace std;

class User {
public:
  User(int money);

  void buyTripulante(int qtd, Caravana &car);
  void buyCaravana(Cidade &cid, int preco = 100);
  void buyMercadoria(Caravana &car, int qtd, int preco = 1);
  void sellMercadoria(Caravana &car, int preco = 2);

private:
  int moedas;
  vector<shared_ptr<Caravana>> caravanas;
};

#endif // INCLUDE_HEADERS_USER_H_
