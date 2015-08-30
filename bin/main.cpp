#include "matriz.h"
#include "jacobi.h"

#include <cstring>

int main (int argc, char *argv[]) {
  unsigned int J_ORDER, J_ROW_TEST, J_ITE_MAX;
  double J_ERROR;
  
  cin >> J_ORDER;
  cin >> J_ROW_TEST;
  cin >> J_ERROR;
  cin >> J_ITE_MAX;
  
  matriz matrizA (J_ORDER);
  matrizA.read();
  
  matriz matrizB (J_ORDER,1);
  matrizB.read();
  
  jacobi *processador;
  
  if (argc > 1 && strcmp (argv[1], "thread") == 0)
    processador = new jacobiThread (matrizA,matrizB);
  else if (argc > 1 && strcmp (argv[1], "normal") == 0)
    processador = new jacobi (matrizA,matrizB);
  
  processador->jacobiRichardson(J_ROW_TEST,J_ERROR,J_ITE_MAX);
  
  delete processador;
  
  return 0;
}
