//
// Created by minis on 19/11/2024.
//

#include "../headers/Buffer.h"

Buffer::~Buffer() { delete[] buffer; }

void Buffer::alocarBuffer() {
  buffer = new char *[linhas];
  for (int i = 0; i < linhas; i++) {
    buffer[i] = new char[colunas];
    for (int j = 0; j < colunas; j++) {
      buffer[i][j] = ' ';
    }
  }
}

void Buffer::liberarBuffer() {
  for (int i = 0; i < linhas; i++) {
    delete[] buffer[i];
  }
  delete[] buffer;
}

void Buffer::limparBuffer() {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      buffer[i][j] = ' ';
    }
  }
}

void Buffer::validarPosicao(int linha, int coluna) const {
  if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
    throw std::out_of_range("A posição é inválida.");
  }
}

void Buffer::moverCursor(int linha, int coluna) {
  validarPosicao(linha, coluna);
  cursorLinha = linha;
  cursorColuna = coluna;
}

void Buffer::escreverChar(char c) {
  validarPosicao(cursorLinha, cursorColuna);
  buffer[cursorLinha][cursorColuna] = c;
  cursorColuna = (cursorColuna + 1) % colunas;
  if (cursorColuna == 0)
    cursorLinha = (cursorLinha + 1) % linhas;
}

void Buffer::escreverString(const std::string &str) {
  for (char c : str) {
    escreverChar(c);
  }
}

void Buffer::imprimir() const {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      std::cout << buffer[i][j];
    }
    std::cout << std::endl;
  }
};
