include <iostream>
include <cpthread>

using namespace std;

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
  
  
  
  return 0;
}
