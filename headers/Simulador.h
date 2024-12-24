#ifndef INCLUDE_HEADERS_SIMULADOR_H_
#define INCLUDE_HEADERS_SIMULADOR_H_

#include <cstdlib>
#include <deque>
#include <memory>
#include <string>
#include <vector>

#include "Caravanas.h"
#include "SimComponents.h"
#include "Timer.h"

using namespace std;

class SimConfig {
public:
  SimConfig();

  void loadConfFile(string confFileName);
  void saveConfFile(string confFileName);

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
  void fase1();
  void fase2();

  void execCmd(string cmd);

private:
  deque<string> cmdQueue;
  Timer timer;
};

#endif // INCLUDE_HEADERS_SIMULADOR_H_
