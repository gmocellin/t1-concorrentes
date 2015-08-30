#include <iostream>

using namespace std;

class matriz {
public:
  /* construtores */
  matriz(unsigned int linha, unsigned int coluna);
  matriz(unsigned int size);
  /* destrutores */
  ~matriz();
  
  /* getters */
  double getLinha ();
  double getColuna ();
  
  // Leitura de uma Matriz
  void read ();
  
protected:
  // tamanho do eixo i de uma Matriz[i][j]
  unsigned int linha;
  // tamanho do eixo j de uma Matriz[i][j]
  unsigned int coluna;
  // valores da Matriz[i][j]
  double **matriz;
  
  /* setters */
  void setLinha (unsigned int linha);
  void setColuna (unsigned int coluna);
};