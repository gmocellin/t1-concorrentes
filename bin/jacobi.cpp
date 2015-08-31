#include "jacobi.h"
#include <cstring>
#include <cmath>
#include <pthread.h> // pthread

double norma (const double *Xk, const double *Xk2, unsigned int size) {
  double max_norma = 0;
  for (unsigned int i = 0; i < size; i++) {
    double aux = fabs(Xk[i] - Xk2[i]);
    if (aux < max_norma)
      max_norma = aux;
  }
  
  return max_norma;
}

jacobi::jacobi(matriz &matrizA, matriz &matrizB) {
  setMatrizA(matrizA);
  setMatrizB(matrizB);
  setSize(matrizA.getLinha());
}

jacobi::~jacobi() {
  delete this->matrizA;
  delete this->matrizB;
}

matriz jacobi::getMatrizA () {
  return this->matrizA;
}

matriz jacobi::getMatrizB () {
  return this->matrizB;
}

unsigned int jacobi::getSize () {
  return this->size;
}

void jacobi::jacobiRichardson (unsigned int J_ROW_TEST, double J_ERROR, unsigned int J_ITE_MAX) {
  unsigned int i;
  double Xk2[this->size];
  for (i = 0; i < this->size; i++)
    Xk2[i] = this->matrizB[0][i];
  double Xk[this->size];
  for (i = 0; i < this->size; i++)
    Xk[i] = 1;
  
  unsigned int n_iteracoes;
  for (n_iteracoes = 0; n_iteracoes < J_ITE_MAX; n_iteracoes++) {
    iterar(Xk2,Xk);
    
    for (i = 0; i < this->size; i++)
      Xk[i] = Xk2[i];
    
    double normasup = norma(Xk2,Xk,this->size);
    if (normasup < J_ERROR)
      break;
  }
  
  cout << "Numero de iteracoes: " << n_iteracoes << endl;
  
  double compare = 0;
  for(i = 0; i < this->size; i++)
    compare += this->matrizA[J_ROW_TEST][i] * Xk2[i];
  
  cout << "Linha de teste: " << J_ROW_TEST << " => [" << compare << "] =? " << this->matrizB[0][J_ROW_TEST] << endl;
}

virtual void jacobi::iterar (double *Xk2, double *Xk) {
  for(unsigned int i = 0; i < this->size; i++)
    processamento(i, Xk2, Xk);
}
  
void jacobi::processamento (unsigned int index, double *Xk2, double *Xk) {
  int aux = 0;
  for (unsigned int i = 0; i < this->size; i++) {
    if (i != index)
      aux += this->matrizA[index][i] * Xk[i];
  }
  Xk2[index] = (this->matrizB[0][index] - aux) / this->matrizA[index][index];
}
  
void jacobi::setMatrizA (matriz &matrizA) {
  this->matrizA = matrizA;
}

void jacobi::setMatrizB (matriz &matrizB) {
  this->matrizB = matrizB;
}

void jacobi::setSize (unsigned int size) {
  this->size = size;
}

jacobiThread::jacobiThread(matriz &matrizA, matriz &matrizB) { }

void jacobiThread::iterar (double *Xk2, double *Xk) { }
  
void jacobiThread::divideProcessamento (unsigned int ini, unsigned int fim, double *Xk2, double *Xk) { }
