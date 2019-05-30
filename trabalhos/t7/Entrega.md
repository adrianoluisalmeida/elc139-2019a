# T7: Avaliação de desempenho de programas MPI

Disciplina: elc139 - Programação Paralela <br/>
Aluno: Adriano Luís de Almeida

## Parte 1

**MPI_Bcast() e MPI_Barrier()** são utilizados para o processo de comunicação e multiplicação. Ele são usado para substituir os send(s)/recieve(s) da aplicação. 

*MPI_Bcast* é usado para a difusão, usando broadcast, que é utilizado por todos os processos. Diferente de Send/Recieve, *MPI_Bcast* transmite uma mensagem do processo com classificação "raiz" para todos os outros processos do comunicador.

```c
MPI_Bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);
```

*MPI_Barrier* Bloqueia o chamador até que todos os processos no comunicador o tenham chamado; ou seja, a chamada retorna em qualquer processo somente depois que todos os membros do comunicador  tiverem entrado na chamada.

```c
MPI_Barrier(MPI_COMM_WORLD);
```

Implementação: [sr_bcast_p1.c](sr_bcast_p1.c)

**Resultados**

| send/recieve |          | bcast |          |
|--------------|----------|-------|----------|
| np           | usec     | np    | usec     |
| 2            | 81782.63 | 2     | 57466.80 |
| 4            | 56153.03 | 4     | 58949.26 |
| 8            | 64451.93 | 8     | 56976.60 |
| 12           | 75911.46 | 12    | 63893.00 |
| 16           | 98332.34 | 16    | 70722.76 |

Os testes foram realizado com auxilio do [calc_time.sh](calc_time.sh) que realizou 30 testes e fez a média entre os testes para cada np (número de processos) informado na tabela.

## Parte 2

Testes variando largura de banda, latência e tam. vetor.

| np | largura banda | latência | usec     | vetor |
|----|---------------|----------|----------|-------|
| 16 | 125mbs        | 5us      | 0.046102 | 10000 |
| 16 | 125mbs        | 5us      | 0.089383 | 20000 |
| 16 | 125mbs        | 5us      | 0.133434 | 30000 |
| 16 | 125mbs        | 5us      | 0.180166 | 40000 |
| 16 | 250mbs        | 5us      | 0.048659 | 10000 |
| 16 | 250mbs        | 5us      | 0.090921 | 20000 |
| 16 | 250mbs        | 5us      | 0.148708 | 30000 |
| 16 | 250mbs        | 5us      | 0.179118 | 40000 |
| 16 | 250mbs        | 300us    | 0.089836 | 10000 |
| 16 | 250mbs        | 300us    | 0.091131 | 20000 |
| 16 | 250mbs        | 300us    | 0.129186 | 30000 |
| 16 | 250mbs        | 300us    | 0.193719 | 40000 |


# Máquina utilizada

| Meu computador  |
| --------------- |
| Dell 7460      |
| <img src="https://i.dell.com/sites/csimages/Videos_Images/en/69227bce-ff5c-4525-9fe2-64a4ae7cec5d.jpg" width="48">|

| Características |
| --------------------------------------------------------- |
| Memória Compartilhada |
| Número total de núcleos de processamento - 2C / 4 Threads  |
| Fabricante e modelo do(s) processador(es)  Intel Core i5 7200U   |
| Frequência do(s) processador(es) 2.5 GHz-3.1 GHz |
| Memória total   8GB             |



## Referências

[MPI_Bcast](https://www.mpich.org/static/docs/v3.1/www3/MPI_Bcast.html)   
[MPI_Barrier](https://www.mpich.org/static/docs/latest/www3/MPI_Barrier.html)   
[MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)     
[A Comprehensive MPI Tutorial Resource](http://mpitutorial.com/)