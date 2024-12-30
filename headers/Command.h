#ifndef INCLUDE_HEADERS_COMANDS_H_
#define INCLUDE_HEADERS_COMANDS_H_

#include <array>
#include <cstddef>
#include <istream>
#include <string>
#include <vector>

using namespace std;

class Command {
public:
  template <size_t S>
  static bool input(istream &from, vector<Command> &to,
                    const array<string, S> &validCmds);

  template <size_t S> bool validate(const array<string, S> &validCmds) const;
  int argc() const;
  string operator[](int) const;

private:
  vector<string> arg;
};

#define CMD_F1_CONF "config"
#define CMD_F1_SAIR "sair"

#define CMD_F2_EXEC "exec"
#define CMD_F2_PROX "prox"
#define CMD_F2_BUYC "comprac"
#define CMD_F2_PRCE "precos"
#define CMD_F2_CITY "cidade"
#define CMD_F2_CRVN "caravana"
#define CMD_F2_BUYM "compra"
#define CMD_F2_SELL "vende"
#define CMD_F2_MOVE "move"
#define CMD_F2_AUTO "auto"
#define CMD_F2_STOP "stop"
#define CMD_F2_BARB "barbaro"
#define CMD_F2_SAND "areia"
#define CMD_F2_COIN "moedas"
#define CMD_F2_BUYT "tripul"
#define CMD_F2_SAVE "saves"
#define CMD_F2_LOAD "loads"
#define CMD_F2_LIST "lists"
#define CMD_F2_DELS "dels"
#define CMD_F2_EXIT "terminar"

#define F1_VALID_CMD                                                           \
  array<string, 2> { CMD_F1_CONF, CMD_F1_SAIR }
#define F2_VALID_CMD                                                           \
  array<string, 20> {                                                          \
    CMD_F2_EXEC, CMD_F2_PROX, CMD_F2_BUYC, CMD_F2_PRCE, CMD_F2_CITY,           \
        CMD_F2_CRVN, CMD_F2_BUYM, CMD_F2_SELL, CMD_F2_MOVE, CMD_F2_AUTO,       \
        CMD_F2_STOP, CMD_F2_BARB, CMD_F2_SAND, CMD_F2_COIN, CMD_F2_BUYT,       \
        CMD_F2_SAVE, CMD_F2_LOAD, CMD_F2_LIST, CMD_F2_DELS, CMD_F2_EXIT,       \
  }

#define CMD_1ARG                                                               \
  array<string, 4> { CMD_F1_SAIR, CMD_F2_PRCE, CMD_F2_LIST, CMD_F2_EXIT }
#define CMD_2ARG                                                               \
  array<string, 11> {                                                          \
    CMD_F1_CONF, CMD_F2_EXEC, CMD_F2_CITY, CMD_F2_CRVN, CMD_F2_SELL,           \
        CMD_F2_AUTO, CMD_F2_STOP, CMD_F2_COIN, CMD_F2_SAVE, CMD_F2_LOAD,       \
        CMD_F2_DELS                                                            \
  }
#define CMD_3ARG                                                               \
  array<string, 5> {                                                           \
    CMD_F2_BUYC, CMD_F2_BUYM, CMD_F2_MOVE, CMD_F2_BARB, CMD_F2_BUYT            \
  }
#define CMD_4ARG                                                               \
  array<string, 1> { CMD_F2_SAND }
#define CMD_1OR2ARG                                                            \
  array<string, 1> { CMD_F2_PROX }

#endif // INCLUDE_HEADERS_COMANDS_H_
