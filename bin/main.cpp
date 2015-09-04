#include <iostream>
#include <pthread.h>
#include <cstring>
#include <time.h>

#include "jacobi.h"

int main (int argc, char *argv[]) {
  unsigned int J_ORDER, J_ROW_TEST, J_ITE_MAX;
  double J_ERROR;
    
  clock_t tinicio, tfim;  

  cin >> J_ORDER;
  cin >> J_ROW_TEST;
  cin >> J_ERROR;
  cin >> J_ITE_MAX;
  
  matriz *matrizA = new matriz(J_ORDER);
  matrizA->read();
  
  matriz *matrizB = new matriz(J_ORDER,1);
  matrizB->read();
    
  tinicio = clock();
  if (argc > 1 && strcmp (argv[1], "thread") == 0){
    jacobiThread *processador = NULL;
    processador = new jacobiThread (matrizA,matrizB);
    processador->jacobiRichardson(J_ROW_TEST,J_ERROR,J_ITE_MAX);
    if(processador != NULL) delete processador;
   } else if (argc > 1 && strcmp (argv[1], "normal") == 0){
    jacobi *processador = NULL;
    processador = new jacobi (matrizA,matrizB);
    processador->jacobiRichardson(J_ROW_TEST,J_ERROR,J_ITE_MAX);
    if(processador != NULL) delete processador;
   }

  tfim = clock();
  cout << (((double)(tfim-tinicio))/CLOCKS_PER_SEC) << endl;

  if(matrizA != NULL) delete matrizA;
  if(matrizB != NULL) delete matrizB;
 
  return 0;
}
