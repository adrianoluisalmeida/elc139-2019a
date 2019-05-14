# T6: Comunicação coletiva em MPI

Disciplina: elc139 - Programação Paralela <br/>
Aluno: Adriano Luís de Almeida

## Parte 1
------

**MPI_Bcast(), MPI_Scatter() e MPI_Gather()** são utilizados para o processo de comunicação e multiplicação. Ele são usado para substituir os send(s)/recieve(s) da aplicação. 

*MPI_Bcast* é usado para a difusão da matriz B, usando broadcast, que é utilizado por todos os processos. Diferente de Send/Recieve, *MPI_Bcast* transmite uma mensagem do processo com classificação "raiz" para todos os outros processos do comunicador.

```c
MPI_Bcast(B, SIZE*SIZE, MPI_INT, 0 ,MPI_COMM_WORLD);
```

*MPI_Scatter* faz a divisão da matriz A pelos processos e realizado o calculo em cada processo. *MPI_Scatter* Envia dados de um processo para todos os outros processos em um comunicador.


```c
MPI_Scatter(A[from], (to-from)*SIZE, MPI_INT, A[from], (to-from)*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
```
Neste caso o número de multiplicações equivalem ao número total de processo, neste caso o número de elementos a serem enviados é definido pelo número total de elementos ÷ número de processos do grupo.


*MPI_Gather* recebe o resultado do cálculo realizado nos processos e os reúne no processo principal (root).

```c
MPI_Gather (C[from], SIZE*SIZE/nproc, MPI_INT, C, SIZE*SIZE/nproc, MPI_INT, 0, MPI_COMM_WORLD);
```
Nesse caso o parâmetro referente ao número  de recebimentos por processo equivale ao total de elementos ÷ número de processos do grupo.

Implementação: [parte1.c](parte1.c)