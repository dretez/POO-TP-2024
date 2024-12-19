#include "../headers/Caravana.h"
#include <cstdlib>

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
