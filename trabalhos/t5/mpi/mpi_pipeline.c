/*
 *  Implementação de troca de mensagens pipeline com MPI
 *  alalmeida@inf.ufsm.br
 */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int rank, p, msg;

    MPI_Init(&argc, &argv); //Inicializa o ambiente de execução do MPI. Esta função deve ser chamada em todo programa MPI
    MPI_Comm_size(MPI_COMM_WORLD, &p); //Retorna o número total de processos MPI no comunicador especificado, como MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //Retorna a classificação do processo MPI de chamada dentro do comunicador especificado.

    if (rank == 0) {
        printf("inicio do processo "); //informa o inicio da troca de msgs
        msg = 0;
        printf("p[%d] -> p[%d]\n", rank, rank+1);
        MPI_Send(&msg, 1, MPI_INT, (rank+1), 0, MPI_COMM_WORLD); //envia mensagem para rank+1 = 1
    } else if ( rank == (p - 1) ) {
        MPI_Recv(&msg, 1, MPI_INT, (rank-1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  //recebe mensagem do rank - 1 = 0
        printf("p[%d] <- p[%d]\n", rank, rank-1);
        printf("[FIM] Processo %d obteve o resultado %d\n\n", rank, msg);
    } else {
        msg++;
        printf("p[%d] -> p[%d]\n", rank, rank+1);
        MPI_Send(&msg, 1, MPI_INT, (rank+1), 0, MPI_COMM_WORLD); // envia mensagem para o rank + 1 = 1
    }

    MPI_Finalize(); // Finaliza MPI - Encerra o ambiente de execução do MPI. Esta função deve ser a última rotina MPI chamada em todos os programas MPI
    return EXIT_SUCCESS;

}
