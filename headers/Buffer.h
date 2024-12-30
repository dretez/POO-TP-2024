#ifndef BUFFER_H
#define BUFFER_H

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "SimComponents.h"

class Buffer {
public:
  Buffer(string nome);
  ~Buffer();
  string getNome() const;
  void limparBuffer();
  void moverCursor(int linha, int coluna);
  void escreverChar(char c);
  void escreverString(const std::string &str);
  void imprimir() const;

private:
  int colunas;
  int linhas;
  string nome;

  char **buffer;
  int cursorLinha;
  int cursorColuna;

  void alocarBuffer();
  void liberarBuffer();
  void validarPosicao(int linha, int coluna) const;
};

#endif // BUFFER_H
