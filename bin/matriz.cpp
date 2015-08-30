#include "matriz.h"

matriz::matriz(unsigned int linha, unsigned int coluna) {
  if (linha && coluna) {
    this.setColuna(coluna);
    this.setLinha(linha);
    this.matriz = new double* [this.getLinha()];
    for (unsigned int i = 0; i < this.getLinha(); i++)
      this.matriz[i] = new double [this.getColuna()];
  }
}

matriz::matriz(unsigned int size) {
  if (size) {
    this.setColuna(size);
    this.setLinha(size);
    this.matriz = new double* [this.getLinha()];
    for (unsigned int i = 0; i < this.getLinha(); i++)
      this.matriz[i] = new double [this.getColuna()];
  }
}

matriz::~matriz() {
  for (unsigned int i = 0; i < this.getLinha; i++)
    delete[] this.matriz[i];
  delete[] this.matriz;
}
  
double matriz::getLinha () {
  return this.linha;
}
double matriz::getColuna () {
  return this.coluna;
}

void matriz::setLinha (unsigned int linha) {
  this.linha = linha;
}
  
void matriz::setColuna (unsigned int coluna) {
  this.coluna = coluna;
}

void read () {
  for (unsigned int i = 0; i < this.getLinha(); i++) {
    for (unsigned int j = 0; j < this.getColuna(); j++)
      cin >> this.matriz[i][j];
  }
}