#include <iostream>
#include <pthread.h>
#include <cstring>

#include "jacobi.h"

int main (int argc, char *argv[]) {
  unsigned int J_ORDER, J_ROW_TEST, J_ITE_MAX;
  double J_ERROR;
  
  cin >> J_ORDER;
  cin >> J_ROW_TEST;
  cin >> J_ERROR;
  cin >> J_ITE_MAX;
  
  matriz *matrizA = new matriz(J_ORDER);
  matrizA->read();
  
  matriz *matrizB = new matriz(J_ORDER,1);
  matrizB->read();
  
  jacobi *processador = NULL;
  
  if (argc > 1 && strcmp (argv[1], "thread") == 0)
    processador = new jacobiThread (matrizA,matrizB);
  else if (argc > 1 && strcmp (argv[1], "normal") == 0) {
    cout << "oi" << endl;
    processador = new jacobi (matrizA,matrizB);
  }
  
  cout << "main " << &matrizB << endl;
  processador->jacobiRichardson(J_ROW_TEST,J_ERROR,J_ITE_MAX);
  
  if(matrizA != NULL) delete matrizA;
  if(matrizB != NULL) delete matrizB;
  if(processador != NULL) delete processador;
  
  return 0;
}
