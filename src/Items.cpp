#include "../headers/Items.h"
#include "../headers/SimComponents.h"
#include <cstdlib>
#include <vector>

Item::Item(Coords xy, int tv) : pos(xy), tempovida(tv) {}

Coords Item::getPos() { return pos; }
void Item::decrTempoVida() { tempovida--; }

void Item::collect(User &u, vector<Caravana>::iterator &c,
                   vector<Caravana> &allCars) {
  return;
}

void ItemPandora::collect(User &u, vector<Caravana>::iterator &c,
                          vector<Caravana> &allCars) {
  c->changeTripulantes(c->getTripulantes() * 0.8);
}
void ItemTesouro::collect(User &u, vector<Caravana>::iterator &c,
                          vector<Caravana> &allCars) {
  u.changeMoedas(u.getMoedas() * 1.1);
}
void ItemJaula::collect(User &u, vector<Caravana>::iterator &c,
                        vector<Caravana> &allCars) {
  c->changeTripulantes((rand() % 10) + 1);
}
void ItemMina::collect(User &u, vector<Caravana>::iterator &c,
                       vector<Caravana> &allCars) {
  allCars.erase(c);
}
void ItemSurpresa::collect(User &u, vector<Caravana>::iterator &c,
                           vector<Caravana> &allCars) {
  // Super velocidade, a caravana que apanha este item pode fazer o dobro dos
  // movimentos no próximo turno
}
