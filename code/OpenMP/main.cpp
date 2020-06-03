#include <iostream>
#include <omp.h>

#define DIM 1000       // ajuste a dimensão aqui...

// matrizes estáticas
float A [DIM] [DIM];
float B [DIM] [DIM];
float C [DIM] [DIM];

int
main(int argc, char *argv[])
{
    int i,j,k;

    std::cout << "Esta máquina tem " << omp_get_num_procs() 
               << " processadores." << std::endl;
   
    /* Atribuição de valores iniciais (0..5) às matrizes */
    srand(time(NULL));
    for(i=0; i < DIM; i++)
        for(j=0; j < DIM; j++) {
            A[i][j]= (float)rand() / (float)(RAND_MAX/ 5);
            B[i][j]= (float)rand() / (float)(RAND_MAX/ 5);
        }

    /* Multiplicação tradicional */
    for(i=0; i < DIM; i++)
        for(j=0; j < DIM; j++) {
            C[i][j] = 0;
            for(k=0; k < DIM; k++)
                C[i][j] = C[i][j] + A[i][k] * B[k][j]; 
        }

    return 0; 
}
