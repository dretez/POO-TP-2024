#include "../headers/Simulador.h"

Simulador::Simulador(unsigned int startTime) : timer(startTime) {}

void Simulador::start() {
  while (1) {
    fase1();
    fase2();
  }
}

void Simulador::fase1() {
  while (1) {
    // recebe comando, se for exit para, se for config carrega configuação e
    // passa à próxima fase, se não for nenhum volta a pedir comando.
  }
}

void Simulador::fase2() {
  Deserto world(width, height);
  vector<Caravana> userCars;
  vector<CaravanaBarbara> enemyCars;
  User utilizador(world, initMoedas, userCars);
  vector<Item> items;

  while (1) {
    // print buffer
    //
    // read cmds until "prox" is received

    while (cmdQueue.size() > 0) {
      execCmd(*cmdQueue.begin());
      cmdQueue.pop_front();
    }

    vector<Caravana>::iterator uc;
    for (uc = userCars.begin(); uc != userCars.end(); uc++) {
      switch (uc->getMvMode()) {
      case MOV_USR: {
        map<unsigned int, Coords>::iterator i;
        for (i = uc->getTargetPath().begin(); i != uc->getTargetPath().end();
             i++) {
          if (!world[i->second].isValid()) {
            break;
          }
          uc->setPos(i->second);
        }
        uc->resetTargetPath();
        break;
      }
      case MOV_RUN:
      case MOV_AUTO:
        uc->mvAuto(userCars, enemyCars, items);
      case MOV_EMPTY:
        uc->mvEmpty();
        if (uc->getLifetime() == 0) {
          userCars.erase(uc);
        }
      }
    }

    // spawn barbarians if needed and move barbarian caravans
    if (!(timer.get() % time2newBarbarian)) {
      Coords randPos = world.getRandomFreeCell().getCoords();
      enemyCars.push_back(CaravanaBarbara(randPos));
    }
    vector<CaravanaBarbara>::iterator bc;
    for (bc = enemyCars.begin(); bc != enemyCars.end(); bc++) {
      bc->mvAuto(userCars, enemyCars, items);
    }

    //
    // fight between user and barbarian caravans
    //
    // spawn items if needed
  }
}
