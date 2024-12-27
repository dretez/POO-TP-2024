#include "../headers/Simulador.h"

#include <iostream>

#include "../headers/Buffer.h"
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <locale.h>

Timer::Timer(unsigned int startTime) : startTime(startTime) {}
unsigned int Timer::getStartTime() const {
  return startTime;
}

Simulador::Simulador(unsigned int startTime) : timer(startTime) {}

SimConfig::SimConfig()
    : width(0), height(0), initMoedas(0), time2newItem(0),
      itemLifeTime(0), maxItems(0), mercSellVal(0), mercBuyVal(0),
      priceCar(0), time2newBarbarian(0), barbarianLifeTime(0) {
  savedMap = "";
}

using namespace std;

bool lerConfiguracao(const string& nomeFicheiro) {
  ifstream ficheiro(nomeFicheiro);

  if (!ficheiro) {
    cerr << "Erro: Não foi possível abrir o ficheiro." << endl;
    return false;
  }

  int linhas, colunas;
  ficheiro >> linhas >> colunas;
  ficheiro.ignore();

  cout << "Dimensoes do mapa: Linhas = " << linhas << ", Colunas = " << colunas << endl;

  string linha;
  cout << "\nMapa:\n";
  for (int i = 0; i < linhas; i++) {
    if (!getline(ficheiro, linha)) {
      linha = "";
    }
    cout << linha << endl;
  }


  ficheiro.close();
  return true;
}
int processacomando(string& comando) {
  if (comando == "sair") {
    cout << "A sair do jogo..." << endl;
    exit(EXIT_SUCCESS);
  } else if (comando.rfind("config ", 0) == 0) { // Verifica se começa com "config "
    string nomeFicheiro = comando.substr(7); // Extrai o nome do ficheiro
    if (lerConfiguracao(nomeFicheiro)) { // Função ajustada para apenas ler e exibir
      cout << "Configuracao carregada com sucesso!" << endl;
    } else {
      cout << "Erro ao carregar a configuracao." << endl;
    }
  } else {
    cout << "Comando desconhecido: " << comando << endl;
  }
  return 0;
}

void Simulador::start() {
  while (1) {
    fase1();
    //fase2();
  }
}

void Simulador::fase1() {
  while (1) {
    setlocale(LC_ALL, "Portuguese");

    system("cls");
    char comeca;
    string comando;

    cout << "Seja bem-vindo ao simulador de Viagens no Deserto!\n"
            "Deseja comecar o jogo? (Y/N)\n";
    cin >> comeca;
    cin.ignore(); // Limpa o '\n' deixado no buffer pelo cin

    if (comeca == 'y' || comeca == 'Y') {
      cout << "Estes sao os comandos disponiveis:\n"
              "config <nomeFicheiro> - Le as caracteristicas do mapa do deserto\n"
              "sair - Terminar o programa\n";

      // Loop para ler e processar comandos continuamente
      while (true) {
        cout << "\nComando a executar: ";
        getline(cin, comando);

        if (!comando.empty()) { // Processa apenas se o comando não estiver vazio
          processacomando(comando);
        }
      }
    }
    else {
      cout << "A Terminar..." << endl;
      exit(EXIT_SUCCESS);
    }
  }
}

/*void Simulador::fase2() {
  Deserto world(width, height);
  vector<Caravana> userCars;
  vector<CaravanaBarbara> enemyCars;
  User utilizador(world, initMoedas, userCars);

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
      case MOV_AUTO:
        uc->mvAuto(userCars, enemyCars, world.getAllItems());
      }
    }

    // spawn barbarians if needed and move barbarian caravans
    if (!(timer.get() % time2newBarbarian)) {
      Coords randPos = world.getRandomFreeCell().getCoords();
      enemyCars.push_back(CaravanaBarbara(randPos));
    }
    vector<CaravanaBarbara>::iterator bc;
    for (bc = enemyCars.begin(); bc != enemyCars.end(); bc++) {
      bc->mvAuto(userCars);
    }

    //
    // fight between user and barbarian caravans
    //
    // spawn items if needed
  }
}
*/
