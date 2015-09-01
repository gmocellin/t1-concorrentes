#include "matriz.h"

matriz::matriz(unsigned int linha, unsigned int coluna) {
  if (linha && coluna) {
    this->setColuna(coluna);
    this->setLinha(linha);
    this->setMatriz();
  }
}

matriz::matriz(unsigned int size) {
  if (size) {
    
    this->setColuna(size);
    this->setLinha(size);
    this->setMatriz();
  }
}

matriz::~matriz() {
  for (unsigned int i = 0; i < this->getLinha(); i++)
    delete[] this->Matriz[i];
  delete[] this->Matriz;
}

double matriz::getLinha () {
  return this->linha;
}
double matriz::getColuna () {
  return this->coluna;
}

double** matriz::getMatriz () {
  return this->Matriz;
}

void matriz::setLinha (unsigned int linha) {
  this->linha = linha;
}

void matriz::setColuna (unsigned int coluna) {
  this->coluna = coluna;
}

void matriz::setMatriz () {
  this->Matriz = new double* [(int)this->getLinha()];
  for (unsigned int i = 0; i < this->getLinha(); i++)
    this->Matriz[i] = new double [(int)this->getColuna()];
}

void matriz::read () {
  for (unsigned int i = 0; i < this->getLinha(); i++) {
    for (unsigned int j = 0; j < this->getColuna(); j++)
      cin >> this->Matriz[i][j];
  }
}

void matriz::print() {
  for(unsigned int i=0; i < this->getLinha(); i++){
    for (unsigned int j = 0; j < this->getColuna(); j++)
      cout << this->Matriz[i][j];
    cout << endl;
  }
}
