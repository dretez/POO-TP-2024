#ifndef INCLUDE_HEADERS_SIMULADOR_H_
#define INCLUDE_HEADERS_SIMULADOR_H_

#include "Deserto.h"

#include <string>

using namespace std;

class SimConfig {
public:
  SimConfig();

  void loadConfFile(string confFileName);
  void saveConfFile(string confFileName);

private:
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

class Simulador {
public:
  Simulador();

  void start();
  void fase1();
  void fase2();

private:
  SimConfig conf;
};

#endif // INCLUDE_HEADERS_SIMULADOR_H_
