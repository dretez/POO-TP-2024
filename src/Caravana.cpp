#include "../headers/Caravana.h"

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

int Caravana::getAgua() { return agua; }
void Caravana::usaAgua(unsigned int qtd) {
  agua -= qtd;
  agua = agua < 0 ? 0 : agua;
}
void Caravana::refillAgua() { agua = capAgua; }

int Caravana::getTripulantes() { return tripulantes; }
void Caravana::setTripulantes(unsigned int n) { tripulantes = n; }
