#include "matriz.h"

class jacobi {
public:
  /* construtores */
  jacobi(matriz *matrizA, matriz *matrizB);
  /* destrutore */
  ~jacobi();
  
  matriz* getMatrizA ();
  matriz* getMatrizB ();
  unsigned int getSize ();
  
  // 
  void jacobiRichardson (unsigned int J_ROW_TEST, double J_ERROR, unsigned int J_ITE_MAX);
  void processamento (unsigned int index, double *proximo, double *anterior);
   
protected:
  virtual void iterar (double *proximo, double *anterior);
 
  void setMatrizA (matriz *matrizA);
  void setMatrizB (matriz *matrizB);
  void setSize (unsigned int size);
  
  // matriz processada
  matriz *matrizA;
  // vetor
  matriz *matrizB;
  // tamanho das duas matrizes
  unsigned int size;
};

class jacobiThread : public jacobi {
public:
  jacobiThread(matriz *matrizA, matriz *matrizB);
  ~jacobiThread();
  
protected:
  void iterar (double *proximo, double *anterior);
  
  //void divideProcessamento (unsigned int ini, unsigned int fim, double *proximo, double *anterior);
  
  //void processamento (unsigned int index, double *Xk2, double *Xk); //(unsigned int ini, unsigned int fim, double *Xk2, double *Xk) {

  int n_threads;

  int min_size_threads;
  
  pthread_t *Threads;
};
