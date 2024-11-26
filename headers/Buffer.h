
#ifndef BUFFER_H
#define BUFFER_H
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class Buffer {

private:
  int colunas;
  int linhas;

  char** buffer;
  int cursorLinha;
  int cursorColuna;

  void alocarBuffer() ;
  void liberarBuffer();
  void validarPosicao(int linha, int coluna) const ;


  public:
  Buffer();
  ~Buffer();
  void limparBuffer()   ;
  void moverCursor(int linha, int coluna);
  void escreverChar(char c) ;
  void escreverString(const std::string& str);
  void imprimir() const;


};



#endif //BUFFER_H
