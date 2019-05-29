// Adaptado de www.mpitutorial.com
// Exemplo de implementação do MPI_Bcast usando MPI_Send e MPI_Recv

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

long wtime();

int main(int argc, char** argv) {

  int myrank;    // "rank" do processo
  int p;         // numero de processos
  int root;      // rank do processo root
  long start_time, end_time; //time de execução
  int data;     // dado a ser enviado
  
  start_time = wtime(); //inicia o contador sec

  // MPI_Init deve ser invocado antes de qualquer outra chamada MPI
  MPI_Init(&argc, &argv);
  // Descobre o "rank" do processo
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  // Descobre o numero de processos
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  root = 0;     // define o rank do root
  MPI_Bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);
  printf("Processo %d recebendo dado %d do processo root\n", myrank, data);

  //Bloqueia o chamador até que todos os processos no comunicador o tenham chamado; ou seja, 
  //a chamada retorna em qualquer processo somente depois que todos os membros do comunicador 
  //tiverem entrado na chamada.
  MPI_Barrier(MPI_COMM_WORLD);

  if (myrank == root) {    
    data = 100;  // atribui um valor para ser enviado
    end_time = wtime();
    printf("%ld\n", (end_time - start_time) * 1000000);
  } 

  MPI_Finalize();  

  return 0;
}

// Tempo em microssegundos 
long wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}