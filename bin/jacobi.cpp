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
  
  cout << max_norma << endl;
  return max_norma;
}

jacobi::jacobi(matriz *matrizA, matriz *matrizB) {
  setMatrizA(matrizA);
  setMatrizB(matrizB);
  setSize(matrizA->getLinha());
}

jacobi::~jacobi() { 
  this->matrizA = NULL;
  this->matrizB = NULL;
}

matriz* jacobi::getMatrizA () {
  return this->matrizA;
}

matriz* jacobi::getMatrizB () {
  return this->matrizB;
}

unsigned int jacobi::getSize () {
  return this->size;
}

void jacobi::jacobiRichardson (unsigned int J_ROW_TEST, double J_ERROR, unsigned int J_ITE_MAX) {
  unsigned int i;
  double **matrizB_Matriz = this->matrizB->getMatriz();
  double **matrizA_Matriz = this->matrizA->getMatriz();
  double Xk2[this->size];
  for (i = 0; i < this->size; i++)
    Xk2[i] = matrizB_Matriz[0][i];
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
    compare += matrizA_Matriz[J_ROW_TEST][i] * Xk2[i];
  
  cout << "Linha de teste: " << J_ROW_TEST << " => [" << compare << "] =? " << matrizB_Matriz[0][J_ROW_TEST] << endl;
}

void jacobi::iterar (double *Xk2, double *Xk) {
  for(unsigned int i = 0; i < this->size; i++)
    processamento(i, Xk2, Xk);
}
  
void jacobi::processamento (unsigned int index, double *Xk2, double *Xk) {
  int aux = 0;
  double **matrizB_Matriz = this->matrizB->getMatriz();
  double **matrizA_Matriz = this->matrizA->getMatriz();
  
  for (unsigned int i = 0; i < this->size; i++) {
    if (i != index)
      aux += matrizA_Matriz[index][i] * Xk[i];
  }
  Xk2[index] = (matrizB_Matriz[0][index] - aux) / matrizA_Matriz[index][index];
}
  
void jacobi::setMatrizA (matriz *matrizA) {
  this->matrizA = matrizA;
}

void jacobi::setMatrizB (matriz *matrizB) {
  this->matrizB = matrizB;
}

void jacobi::setSize (unsigned int size) {
  this->size = size;
}

jacobiThread::jacobiThread(matriz *matrizA, matriz *matrizB) : jacobi(matrizA,matrizB) { }

void jacobiThread::iterar (double *Xk2, double *Xk) { }
  
void jacobiThread::divideProcessamento (unsigned int ini, unsigned int fim, double *Xk2, double *Xk) { }
