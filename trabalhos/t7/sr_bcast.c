// Adaptado de www.mpitutorial.com
// Exemplo de implementação do MPI_Bcast usando MPI_Send e MPI_Recv

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void sr_bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator) {
  
  int myrank;     // "rank" do processo
  int p;          // numero de processos

  MPI_Comm_rank(communicator, &myrank);
  MPI_Comm_size(communicator, &p);

  if (myrank == root) {
    // Se for o rank root, enviar o dado para cada um dos demais
    int i;
    for (i = 0; i < p; i++) {
      if (i != myrank) {
        MPI_Send(data, count, datatype, i, 0, communicator);
      }
    }
  } else {
    // Se não for o rank root, recebe o dade envidado pelo rank root
    MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
  }
}

int main(int argc, char** argv) {

  int myrank;    // "rank" do processo
  int p;         // numero de processos
  int root;      // rank do processo root

  // MPI_Init deve ser invocado antes de qualquer outra chamada MPI
  MPI_Init(&argc, &argv);
  // Descobre o "rank" do processo
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  // Descobre o numero de processos
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  int data;     // dado a ser enviado
  root = 0;     // define o rank do root

  if (myrank == root) {
    data = 100;  // atribui um valor para ser enviado
    printf("Processo %d (root) realizando broadcast do dado %d\n", root, data);
    sr_bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);
  } else {
    sr_bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);
    printf("Processo %d recebendo dado %d do processo root\n", myrank, data);
  }

  MPI_Finalize();
  return 0;
}