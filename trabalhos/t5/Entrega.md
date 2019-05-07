[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a)

# T5: Primeiros passos com MPI

Disciplina: elc139 - Programação Paralela <br/>
Aluno: Adriano Luís de Almeida

# Aquecimento

Durante os processos de testes obtive algumas dificuldades para instalar o MPI, usando DEBIAN 9 STRETCH. Com muito esforço :P consegui instalar finalmente. Após a conclusão da instalação e testes não consegui executar o comando dado como exemplo:

```sh
mpiexec -np 5 hello_mpi
```

a execução informava que o número de slots disponíveis para execução não era suportado. Para isso foi necessário informar um parâmetro extra, como abaixo:

```sh
mpiexec --oversubscribe -np 5 hello_mpi
```

Obs.: A cláusula *--oversubscribe* foi usada nas demais execuções.

# Parte 1
- 1.0 Implemente uma versão em MPI do programa do trabalho t2, que calcula repetidas vezes o produto escalar entre 2 vetores. Os argumentos do programa devem ser: o número de elementos para cada processo e o número de repetições.

A implementação do código que realiza o produto escalar foi nomeado com [mpi_dotprod.c](mpi/mpi_dotprod.c).
O código em questão está documentado em cada uma das funções do MPI. Pode ser destacado que o MPI diferente da implmentação usando threads, não necessita a separação em intervalos dos cálculos realizados, visto que cada divisão é feita usando processos que criam cópias das váriais úteis. Além disso o Produto escalar é dividio em MASTER e SLAVE. Sendo o MASTER o processo (0) e que recebe uma mensagem (MPI_Recv) e bloqueia até que os dados solicitados estejam disponíveis no buffer do aplicativo na tarefa de recebimento. Os slaves possuem uma operação básica de envio de bloqueio (MPI_Send). Rotina retorna somente depois que o buffer de aplicativo na tarefa de envio está livre para reutilização. 

- 1.1 Avalie o desempenho do programa conforme as instruções do trabalho t2, mas variando o número de processos (-np) ao invés de threads.

Para os testes foram realizados 30 execuções do código [mpi_dotprod.c](mpi/mpi_dotprod.c) com auxilio do [calc_time.sh] (mpi/calc_time.sh) que calcula a média das execuções de acordo com a entrada:
```sh
 ./calc_time.sh <np> <workizeTotal> <repeticoes>.
```
O calc_time além de armazenar a média das execuções, utiliza a mesma pra calcular o speedup, levando em consideração as seguintes regras:

S(p) = T(s) / T(p)

Onde p equivale a quantidade de processadores, t(s) equivale a execução com apenas 1 processo e t(p) execução paralela, nesse caso com os processos.

Além disso o worksize foi recalculado, usando a seguinte regra:

worksize(processo(i)) = worksizetotal ÷ np

nesse caso uma execução com worksizeTotal igual a 100.000 e com 2 processo e 100 repetições equivale ao seguinte:

```sh
./calc_time.sh 2 50.000 100.
```

## Resultados 

## Res.(1) - *Unidade de Tempo = usec*

### 2 processos

| worksizetotal                                | 100 repetições | 1.000 repetições | 2.000 repetições |
|----------------------------------------------|----------------|------------------|------------------|
| 10.000                                       | 1603.33        | 20808.17         | 40452.99         |
| 100.000                                      | 22177.68       | 171171.90        | 327442.30        |
| 1.000.000                                    | 172733.65      | 1663422.64       | 3402707.69       |

### 4 processos

| worksizetotal                                | 100 repetições | 1.000 repetições | 2.000 repetições |
|----------------------------------------------|----------------|------------------|------------------|
| 10.000                                       | 1378.35        | 15418.62         | 28581.61         |
| 100.000                                      | 16441.98       | 126059.85        | 270086.68        |
| 1.000.000                                    | 132655.47      | 1198956.365      | 2639908.53       |

### 8 processos

