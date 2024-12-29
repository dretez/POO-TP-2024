#include "../headers/Simulador.h"
#include "../headers/Deserto.h"
#include "../headers/User.h"

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#define asUsrCars vector<Caravana>

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
  vector<shared_ptr<Caravana>> userCars;
  vector<shared_ptr<Caravana>> enemyCars;
  User utilizador(world, initMoedas, userCars);
  vector<shared_ptr<Item>> items;
  items.reserve(maxItems);

  while (1) {
    turno(world, userCars, enemyCars, utilizador, items);
    timer.advance();
  }
}

void Simulador::turno(Deserto &world, vector<shared_ptr<Caravana>> &userCars,
                      vector<shared_ptr<Caravana>> &enemyCars, User &utilizador,
                      vector<shared_ptr<Item>> &items) {

  /********************************** ITENS **********************************/
  // NOTE: DONE

  if (!(timer.get() % time2newItem) && items.size() < maxItems) {
    Coords randPos = world.getRandomFreeCell()->getCoords();
    RandItemGenerator::gen(items, randPos, itemLifeTime);
    world[randPos]->setItem(*items.end());
  }

  asUsrCars::iterator i;

  /***************************** MOSTRA BUFFER *****************************/

  /************************** LEITURA DE COMANDOS **************************/

  /************************** EXECUÇÃO DE COMANDOS **************************/

  for (auto cmd = cmdQueue.begin(); cmd != cmdQueue.end(); cmd++)
    execCmd(*cmd);
  cmdQueue.clear();

  /*********************** COMPORTAMENTOS AUTOMÁTICOS ***********************/
  // NOTE: DONE

  for (auto uc = userCars.begin(); uc != userCars.end(); uc++) {
    switch ((*uc)->getMvMode()) {
    case MOV_RUN:
    case MOV_AUTO:
      (*uc)->mvAuto(userCars, enemyCars, items);
      break;
    case MOV_EMPTY:
      (*uc)->mvEmpty();
      if ((*uc)->getLifetime() == 0) {
        userCars.erase(uc);
      }
      break;
    case MOV_USR:
    default:
      break;
    }

    // Percorre o caminho projetado até encontrar um obstáculo
    for (auto i = (*uc)->getTargetPath().begin();
         i != (*uc)->getTargetPath().end() && world[i->second]->isValid();
         i++) {
      world[(*uc)->getPos()]->unsetCaravana();
      (*uc)->setPos(i->second);
      world[(*uc)->getPos()]->setCaravana(*uc);
    }
    (*uc)->resetTargetPath();

    // Apanha os itens adjacentes
    for (Coords pos : (*uc)->getPos().getAdjacent()) {
      if (!world[pos]->hasItem())
        continue;
      shared_ptr<Item> it = world[pos]->getItem();
      it->collect(utilizador, uc, userCars);
      items.erase(find(items.begin(), items.end(), it));
    }
  }

  /******************************** BÁRBAROS ********************************/
  // NOTE:

  if (!(timer.get() % time2newBarbarian)) {
    Coords randPos = world.getRandomFreeCell()->getCoords();
    enemyCars.push_back(make_shared<CaravanaBarbara>(randPos));
  }
  for (auto bc = enemyCars.begin(); bc != enemyCars.end(); bc++) {
    (*bc)->mvAuto(userCars, enemyCars, items);

    // Percorre o caminho projetado até encontrar um obstáculo
    for (auto i = (*bc)->getTargetPath().begin();
         i != (*bc)->getTargetPath().end() && world[i->second]->isValid();
         i++) {
      world[(*bc)->getPos()]->unsetCaravana();
      (*bc)->setPos(i->second);
      world[(*bc)->getPos()]->setCaravana(*bc);

      // Apanha os itens adjacentes
      for (Coords pos : (*bc)->getPos().getAdjacent()) {
        if (!world[pos]->hasItem())
          continue;
        shared_ptr<Item> it = world[pos]->getItem();
        it->collect(utilizador, bc, userCars);
        items.erase(find(items.begin(), items.end(), it));
      }
    }
    (*bc)->resetTargetPath();
  }

  /************************* LUTAS ENTRE CARAVANAS *************************/
  // NOTE: Done

  for (auto uc = userCars.begin(); uc != userCars.end();) {
    vector<shared_ptr<Caravana>> ecAdj;
    ecAdj.reserve(4);
    for (Coords pos : (*uc)->getPos().getAdjacent()) {
      if (!world[pos]->hasCaravana() || world[pos]->getCaravana()->ownedByUsr())
        continue;
      ecAdj.push_back(world[pos]->getCaravana());
    }
    if (!ecAdj.size()) {
      uc++;
      continue;
    }

    unsigned int enemyAtk = 0;
    for (auto enmy : ecAdj)
      enemyAtk += enmy->attack();
    unsigned int usrAtk = (*uc)->attack();
    if (enemyAtk == usrAtk) { // empate, todos perdem 10% da triulação
      (*uc)->changeTripulantes((*uc)->getTripulantes() * -0.1);
      for (auto bc : ecAdj)
        bc->changeTripulantes(bc->getTripulantes() * -0.1);
    } else if (enemyAtk < usrAtk) {
      int chng = (*uc)->changeTripulantes((*uc)->getTripulantes() * -0.2);
      for (auto bc : ecAdj)
        bc->changeTripulantes(chng * 2 / ecAdj.size());
    } else {
      int chng = 0;
      for (auto bc : ecAdj)
        chng += bc->changeTripulantes(bc->getTripulantes() * -0.2);
      (*uc)->changeTripulantes(chng * 2);
    }

    for (auto bc = ecAdj.begin(); bc != ecAdj.end();)
      if (!(*bc)->getTripulantes()) {
        (*uc)->changeAgua((*bc)->getAgua());
        enemyCars.erase(find(enemyCars.begin(), enemyCars.end(), *bc));
        ecAdj.erase(bc);
      } else
        ++bc;
    if (!(*uc)->getTripulantes()) {
      for (auto bc : ecAdj)
        bc->changeAgua((*uc)->getAgua() / ecAdj.size());
      userCars.erase(uc);
      continue;
    }
    uc++;
  }
}
