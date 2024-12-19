#include "../headers/Simulador.h"

#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]) {
  if (argc == 2) {
    srand(atoi(argv[1])); // always use the same seed for deterministic results
  } else
    srand((time(NULL)));

  Simulador sim;
  sim.start();

  return 0;
}
