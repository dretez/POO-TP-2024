#include "../headers/Caravana.h"
#include "../headers/Coordinates.h"

#include <iostream>
#include <map>

using namespace std;
/*
Caravana::Caravana(Coords xy, int trip, unsigned int capT, unsigned int capC,
                   unsigned int capA)
    : pos(xy), tripulantes(trip), capTrip(capT), capMerc(capC), capAgua(capA),
      mercadoria(0), agua(capA / 2) {}

CaravanaComercio::CaravanaComercio(Coords xy) : Caravana(xy, 20, 20, 40, 200) {}
CaravanaMilitar::CaravanaMilitar(Coords xy) : Caravana(xy, 20, 40, 5, 400) {}
CaravanaSecreta::CaravanaSecreta(Coords xy) : Caravana(xy, 0, 0, 0, 0) {}
CaravanaBarbara::CaravanaBarbara(Coords xy, unsigned int tv)
    : Caravana(xy, 40, 40, 0, 0) {}

Coords Caravana::getPos() { return pos; }
int Caravana::getId() const  { return id; }

unsigned int Caravana::getMaxAgua() { return capAgua; }
unsigned int Caravana::getAgua() { return agua; }
void Caravana::usaAgua(unsigned int qtd) { agua -= agua < qtd ? agua : qtd; }
void Caravana::refillAgua() { agua = capAgua; }

unsigned int Caravana::getMaxMerc() { return capMerc; }
unsigned int Caravana::getMerc() { return mercadoria; }
void Caravana::setMerc(unsigned int n) { mercadoria = n; }
void Caravana::changeMerc(int qtd) {
  mercadoria += mercadoria < -qtd ? -mercadoria : qtd;
}

unsigned int Caravana::getMaxTripulantes() { return capTrip; }
unsigned int Caravana::getTripulantes() { return tripulantes; }
void Caravana::setTripulantes(unsigned int n) { tripulantes = n; }
void Caravana::changeTripulantes(int n) {
  tripulantes += tripulantes < -n ? -tripulantes : n;
}

int Caravana::attack() { return rand() % (tripulantes + 1); }

void Caravana::resetTargetPath() { targetPath.clear(); }

void Caravana::mv(Coords target) {
  if (targetPath.size() >= maxTargPathSize)
    return;
  Coords oldpos =
      targetPath.size() > 0 ? targetPath.at(targetPath.size() - 1) : pos;
  targetPath.insert({targetPath.size(), oldpos + target.normalize()});
}
void Caravana::mvAuto(vector<Caravana> &usr, vector<CaravanaBarbara> &enemy,
                      vector<Item> &itens) {
  return;
}
void Caravana::mvEmpty() { return; }

void CaravanaComercio::mvAuto(vector<Caravana> &usr,
                              vector<CaravanaBarbara> &enemy,
                              vector<Item> &items) {
  for (int i = 0; i < maxTargPathSize; i++) {
    vector<Item>::iterator ii = items.begin();
    int minDist = getPos().distance(ii->getPos());
    vector<Item>::iterator auxi = ii;
    for (ii++; ii != items.end(); ii++) {
      if (minDist > getPos().distance(ii->getPos())) {
        minDist = getPos().distance(ii->getPos());
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

      mv(auxi->getPos());
      return;
    }

    vector<Caravana>::iterator ic = usr.begin();
    minDist = getPos().distance(ic->getPos());
    vector<Caravana>::iterator auxc = ic;

    for (ic++; ic != usr.end(); ic++) {
      if (ic.base() == this)
        continue;
      if (minDist > getPos().distance(ic->getPos())) {
        minDist = getPos().distance(ic->getPos());
        auxc = ic;
      }
    }

    if (minDist > 1) {
      mv(auxc->getPos());
    }
  }
}

void CaravanaComercio::mvEmpty() {
  // move random 5 times
  if (lifetime == 0) {
    // commit seppuku
  }
  lifetime--;
}

void CaravanaMilitar::mvAuto(vector<Caravana> &usr,
                             vector<CaravanaBarbara> &enemy,
                             vector<Item> &items) {
  vector<Caravana>::iterator ic = usr.begin();
  int minDist = getPos().distance(ic->getPos());
  vector<Caravana>::iterator auxi = ic;

  for (ic++; ic != usr.end(); ic++) {
    if (ic.base() == this)
      continue;
    if (minDist > getPos().distance(ic->getPos())) {
      minDist = getPos().distance(ic->getPos());
      auxi = ic;
    }
  }

  if (minDist <= 6) {
    mv(auxi->getPos());
  }
}

void CaravanaSecreta::mvAuto(vector<Caravana> &usr,
                             vector<CaravanaBarbara> &enemy,
                             vector<Item> &itens) {
  /* Moves randomly across the map. If it detects a barbarian caravan within 8
   * cells, it performs a hit-and-run:
   *  - It tries to approach the barbarian caravan;
   *  - Once the barbarians are within a distance of 1, it attempts to convert
   *    them to a user caravan (this action has a 5% sucess rate);
   *  - After "hitting", the secret caravan changes to "flee" mode, where it
   *    gets as far away from the barbarians as possible.

}

void CaravanaSecreta::mvEmpty() {
  // destroy any caravan within a distance of 2
  // commit seppuku
}

void CaravanaBarbara::mvEmpty() {
  // commit seppuku
}

void Caravana::apanhaItem(Item i) {
  switch (i.getTipo()) {
  case ITEM_PANDORA:
    tripulantes /= 5;
    break;
  case ITEM_TESOURO:
    // adiciona 10% às moedas do utilizador
    break;
  case ITEM_JAULA:
    changeTripulantes((rand() % 10) + 1);
    break;
  case ITEM_MINA:
    // commit seppuku
    break;
  case ITEM_SURPRESA:
    // idk yet
    break;
  default:
    break;
  }
}
*/

int Caravana::getId() const  { return id; }
void Caravana::Info() const {

    std::cout << "ID: " << id
        << "\n- Pos: (" << pos.getx() << ", " << pos.gety() << ")"
              << "\n- Mercadoria: " << mercadoria << "/" << capMerc
              << "\n- Agua: " << agua << "/" << capAgua
              << "\n- Tripulacao: " << tripulantes << "/" << capTrip
              << std::endl;

}