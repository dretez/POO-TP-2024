#include "../headers/Caravanas.h"
#include "../headers/Items.h"

Caravana::Caravana(Coords xy, int trip, unsigned int capT, unsigned int capC,
                   unsigned int capA, unsigned int lt)
    : pos(xy), tripulantes(trip), capTrip(capT), capMerc(capC), capAgua(capA),
      mercadoria(0), agua(capA / 2), superSpeed(false), lifetime(lt) {}

CaravanaComercio::CaravanaComercio(Coords xy)
    : Caravana(xy, 20, 20, 40, 200, 5) {}
CaravanaMilitar::CaravanaMilitar(Coords xy) : Caravana(xy, 20, 40, 5, 400, 7) {}
CaravanaSecreta::CaravanaSecreta(Coords xy) : Caravana(xy, 5, 10, 5, 100, 1) {}
CaravanaBarbara::CaravanaBarbara(Coords xy, unsigned int lt)
    : Caravana(xy, 40, 40, 0, 0, lt) {}

Coords Caravana::getPos() { return pos; }

unsigned int Caravana::getMaxAgua() { return capAgua; }
unsigned int Caravana::getAgua() { return agua; }
void Caravana::usaAgua(unsigned int qtd) { agua -= agua < qtd ? agua : qtd; }
void Caravana::refillAgua() { agua = capAgua; }

unsigned int Caravana::getMaxMerc() { return capMerc; }
unsigned int Caravana::getMerc() { return mercadoria; }
void Caravana::setMerc(unsigned int n) { mercadoria = n; }
int Caravana::changeMerc(int qtd) {
  int change = mercadoria < -qtd ? -mercadoria : qtd;
  mercadoria += change;
  return change;
}

unsigned int Caravana::getMaxTripulantes() { return capTrip; }
unsigned int Caravana::getTripulantes() { return tripulantes; }
void Caravana::setTripulantes(unsigned int n) { tripulantes = n; }
int Caravana::changeTripulantes(int n) {
  int change = tripulantes < -n ? -tripulantes : n;
  tripulantes += change;
  return change;
}

unsigned int Caravana::attack() { return rand() % (tripulantes + 1); }

unsigned int Caravana::getMaxMvs() {
  return maxTargPathSize * (superSpeed ? 2 : 1);
}
void Caravana::resetTargetPath() { targetPath.clear(); }

void Caravana::mv(Coords target) {
  if (targetPath.size() >= getMaxMvs())
    return;
  Coords oldpos =
      targetPath.size() > 0 ? targetPath.at(targetPath.size() - 1) : pos;
  targetPath.insert({targetPath.size(), oldpos + target.normalize()});
}
void Caravana::mvEmpty() { return; }
void Caravana::mvAuto(const vector<shared_ptr<Caravana>> &usr,
                      const vector<shared_ptr<Caravana>> &enemy,
                      const vector<shared_ptr<Item>> &) {
  return;
}

void CaravanaComercio::mvEmpty() {
  // move random 5 times
  if (lifetime == 0) {
    // commit seppuku
  }
  lifetime--;
}
void CaravanaComercio::mvAuto(const vector<shared_ptr<Caravana>> &usr,
                              const vector<shared_ptr<Caravana>> &enemy,
                              const vector<shared_ptr<Item>> &items) {
  for (int i = 0; i < getMaxMvs(); i++) {
    auto ii = items.begin();
    int minDist = getPos().distance((*ii)->getPos());
    auto auxi = ii;
    for (ii++; ii != items.end(); ii++) {
      if (minDist > getPos().distance((*ii)->getPos())) {
        minDist = getPos().distance((*ii)->getPos());
        auxi = ii;
      }
    }
    if (minDist <= 2) {
      /* WARN: Uma caravana pode aproximar-se do item pela diagonal, o que
       * impossibilitaria a recolha do item. Este problema precisa de ser
       * resolvido.
       */
      /* NOTE: Possível solução: se o item estiver a uma distância de 1,
       * verificamos se está numa posição adjacente, se estiver recolhemos o
       * item, senão movemo-nos para uma coordenada adjacente ao item aleatória
       * com uma distância à coordenada atual de 1.
       */
      mv((*auxi)->getPos());
      return;
    }

    auto ic = usr.begin();
    minDist = getPos().distance((*ic)->getPos());
    auto auxc = ic;

    for (ic++; ic != usr.end(); ic++) {
      if ((*ic)->getId() == getId())
        continue;
      if (minDist > getPos().distance((*ic)->getPos())) {
        minDist = getPos().distance((*ic)->getPos());
        auxc = ic;
      }
    }

    if (minDist > 1) {
      mv((*auxc)->getPos());
    }
  }
}

void CaravanaMilitar::mvEmpty() {}
void CaravanaMilitar::mvAuto(const vector<shared_ptr<Caravana>> &usr,
                             const vector<shared_ptr<Caravana>> &enemy,
                             const vector<shared_ptr<Item>> &items) {
  auto ic = usr.begin();
  int minDist = getPos().distance((*ic)->getPos());
  auto auxi = ic;

  for (ic++; ic != usr.end(); ic++) {
    if ((*ic)->getId() == getId())
      continue;
    if (minDist > getPos().distance((*ic)->getPos())) {
      minDist = getPos().distance((*ic)->getPos());
      auxi = ic;
    }
  }

  if (minDist <= 6) {
    mv((*auxi)->getPos());
  }
}

void CaravanaSecreta::mvEmpty() {
  // destroy any caravan within a distance of 2
  // commit seppuku
}
void CaravanaSecreta::mvAuto(const vector<shared_ptr<Caravana>> &usr,
                             const vector<shared_ptr<Caravana>> &enemy,
                             const vector<shared_ptr<Item>> &items) {
  /* Moves randomly across the map. If it detects a barbarian caravan within 8
   * cells, it performs a hit-and-run:
   *  - It tries to approach the barbarian caravan;
   *  - Once the barbarians are within a distance of 1, it attempts to convert
   *    them to a user caravan (this action has a 5% sucess rate);
   *  - After "hitting", the secret caravan changes to "flee" mode, where it
   *    gets as far away from the barbarians as possible.
   */
}

void CaravanaBarbara::mvEmpty() {
  // commit seppuku
}
void CaravanaBarbara::mvAuto(const vector<shared_ptr<Caravana>> &usr,
                             const vector<shared_ptr<Caravana>> &enemy,
                             const vector<shared_ptr<Item>> &items) {}
