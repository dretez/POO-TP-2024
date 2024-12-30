#include "../headers/Simulador.h"
#include "../headers/Buffer.h"
#include "../headers/Command.h"
#include "../headers/Deserto.h"
#include "../headers/User.h"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

SimConfig::SimConfig() {}
Simulador::Simulador(unsigned int startTime) : timer(startTime), proxCount(0) {}

vector<shared_ptr<Item>>& Simulador::getItems() { return items; }


void Simulador::start()
{
  while (true)
  {
    fase1();
    fase2();
  }
}
vector<shared_ptr<Caravana>>& Simulador::getUCars() { return userCars; }
vector<shared_ptr<Caravana>>& Simulador::getECars() { return enemyCars; }


void Simulador::fase1() {
  cout << "Bien Venue";
  while (true) {
    do {
      Command::input(cin, cmdQueue, F1_VALID_CMD);
    } while (cmdQueue.empty());
    auto cmd = cmdQueue.begin();
    if (execF1Cmd(*cmd))
      break;
    cmdQueue.clear();
  }
}

bool Simulador::fase2() {
  timer.reset();
  Deserto world(width, height);
  userCars.clear();
  enemyCars.clear();
  items.clear();
  items.reserve(maxItems);
  User user(world, initMoedas, userCars);

  while (1) {
    turno(world, user);
    timer.advance();
  }
}

void Simulador::turno(Deserto &world, User &user) {

  /********************************** ITENS **********************************/
  // NOTE: DONE

  if (!(timer.get() % time2newItem) && items.size() < maxItems) {
    Coords randPos = world.getRandomFreeCell()->getCoords();
    RandItemGenerator::gen(items, randPos, itemLifeTime);
    world[randPos]->setItem(*items.end());
  }

  /***************************** MOSTRA BUFFER *****************************/

  Buffer(*this, world, width, height).imprimir();

  /************************** LEITURA DE COMANDOS **************************/

  do {
    Command::input(cin, cmdQueue, F2_VALID_CMD);
  } while (cmdQueue.back()[0] != "prox");

  /************************** EXECUÇÃO DE COMANDOS **************************/

  for (auto cmd = cmdQueue.begin(); cmd != cmdQueue.end(); cmd++)
    execCmd(*cmd, world, user);
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
      it->collect(user, uc, userCars);
      items.erase(find(items.begin(), items.end(), it));
    }
  }

  /******************************** BÁRBAROS ********************************/
  // NOTE: Done

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
        it->collect(user, bc, userCars);
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