| worksizetotal                                | 100 repetições | 1.000 repetições | 2.000 repetições |
|----------------------------------------------|----------------|------------------|------------------|
| 10.000                                       | 2447.49        | 14250.80         | 28779.44         |
| 100.000                                      | 16850.28       | 129914.42        | 235336.78        |
| 1.000.000                                    | 130110.99      | 1167707.65       | 2545583.90       |

## Res.(2) - *Speedup*

### 2 processos

| worksizetotal                                | 100 repetições | 1.000 repetições | 2.000 repetições |
|----------------------------------------------|----------------|------------------|------------------|
| 10.000                                       | 1.873          | 1.410            | 1.448            |
| 100.000                                      | 1.368          | 1.778            | 2.303            |
| 1.000.000                                    | 1.809          | 2.054            | 2.034            |

### 4 processos

| worksizetotal                                | 100 repetições | 1.000 repetições | 2.000 repetições |
|----------------------------------------------|----------------|------------------|------------------|
| 10.000                                       | 1.873          | 1.410            | 1.448            |
| 100.000                                      | 1.368          | 1.778            | 2.303            |
| 1.000.000                                    | 1.809          | 2.054            | 2.034            |

### 8 processos

| worksizetotal                                | 100 repetições | 1.000 repetições | 2.000 repetições |
|----------------------------------------------|----------------|------------------|------------------|
| 10.000                                       | 1.252          | 2.068            | 2.715            |
| 100.000                                      | 1.829          | 2.331            | 2.563            |
| 1.000.000                                    | 2.448          | 2.794            | 2.534            |

# Parte 2
- Implemente um programa MPI que transporte uma mensagem em um pipeline formado por processos de 0 a NP-1 (processo 0 envia para 1, processo 1 envia para 2, ..., processo NP-1 mostra o resultado). A mensagem é um número inteiro que é incrementado antes de ser passado adiante.

A implementação do código referente a parte dois foi nomeado com [mpi_pipeline](mpi/mpi_pipeline.c);
Ó código em questão está documentado.
Podemos considerar que foi utilizado as funções básicas da documentação do open MPI como MPI_Init, MPI_Comm_size (com comunicador MPI_COMM_WORLD) e MPI_Comm_rank. Além dos responsáveis pelas trocas de mensagens entre os processos MPI_Send e MPI_Recv. Para determinar a origem e destino das mensagens foi usado o rank, como rank 0, rank+1 e rank-1; 

# Parte 3
- O programa mpi_errado1.c deveria realizar a troca de mensagens entre 2 processos, mas ele não funciona como esperado. Identifique o erro e corrija-o.

A correção do programa mpi foi nomeado com [mpi_certo1.c](mpi/mpi_certo1.c).
O erro estava pesente nos seguintes trechos de envio e recebimento de mensagens:

```c
    tag = 0; //com erro estava usando -> tag = rank
    rc = MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
```

```c
    tag = 0; //com erro -> tag = rank
    rc = MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
```

- O programa mpi_errado2.c deveria realizar a troca de mensagens entre 2 processos, mas também não funciona como esperado. Identifique o erro e corrija-o

A correção do programa mpi foi nomeado com [mpi_certo2.c](mpi/mpi_certo2.c).
O erro é que o MPI_Finalize() não estava sendo utilizado, ficando assim: 

```c
    ...
      rc = MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
      printf("Recebi mensagem do processo %d...\n", source);
      rc = MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
      printf("Enviei mensagem para processo %d...\n", dest);
   }

   MPI_Finalize(); 
```

Correção -> MPI_Finalize() Encerra o ambiente de execução do MPI. Esta função deve ser a última rotina MPI chamada em todos os programas MPI

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

# Referências

- [Tutorial MPI](https://computing.llnl.gov/tutorials/mpi/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre MPI.

- [MPI Tutorial](http://mpitutorial.com/tutorials/)

- [MPI Tutorial - MPI Send and Receive](http://mpitutorial.com/tutorials/mpi-send-and-receive/)

- [An introduction to the Message Passing Interface (MPI)](http://condor.cc.ku.edu/~grobe/docs/intro-MPI-C.shtml)

- [Message Passing Interface - wikipedia](https://en.wikipedia.org/wiki/Message_Passing_Interface)