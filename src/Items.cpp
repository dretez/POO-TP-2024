#include "../headers/Items.h"
#include "../headers/Caravanas.h"
#include "../headers/User.h"

Item::Item(Coords xy, int tv) : pos(xy), tempovida(tv) {}
ItemPandora::ItemPandora(Coords xy, int tv) : Item(xy, tv) { }
ItemTesouro::ItemTesouro(Coords xy, int tv) : Item(xy, tv) { }
ItemJaula::ItemJaula(Coords xy, int tv) : Item(xy, tv) { }
ItemMina::ItemMina(Coords xy, int tv) : Item(xy, tv) { }
ItemSurpresa::ItemSurpresa(Coords xy, int tv) : Item(xy, tv) { }


Coords Item::getPos() { return pos; }
void Item::decrTempoVida() { tempovida--; }
void RandItemGenerator::gen(vector<shared_ptr<Item>> &to, Coords xy, int tv) {
  switch (rand() % ITEM_COUNT) {
  case 0:
    to.push_back(make_shared<ItemPandora>(xy, tv));
  case 1:
    to.push_back(make_shared<ItemTesouro>(xy, tv));
  case 2:
    to.push_back(make_shared<ItemJaula>(xy, tv));
  case 3:
    to.push_back(make_shared<ItemMina>(xy, tv));
  case 4:
    to.push_back(make_shared<ItemSurpresa>(xy, tv));
  default:
    // Não é suposto chegar aqui
    to.push_back(make_shared<Item>(xy, tv));
  }
}

void Item::collect(User &u, vector<shared_ptr<Caravana>>::iterator &c,
                   vector<shared_ptr<Caravana>> &allCars) {
  return;
}

void ItemPandora::collect(User &u, vector<shared_ptr<Caravana>>::iterator &c,
                          vector<shared_ptr<Caravana>> &allCars) {
  (*c)->changeTripulantes((*c)->getTripulantes() * 0.8);
}
void ItemTesouro::collect(User &u, vector<shared_ptr<Caravana>>::iterator &c,
                          vector<shared_ptr<Caravana>> &allCars) {
  u.changeMoedas(u.getMoedas() * 1.1);
}
void ItemJaula::collect(User &u, vector<shared_ptr<Caravana>>::iterator &c,
                        vector<shared_ptr<Caravana>> &allCars) {
  (*c)->changeTripulantes((rand() % 10) + 1);
}
void ItemMina::collect(User &u, vector<shared_ptr<Caravana>>::iterator &c,
                       vector<shared_ptr<Caravana>> &allCars) {
  allCars.erase(c);
}
void ItemSurpresa::collect(User &u, vector<shared_ptr<Caravana>>::iterator &c,
                           vector<shared_ptr<Caravana>> &allCars) {
  // Super velocidade, a caravana que apanha este item pode fazer o dobro dos
  // movimentos no próximo turno
}
