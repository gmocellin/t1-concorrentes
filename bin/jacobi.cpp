#include "jacobi.h"
#include <cstring>
#include <cmath>
#include <pthread.h> // pthread


double norma (const double *Xk, const double *Xk2, unsigned int size) {
  double max_norma = 0;
  double divide = 0;
  for (unsigned int i = 0; i < size; i++) {
    double aux = fabs(Xk[i] - Xk2[i]);
    double aux2 = fabs(Xk[i]);
    if (aux > max_norma)
      max_norma = aux;
    if (aux2 > divide)
      divide = aux2;
  }
  
  return max_norma/divide;
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

void prepare_Matriz(double **matrizA_Matriz, double **matrizB_Matriz, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if(i != j)
	matrizA_Matriz[i][j] = matrizA_Matriz[i][j] / matrizA_Matriz[i][i];
    }
    matrizB_Matriz[i][0] = matrizB_Matriz[i][0] / matrizA_Matriz[i][i];
    matrizA_Matriz[i][i] = 0;
  }
}

void make_a_copy(double **copyA, double **copyB, double **matrizA_Matriz, double **matrizB_Matriz, int size) {
  copyA = new double* [size];
  copyB = new double* [size];
  unsigned int i;
  for (i = 0; i < size; i++) {
    copyA[i] = new double [size];
    copyB[i] = new double [1];
    for (unsigned int j = 0; j < size; j++)
      copyA[i][j] = matrizA_Matriz[i][j];
    copyB[i][0] = matrizB_Matriz[i][0];
  }
}

void jacobi::jacobiRichardson (unsigned int J_ROW_TEST, double J_ERROR, unsigned int J_ITE_MAX) {
  unsigned int i;
  double **matrizB_Matriz = this->matrizB->getMatriz();
  double **matrizA_Matriz = this->matrizA->getMatriz();
  
  /* gambiarra para nao perder os dados iniciais da matriz */
  double **copyA, **copyB;
  copyA = new double* [size];
  copyB = new double* [size];
  for (i = 0; i < this->size; i++) {
    copyA[i] = new double [size];
    copyB[i] = new double [1];
    for (unsigned int j = 0; j < size; j++)
      copyA[i][j] = matrizA_Matriz[i][j];
    copyB[i][0] = matrizB_Matriz[i][0];
  }
  
  double Xk2[this->size];
  prepare_Matriz(matrizA_Matriz,matrizB_Matriz,this->size);
  for (i = 0; i < this->size; i++)
    Xk2[i] = matrizB_Matriz[i][0];
  double Xk[this->size];
  
  unsigned int n_iteracoes;
  for (n_iteracoes = 0; n_iteracoes < J_ITE_MAX; n_iteracoes++) {
    for (i = 0; i < this->size; i++)
      Xk[i] = Xk2[i];
    
    iterar(Xk2,Xk);    
    
    double normasup = norma(Xk2,Xk,this->size);
    if (normasup < J_ERROR)
      break;
  }
  
  cout << "Numero de iteracoes: " << n_iteracoes << endl;
  
  double compare = 0;
  for(i = 0; i < this->size; i++)
    compare += copyA[J_ROW_TEST][i] * Xk2[i];
  
  cout << "Linha de teste: " << J_ROW_TEST << " => [" << compare << "] =? " << copyB[J_ROW_TEST][0] << endl;
}

void jacobi::iterar (double *Xk2, double *Xk) {
  for(unsigned int i = 0; i < this->size; i++)
    processamento(i, Xk2, Xk);
}
  
void jacobi::processamento (unsigned int index, double *Xk2, double *Xk) {
  double aux = 0.0;
  double **matrizB_Matriz = this->matrizB->getMatriz();
  double **matrizA_Matriz = this->matrizA->getMatriz();
  
  for (unsigned int i = 0; i < this->size; i++) {
    if (i != index)
      aux -= matrizA_Matriz[index][i] * Xk[i];
  }
  Xk2[index] = (aux + matrizB_Matriz[index][0]);
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

//Jacobi Thread ------------------------------------------------------------------------

typedef struct {
  jacobi *thread_jacobi;
  double *Xk, *Xk2 ;
  int ini, fim;
} thread_struct; 


jacobiThread::jacobiThread(matriz *matrizA, matriz *matrizB) : jacobi(matrizA,matrizB) { 
  setMatrizA(matrizA);
  setMatrizB(matrizB);
  setSize(matrizA->getLinha());
  this->n_threads = 4;
  this->min_size_threads = floor(((this->size)/(this->n_threads)));
  this->Threads = new pthread_t[this->n_threads];
}

jacobiThread::~jacobiThread(){ 
  this->matrizA = NULL;
  this->matrizB = NULL;
  if(this->Threads != NULL){
    delete Threads;
    this->Threads = NULL;
  }
}

void *divideProcessamento (void *args_thread) { //(unsigned int ini, unsigned int fim, double *Xk2, double *Xk) {

  thread_struct *arg_struct = (thread_struct *) args_thread;

  for(unsigned int i = arg_struct->ini; i <= arg_struct->fim; i++)
    arg_struct->thread_jacobi->processamento(i, arg_struct->Xk2, arg_struct->Xk);
   
}

void jacobiThread::iterar (double *Xk2, double *Xk) {
 
  thread_struct args_thread[this->n_threads];  

  for(unsigned int i; i < this->n_threads; i++){
    args_thread[i].thread_jacobi = this;
    args_thread[i].Xk = Xk;
    args_thread[i].Xk2 = Xk2;
    args_thread[i].ini = i*(this->min_size_threads);
    if (i < (this->n_threads-1))
      args_thread[i].fim = ((i+1)*(this->min_size_threads)-1);
    else
      args_thread[i].fim = (this->size)-1;
    
    pthread_create (&(this->Threads[i]), NULL, &divideProcessamento, &args_thread[i]);   
  }

  for(unsigned int i; i < this->n_threads; i++){
    pthread_join(this->Threads[i], NULL);
  }
}
 