int Simulador::execF1Cmd(const Command &cmd){
  if (cmd[0] == CMD_F1_CONF) {
    ifstream file(cmd[1]);
    if (!file) {
      cout << "Não foi possível abrir o ficheiro de configuração \"" << cmd[1]
           << '"' << endl;
      return 0;
    }
    loadConfFile(file);
    file.close();
    return 1;
  } else if (cmd[0] == CMD_F1_SAIR) {
    exit(0);
  }
}
int Simulador::execCmd(const Command &cmd, Deserto &world, User &user) {
  if (cmd[0] == CMD_F2_EXEC) {
    ifstream file(cmd[1]);
    if (!file) {
      cout << "Não foi possível abrir o ficheiro de comandos \"" << cmd[1]
           << '"' << endl;
      return 0;
    }

    vector<Command> extraCmdQueue;
    while (Command::input(file, extraCmdQueue, F2_VALID_CMD)) {
    }

    // WARN: risk of infinite recursion
    for (auto cmd = extraCmdQueue.begin(); cmd != extraCmdQueue.end(); cmd++) {
      fileCmdQSavePoint = cmd + 1;
      int ret = execCmd(*cmd, world, user);
      if (ret)
        return ret;
    }
    extraCmdQueue.clear();

    file.close();
    return 0;
  } else if (cmd[0] == CMD_F2_PROX) {
    int counter;
    try {
      counter = cmd.argc() == 2 && stoi(cmd[1]) ? stoi(cmd[1]) : 1;
    } catch (exception &err) {
      counter = 1;
    }
    proxCount += counter;
    return 2;
  } else if (cmd[0] == CMD_F2_BUYC) {
    if (cmd[1].size() > 1) {
      cout << '\"' << cmd[1] << "\" não é uma cidade" << endl;
      return 0;
    }
    for (auto city : world.getCities()) {
      if (city.getNome() != cmd[1][0])
        continue;
      if (cmd[2] == "C" && !city.getCComercio()) {
        userCars.push_back(make_shared<CaravanaComercio>(city.getPos()));
        city.unsetCComercio();
      } else if (cmd[2] == "M" && !city.getCMilitar()) {
        userCars.push_back(make_shared<CaravanaMilitar>(city.getPos()));
        city.unsetCMilitar();
      } else if (cmd[2] == "S" && !city.getCSecreta()) {
        userCars.push_back(make_shared<CaravanaSecreta>(city.getPos()));
        city.unsetCSecreta();
      } else {
        cout << "Tipo de caravana \"" << cmd[2] << "\" desconhecido" << endl;
        return 0;
      }
      return 0;
    }
    cout << "A cidade " << cmd[1] << "não foi encontrada" << endl;
    return 0;
  } else if (cmd[0] == CMD_F2_PRCE) {
    cout << "Preço de venda de mercadoria: " << mercSellVal << '\n'
         << "Preço de compra de mercadoria: " << mercBuyVal << endl;
    return 0;
  } else if (cmd[0] == CMD_F2_CITY) {
    if (cmd[1].size() > 1) {
      cout << '\"' << cmd[1] << "\" não é uma cidade" << endl;
      return 0;
    }
    for (auto city : world.getCities()) {
      if (city.getNome() != cmd[1][0])
        continue;
      for (auto car : userCars) {
        if (!(car->getPos() == city.getPos()))
          continue;
        cout << car->getTipo() << " (id=" << car->getId() << ")\n";
      }
      for (auto car : enemyCars) {
        if (!(car->getPos() == city.getPos()))
          continue;
        cout << car->getTipo() << " (id=" << car->getId() << ")\n";
      }
      return 0;
    }
    cout << "A cidade " << cmd[1] << "não foi encontrada" << endl;
    return 0;
  } else if (cmd[0] == CMD_F2_CRVN) {
    for (auto car : userCars) {
      if (to_string(car->getId()) != cmd[1]) {
        continue;
      }
      cout << car->info();
      return 0;
    }
    cout << "A caravana " << cmd[1] << "não foi encontrada" << endl;
    return 0;
  } else if (cmd[0] == CMD_F2_BUYM) {
    try {
      int a = stoi(cmd[2]);
      if (a <= 0)
        throw;
    } catch (exception &) {
      cout << "Não é possível comprar \"" << cmd[2]
           << "\" toneladas de mercadoria" << endl;
      return 0;
    }
    for (auto car : userCars) {
      if (to_string(car->getId()) != cmd[1]) {
        continue;
      }
      if (!world[car->getPos()]->isCity()) {
        cout << "Caravana \"" << cmd[1] << "\" não está numa cidade" << endl;
        break;
      }
      int total = car->changeMerc(stoi(cmd[2]));
      user.changeMoedas(-total * mercBuyVal);
      break;
    }
    return 0;
  } else if (cmd[0] == CMD_F2_SELL) {
    for (auto car : userCars) {
      if (to_string(car->getId()) != cmd[1]) {
        continue;
      }
      if (!world[car->getPos()]->isCity()) {
        cout << "Caravana \"" << cmd[1] << "\" não está numa cidade" << endl;
        break;
      }
      user.changeMoedas(car->getMerc() * mercBuyVal);
      car->setMerc(0);
      break;
    }
    return 0;
  } else if (cmd[0] == CMD_F2_MOVE) {
    Coords dir;
    if (cmd[2] == "D") {
      dir = Coords(1, 0);
    } else if (cmd[2] == "E") {
      dir = Coords(-1, 0);
    } else if (cmd[2] == "C") {
      dir = Coords(0, 1);
    } else if (cmd[2] == "B") {
      dir = Coords(0, -1);
    } else if (cmd[2] == "CE") {
      dir = Coords(-1, 1);
    } else if (cmd[2] == "CD") {
      dir = Coords(1, 1);
    } else if (cmd[2] == "BE") {
      dir = Coords(-1, -1);
    } else if (cmd[2] == "BD") {
      dir = Coords(1, -1);
    } else {
      cout << "Direção \"" << cmd[2] << "\" desconhecida" << endl;
      return 0;
    }
    for (auto car : userCars) {
      if (to_string(car->getId()) != cmd[1]) {
        continue;
      }
      car->mv(dir);
      break;
    }
    return 0;
  } else if (cmd[0] == CMD_F2_AUTO) {
    for (auto car : userCars) {
      if (to_string(car->getId()) != cmd[1]) {
        continue;
      }
      car->setMvMode(MOV_AUTO);
      break;
    }
    return 0;
  } else if (cmd[0] == CMD_F2_STOP) {
    for (auto car : userCars) {
      if (to_string(car->getId()) != cmd[1]) {
        continue;
      }
      car->setMvMode(MOV_USR);
      break;
    }
    return 0;
  } else if (cmd[0] == CMD_F2_BARB) {
    try {
      int a = stoi(cmd[1]);
      a = stoi(cmd[2]);
    } catch (exception &) {
      cout << '(' << cmd[1] << ',' << cmd[2] << ") não são coordenadas válidas"
           << endl;
      return 0;
    }
    enemyCars.push_back(
        make_shared<CaravanaBarbara>(Coords(stoi(cmd[1]), stoi(cmd[2]))));
  } else if (cmd[0] == CMD_F2_SAND) {
    try {
      int a = stoi(cmd[1]);
      a = stoi(cmd[2]);
    } catch (exception &) {
      cout << '(' << cmd[1] << ',' << cmd[2] << ") não são coordenadas válidas"
           << endl;
      return 0;
    }
    int radius;
    try {
      radius = stoi(cmd[3]);
      if (radius <= 0)
        throw;
    } catch (exception &) {
      cout << '\"' << cmd[3] << "\" não é um valor de raio válido" << endl;
      return 0;
    }
    Coords center(stoi(cmd[1]), stoi(cmd[2]));
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        shared_ptr<Cell> aux = world[Coords(i, j)];
        if (aux->getCoords().distance(center) <= radius)
          aux->setStorm();
      }
    }
  } else if (cmd[0] == CMD_F2_COIN) {
    int total;
    try {
      total = stoi(cmd[1]);
    } catch (exception &) {
      cout << '\"' << cmd[1] << "\" não é um valor de moedas válido" << endl;
      return 0;
    }
    user.changeMoedas(total);
    return 0;
  } else if (cmd[0] == CMD_F2_BUYT) {
    try {
      int a = stoi(cmd[2]);
      if (a <= 0)
        throw;
    } catch (exception &) {
      cout << '\"' << cmd[2] << "\" não é um valor de tripulantes válido"
           << endl;
      return 0;
    }
    for (auto car : userCars) {
      if (to_string(car->getId()) != cmd[1]) {
        continue;
      }
      if (!world[car->getPos()]->isCity()) {
        cout << "Caravana \"" << cmd[1] << "\" não está numa cidade" << endl;
        break;
      }
      int total = car->changeTripulantes(stoi(cmd[2]));
      user.changeMoedas(-total);
      break;
    }
    return 0;
  } else if (cmd[0] == CMD_F2_SAVE) {
    savedBuffers.emplace_back(*this, world, width, height, cmd[1]);
    return 0;
  } else if (cmd[0] == CMD_F2_LOAD) {
    for (const auto& buf : savedBuffers) {
      if (buf.getNome() != cmd[1])
        continue;
      buf.imprimir();
      return 0;
    }
    cout << "Buffer " << cmd[1] << " não encontrado" << endl;
  } else if (cmd[0] == CMD_F2_LIST) {
    for (const auto& buf : savedBuffers)
      cout << buf.getNome() << '\n';
    cout << endl;
    return 0;
  } else if (cmd[0] == CMD_F2_DELS) {
    for (auto buf = savedBuffers.begin(); buf != savedBuffers.end(); ++buf) {
      if (buf->getNome() != cmd[1])
        continue;
      savedBuffers.erase(buf);
      return 0;
    }
    cout << "Buffer \"" << cmd[1] << "\" não encontrado" << endl;
  } else if (cmd[0] == CMD_F2_EXIT) {
    return 1;
  }

  // Something went terribly wrong, check your command implementations
  cout << "Comando inesperado:";
  for (int i = 0; i < cmd.argc(); i++)
    cout << ' ' << cmd[i];
  cout << endl;
  return true;
}

void SimConfig::loadConfFile(ifstream &confFile) {
  string discard;
  confFile >> discard >> height;
  confFile >> discard >> width;
  for (int i = 0; i < height; i++) {
    getline(confFile, discard);
  }
  confFile >> discard >> initMoedas;
  confFile >> discard >> time2newItem;
  confFile >> discard >> itemLifeTime;
  confFile >> discard >> maxItems;
  confFile >> discard >> mercSellVal;
  confFile >> discard >> mercBuyVal;
  confFile >> discard >> priceCar;
  confFile >> discard >> time2newBarbarian;
  confFile >> discard >> barbarianLifeTime;
}
