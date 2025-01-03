#ifndef INCLUDE_HEADERS_SIMULADOR_H_
#define INCLUDE_HEADERS_SIMULADOR_H_

#include <memory>
#include <string>
#include <vector>

#include "Caravanas.h"
#include "Deserto.h"
#include "Items.h"
#include "Timer.h"
#include "Command.h"
#include "Buffer.h"

using namespace std;

class SimConfig {
public:
  SimConfig();

  void loadConfFile(ifstream &confFile);
  void saveConfFile(ifstream &confFile);

protected:
  unsigned int width, height;
  string savedMap;
  int initMoedas;
  unsigned int time2newItem;
  unsigned int itemLifeTime;
  unsigned int maxItems;
  int mercSellVal, mercBuyVal;
  int priceCar;
  unsigned int time2newBarbarian;
  unsigned int barbarianLifeTime;
};

class Simulador : public SimConfig {
public:
  Simulador(unsigned int startTime = 1);

  void start();

  vector<shared_ptr<Caravana>> &getUCars();
  vector<shared_ptr<Caravana>> &getECars();
  vector<shared_ptr<Item>> &getItems();

private:
  void fase1();
  bool fase2();
  void turno(Deserto &, User &);

  int execF1Cmd(const Command &cmd);
  int execCmd(const Command &, Deserto &, User &);

  unsigned int proxCount;
  vector<Command> cmdQueue;
  vector<Command>::iterator fileCmdQSavePoint;
  vector<Buffer> savedBuffers;
  vector<shared_ptr<Caravana>> userCars;
  vector<shared_ptr<Caravana>> enemyCars;
  vector<shared_ptr<Item>> items;
  Timer timer;
};

#endif // INCLUDE_HEADERS_SIMULADOR_H_
