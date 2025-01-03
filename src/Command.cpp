#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

#include "../headers/Command.h"

int Command::argc() const { return arg.size(); }

string Command::operator[](int i) const { return arg[i]; }

bool Command::input(istream &from, vector<Command> &to,
                    const vector<string> &validCmds) {
  Command out;
  string in;
  bool ret = false;
  if (getline(from, in))
    ret = true;

  auto it = in.begin();
  // find first word
  for (; it != in.end() && isspace(*it); it++)
    ;
  while (it != in.end()) {
    string word;
    for (; it != in.end() && !isspace(*it); it++)
      word += *it;
    out.arg.push_back(word);
    // find next word
    for (; it != in.end() && isspace(*it); it++)
      ;
  }
  // if (any_of(validCmds.begin(), validCmds.end(), out.arg[0]))
  if (out.validate(validCmds))
    to.push_back(out);

  return ret;
}

bool Command::validate(const vector<string> &validCmds) const {
  if (argc() == 0) {
    cout << "Esperado comando" << endl;
    return false;
  }
  if (find(validCmds.begin(), validCmds.end(), arg[0]) == validCmds.end()) {
    cout << "Comando desconhecido" << endl;
    return false;
  }
  /*
  if (find(CMD_1ARG.begin(), CMD_1ARG.end(), arg[0]) != CMD_1ARG.end() && argc() != 1) {
    cout << "Número inesperado de argumentos. Esperado:\n" << arg[0] << endl;
    return false;
  }
  if (find(CMD_2ARG.begin(), CMD_2ARG.end(), arg[0]) != CMD_2ARG.end() && argc() != 2) {
    cout << "Número inesperado de argumentos. Esperado:\n"
         << arg[0] << " <arg>" << endl;
    return false;
  }
  if (find(CMD_3ARG.begin(), CMD_3ARG.end(), arg[0]) != CMD_3ARG.end() && argc() != 3) {
    cout << "Número inesperado de argumentos. Esperado:\n"
         << arg[0] << " <arg1> <arg2>" << endl;
    return false;
  }
  if (find(CMD_4ARG.begin(), CMD_4ARG.end(), arg[0]) != CMD_4ARG.end() && argc() != 4) {
    cout << "Número inesperado de argumentos. Esperado:\n"
         << arg[0] << " <arg1> <arg2> <arg3>" << endl;
    return false;
  }
  if (find(CMD_1OR2ARG.begin(), CMD_1OR2ARG.end(), arg[0]) != CMD_1OR2ARG.end() && argc() > 2) {
    cout << "Número inesperado de argumentos. Esperado:\n"
         << arg[0] << " <arg opcional>" << endl;
    return false;
  }
  */
  return true;
}
