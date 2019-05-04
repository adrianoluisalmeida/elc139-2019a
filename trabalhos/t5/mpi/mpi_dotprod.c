/*
 *  Exemplo de programa para calculo de produto escalar em paralelo, usando MPI.
 *  andrea@inf.ufsm.br
 *  mpi -> alalmeida@inf.ufsm.br
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mpi.h"

typedef struct {
    double *a;
    double *b;
    int wsize;
    int repeat; 
} dotdata_t;

dotdata_t dotdata;

void check_params(int argc, char **argv, int *wsize, int *repeat);
double product_mpi(int wsize, int repeat);
void create_arrays(int wsize, int repeat);
void fill(double *a, int size, double value);
long wtime();
void show_info(double total_dotprod, int wsize, int p, long start_time, long end_time, double start_time_mpi, double end_time_mpi);
void check_result(double total_dotprod, int wsize, int qtd_proc);


int main(int argc, char **argv) {
    int myrank, p, source, dest = 0, tag = 0, wsize, repeat;         // "rank" do processo (0 a P-1)
    
    double result;      // a mensagem (resultado do calculo)
    MPI_Status status;  // "status" de uma operação efetuada
    
    long start_time, end_time;
    double start_time_mpi, end_time_mpi;

    // Criacao e controle da estrutura master-slave
    MPI_Init(&argc, &argv); //Inicializa o ambiente de execução do MPI. Esta função deve ser chamada em todo programa MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank); //Retorna a classificação do processo MPI de chamada dentro do comunicador especificado.
    MPI_Comm_size(MPI_COMM_WORLD, &p); //Retorna o número total de processos MPI no comunicador especificado, como MPI_COMM_WORLD
    
    check_params(argc, argv, &wsize, &repeat); //testa os parâmetros de entrada
    start_time = wtime(); //inicia o contador sec
    start_time_mpi = MPI_Wtime(); //Retorna um tempo de relógio de parede decorrido em segundos (precisão dupla) no processador de chamada.
    
    if (myrank != 0) { 	/* SLAVES */
        result = product_mpi(wsize, repeat);
        //Operação básica de envio de bloqueio. Rotina retorna somente depois que o buffer de aplicativo na tarefa de envio está livre para reutilização. 
        MPI_Send(&result, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD); 
    } else {            /* MASTER */
        double total_dotprod = product_mpi(wsize, repeat); // 'master' tambem realiza o calculo
        for(source = 1; source < p; source++) {
            //Receba uma mensagem e bloqueie até que os dados solicitados estejam disponíveis no buffer do aplicativo na tarefa de recebimento.
            MPI_Recv(&result, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status); 
            total_dotprod += result;
        }
        end_time = wtime();
        end_time_mpi = MPI_Wtime();
        show_info(total_dotprod, wsize, p, start_time, end_time, start_time_mpi, end_time_mpi);
    }
    
    MPI_Finalize(); // Encerra o ambiente de execução do MPI. Esta função deve ser a última rotina MPI chamada em todos os programas MPI -

    return EXIT_SUCCESS;
}

// Valida argumentos do programa
void check_params(int argc, char **argv, int *wsize, int *repeat) {
    if ( (argc != 3) ) {
        fprintf(stderr,"Usage: %s <worksize> <repetitions>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    *wsize = atoi(argv[1]);
    *repeat = atoi(argv[2]);
    if ( (*wsize <= 0) || (*repeat <= 0) ) {
        fprintf(stderr, "%s: worksize and repetitions should be > 0.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

// Função para  o cálculo do produto escalar 
double product_mpi(int wsize, int repeat) {
    create_arrays(wsize, repeat);
    double *a = dotdata.a;
    double *b = dotdata.b;  
    double mysum;
    for (int k = 0; k < repeat; k++) {
    	mysum = 0.0;
    	for (int i = 0; i < wsize; i++) {
            mysum += (a[i] * b[i]);
    	}
    }
    free(dotdata.a);
    free(dotdata.b);
    return mysum; 
}

// Criação dos vetores
// Diferente do modelo usando o threads, no mpi é feito uma cópias das váriaveis em cada processo, nesse conceito não é necessário dividir intervalos.
void create_arrays(int wsize, int repeat) {
    dotdata.a = (double*) malloc(wsize * sizeof(double));
    fill(dotdata.a, wsize, 0.01);
    dotdata.b = (double*) malloc(wsize * sizeof(double));
    fill(dotdata.b, wsize, 1.0);
    dotdata.wsize = wsize;
    dotdata.repeat = repeat;
}

// Preenchimento do vetor
void fill(double *a, int size, double value) {  
    for (int i = 0; i < size; i++)
        a[i] = value;
}

// Tempo em microssegundos 
long wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

// Mostra resultado da execução
void show_info(double total_dotprod, int wsize, int p, long start_time, long end_time, double start_time_mpi, double end_time_mpi) {
    printf("dot product: %f\n", total_dotprod);
    printf("number of processes: %d ", p);
    printf("wall time MPI: %f usec\n", (end_time_mpi - start_time_mpi) * 1000000),
    fflush(stdout);
}

