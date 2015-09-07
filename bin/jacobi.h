#include "matriz.h"

class jacobi {
public:
    /* construtores */
    jacobi(matriz *matrizA, matriz *matrizB);
    /* destrutores */
    virtual ~jacobi();
    
    /* getters */
    matriz* getMatrizA ();
    matriz* getMatrizB ();
    unsigned int getSize ();
    
    /* Funcao que aplica a formula de Jacobi-Richardson
     * e imprime a comparacao final entre
     * os valores de teste e o valores finais da matriz
     * Parametros: 
     * 		J_ROW_TEST - linha base da comparacao
     * 		J_ERROR - erro minimo para criterio de parada
     * 		J_ITE_MAX - numero maximo de iteracoes para criterio de parada
     */
    void jacobiRichardson (unsigned int J_ROW_TEST, double J_ERROR, unsigned int J_ITE_MAX);
    
    /* Funcao que calcula o valor da proxima iteracao 
     * da MatrizXk+1 na linha desejada
     * Parametros: 
     * 		index - linha processada
     * 		Xk2 - MatrizXk+1
     * 		Xk - MatrizXk
     */
    void processamento (unsigned int index, double *Xk2, double *Xk);
    
protected:
    /* setters */
    void setMatrizA (matriz *matrizA);
    void setMatrizB (matriz *matrizB);
    void setSize (unsigned int size);
    
    /* Funcao que calcula todos os valores
     * da proxima iteracao da MatrizXk+1
     * Parametros: 
     * 		Xk2 - MatrizXk+1
     * 		Xk - MatrizXk
     */
    virtual void iterar (double *Xk2, double *Xk);
    
    // matriz processada
    matriz *matrizA;
    // vetor
    matriz *matrizB;
    // tamanho das duas matrizes
    unsigned int size;
};

class jacobiThread : public jacobi {
public:
    /* construtores */
    jacobiThread(matriz *matrizA, matriz *matrizB);
    /* destrutores */
    ~jacobiThread();
    
protected:
    /* Funcao que cria cada thread e pede a iteracao
     * da MatrizXk+1
     * Parametros: 
     * 		Xk2 - MatrizXk+1
     * 		Xk - MatrizXk
     */
    void iterar (double *Xk2, double *Xk);
    
    // numero de threads
    int n_threads;
    // tamanho minimo de processamento das threads
    int min_size_threads;
    // threads
    pthread_t *Threads;
};
