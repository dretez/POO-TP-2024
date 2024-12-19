#include "../headers/User.h"

User::User(Deserto &mapa, int money) : world(mapa), moedas(money) {};

template <typename T> void User::buyCaravana(Cidade &cid, int preco) {
  cid.sellCaravana<T>();
}

void User::buyTripulante(Caravana &car, unsigned int qtd) {
  if (world[car.getPos()].getType() != CITY_CELL)
    return; // a caravana não está numa cidade

  unsigned int finalQtd = qtd;
  finalQtd = moedas < finalQtd ? moedas : finalQtd;
  finalQtd = car.getTripulantes() + finalQtd > car.getMaxTripulantes()
                 ? car.getMaxTripulantes() - car.getTripulantes()
                 : finalQtd;

  moedas -= finalQtd;
  car.changeTripulantes(finalQtd);
}

void User::buyMercadoria(Caravana &car, unsigned int qtd, int preco) {
  if (world[car.getPos()].getType() != CITY_CELL)
    return; // a caravana não está numa cidade

  unsigned int finalQtd = qtd;
  finalQtd = moedas / preco < finalQtd ? moedas / preco : finalQtd;
  finalQtd = car.getMerc() + finalQtd > car.getMaxMerc()
                 ? car.getMaxMerc() - car.getMerc()
                 : finalQtd;

  moedas -= finalQtd * preco;
  car.changeMerc(finalQtd);
}

void User::sellMercadoria(Caravana &car, int preco) {
  if (world[car.getPos()].getType() != CITY_CELL)
    return; // a caravana não está numa cidade

  moedas += preco * car.getMerc();
  car.setMerc(0);
}
