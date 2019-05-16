# T6: Comunicação coletiva em MPI

Disciplina: elc139 - Programação Paralela <br/>
Aluno: Adriano Luís de Almeida

## Parte 1

- No código fornecido, são feitas várias chamadas de send/recv que podem ser trocadas por outras funções. Você deve descobrir quais são essas funções, fazer a alteração e testar se o resultado é o mesmo. (O programa gera sempre as mesmas matrizes, então o resultado deve ser sempre o mesmo).

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


## Parte 2

- Leia o artigo Send-receive considered harmful: Myths and realities of message passing e escreva um resumo crítico relacionando os argumentos do autor com sua própria experiência de programação com MPI. Obs: artigo acessível pela rede da UFSM (caso esteja em outra rede, use proxy ou siga instruções aqui).


Send-Receive Considered Harmful: Myths and Realities of Message Passing

Desenvolvimento de programas paralelos continua sendo um grande desafio a muitos anos. Muitas implementações surgiram, mas poucas conseguiram popularidade, o principal e mais conhecido é o OpenMP. O mérito do OpenMP é devido a sua padronização, integração e construções paralelas testadas na prática.

Por volta dos anos 60 com a crise e comprovação de falhas no cenário sequencial, surgiram novas sugestões de implementações, as chamadas estruturas sem qualquer declarações goto. 

Entre as principais implementações ao longo dos anos são usados as primitivas send-recieve. O artigo analísado propoem uma nova solução, conhecida como Operações Coletivas. Entre os principais problemas apontados por programas que usam a premissa de send-recieve, está a complexidade de entender e depurar o programa. Ainda no caso do MPI existem diversas formas de combinações de envio e recebimento, o que torna o programa ainda menos compreensivo devido a sua alta complexidade. 

Algoritmos recentes para comunicação coletiva tem características específicas, de rede interprocessora, que podem ser consideradas durante a fase de compilação da biblioteca de comunicação. Há fortes evidências de que o envio-recebimento não oferece vantagens de desempenho em relação às operações coletivas.

Operações coletivas contribuem para o objetivo de prever características do programa durante o processo de desenho do programação,sem a necessidade de execução prévia. O uso de envio e recebimento faz com que o programa seja muito menos previsível. Além disso,a previsibilidade de operações coletivas simplica toda a etapa de modelagem da aplicação.

Existem vários tipos e modos para realizar o envio-recebimento no padrão no padrão MPI, porém, são primitivos e acabam causando uma bagunça em programas paralelos. Por esse motivo o artigo apresenta comparações que buscam provar que operações coletivas possuem um potencial maior para os problemas em questão, além de permitir a concepção de estruaturas paralelas bem estruturadas e eficientes.


## Referências

[MPI_Scatter](https://www.mpich.org/static/docs/v3.1/www3/MPI_Scatter.html)   
[MPI_Bcast](https://www.mpich.org/static/docs/v3.1/www3/MPI_Bcast.html)   
[MPI_Gather](https://www.mpich.org/static/docs/v3.1/www3/MPI_Gather.html)   
[Examples using MPI_SCATTER, MPI_SCATTER](https://www.mpi-forum.org/docs/mpi-1.1/mpi-11-html/node72.html)    
[MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)     
[A Comprehensive MPI Tutorial Resource](http://mpitutorial.com/)      


