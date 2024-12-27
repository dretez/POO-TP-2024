#include "../headers/Simulador.h"
#include "../headers/Deserto.h"
#include "../headers/User.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

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
  timer.reset();
  Deserto world(width, height);
  vector<Caravana> userCars;
  vector<CaravanaBarbara> enemyCars;
  User utilizador(world, initMoedas, userCars);
  vector<Item> items;

  while (1) {
    turno(world, userCars, enemyCars, utilizador, items);
    timer.advance();
  }
}

void Simulador::turno(Deserto &world, vector<Caravana> &userCars,
                      vector<CaravanaBarbara> &enemyCars, User &utilizador,
                      vector<Item> &items) {
  /***************************** MOSTRA BUFFER *****************************/

  /************************** LEITURA DE COMANDOS **************************/

  /************************** EXECUÇÃO DE COMANDOS **************************/

  for (auto cmd = cmdQueue.begin(); cmd != cmdQueue.end(); cmd++)
    execCmd(*cmd);
  cmdQueue.clear();

  /*********************** COMPORTAMENTOS AUTOMÁTICOS ***********************/

  for (auto uc = userCars.begin(); uc != userCars.end(); uc++) {
    switch (uc->getMvMode()) {
    case MOV_RUN:
    case MOV_AUTO:
      uc->mvAuto(userCars, enemyCars, items);
      break;
    case MOV_EMPTY:
      uc->mvEmpty();
      if (uc->getLifetime() == 0) {
        world[uc->getPos()].setLocalCar(nullptr);
        userCars.erase(uc);
      }
      break;
    case MOV_USR:
    default:
      break;
    }
    for (auto i = uc->getTargetPath().begin(); i != uc->getTargetPath().end();
         i++) {
      if (!world[i->second].isValid())
        break;
      world[uc->getPos()].setLocalCar(nullptr);
      uc->setPos(i->second);
      world[uc->getPos()].setLocalCar(&(*uc));
    }
    uc->resetTargetPath();

    for (Coords pos : uc->getPos().getAdjacent()) {
      if (!world[pos].hasItem())
        continue;
      Item &it = world[pos].getLocalItem();
      it.collect(utilizador, uc, userCars);
      world[pos].setLocalItem(nullptr);
      items.erase(find(items.begin(), items.end(), it));
    }
  }

  /******************************** BÁRBAROS ********************************/

  if (!(timer.get() % time2newBarbarian)) {
    Coords randPos = world.getRandomFreeCell().getCoords();
    enemyCars.push_back(CaravanaBarbara(randPos));
  }
  for (auto bc = enemyCars.begin(); bc != enemyCars.end(); bc++) {
    bc->mvAuto(userCars, enemyCars, items);
  }

  /************************* LUTAS ENTRE CARAVANAS *************************/

  for (auto uc = userCars.begin(); uc != userCars.end();) {
    vector<Caravana *> ecAdj;
    ecAdj.reserve(4);
    for (Coords pos : (*uc).getPos().getAdjacent()) {
      if (!world[pos].hasCaravana() ||
          world[pos].getLocalCaravana().ownedByUsr())
        continue;
      ecAdj.push_back(&world[pos].getLocalCaravana());
    }
    if (!ecAdj.size()) {
      uc++;
      continue;
    }

    unsigned int enemyAtk = 0;
    for (auto enmy : ecAdj)
      enemyAtk += enmy->attack();
    unsigned int usrAtk = uc->attack();
    if (enemyAtk == usrAtk) { // empate, todos perdem 10% da triulação
      uc->changeTripulantes(uc->getTripulantes() * -0.1);
      for (auto bc : ecAdj)
        bc->changeTripulantes(bc->getTripulantes() * -0.1);
    } else if (enemyAtk < usrAtk) {
      int chng = uc->changeTripulantes(uc->getTripulantes() * -0.2);
      for (auto bc : ecAdj)
        bc->changeTripulantes(chng * 2 / ecAdj.size());
    } else {
      int chng = 0;
      for (auto bc : ecAdj)
        chng += bc->changeTripulantes(bc->getTripulantes() * -0.2);
      uc->changeTripulantes(chng * 2);
    }

    for (auto bc = ecAdj.begin(); bc != ecAdj.end();)
      if (!(*bc)->getTripulantes()) {
        uc->changeAgua((*bc)->getAgua());
        world[(*bc)->getPos()].setLocalCar(nullptr);
        enemyCars.erase(find(enemyCars.begin(), enemyCars.end(), bc));
        ecAdj.erase(bc);
      } else
        ++bc;
    if (!uc->getTripulantes()) {
      for (auto bc : ecAdj)
        bc->changeAgua(uc->getAgua() / ecAdj.size());
      world[uc->getPos()].setLocalCar(nullptr);
      userCars.erase(uc);
      continue;
    }
    uc++;
  }

  /****************************** NOVOS ITENS ******************************/

  if (!(timer.get() % time2newItem)) {
    Coords randPos = world.getRandomFreeCell().getCoords();
    Item it = itemGen.get(randPos, itemLifeTime);
    items.push_back(itemGen.get(randPos, itemLifeTime));
    world[randPos].setLocalItem(&(*items.end()));
  }
}
