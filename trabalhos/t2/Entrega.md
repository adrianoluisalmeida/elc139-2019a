[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a)

# T2: Programação Paralela Multithread

Disciplina: elc139 - Programação Paralela <br/>
Aluno: Adriano Luís de Almeida

## Sumário

## Parte I: Pthreads
### Questão 1
- Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).


- **Particionamento**
O programa pthreads_dotprod que foi análise utilizou de um particionamento estrutural que utiliza dados de entrada, como pode ser visualizado no trecho abaixo:

``` c
long offset = (long) arg;
double *a = dotdata.a;
double *b = dotdata.b;    
int wsize = dotdata.wsize;
int start = offset*wsize;
int end = start + wsize;
```

- **Comunicação entre as threads**
A comunicação é feita e necessária para coordenar a execução das tarefas. No código foi feito a utilização de semáforos para garantir um bom funcionamento e manter os dados corretamente. O trecho abaixo demonstra onde foi feita a comunicação:
``` c
pthread_mutex_lock (&mutexsum); //LINHA EXTRA 1
dotdata.c += mysum;
pthread_mutex_unlock (&mutexsum); //LINHA EXTRA 2
```
- **Aglomeração**

A etapa de aglomeração é composta por somos parciais que acontecem nas threads e são armazenadas na variável mysum e definidas pelo offset que definem o início/fim do cálculo de cada thread.
``` c
for (k = 0; k < dotdata.repeat; k++) {
    mysum = 0.0;
	for (i = start; i < end; i++)  {
	    mysum += (a[i] * b[i]);
	}
}
``` 

- **Mapeamento**

O mapeamento acontece no momento da definição das threads que o próprio sistema operacional tem o trabalho de mapear, pois não são definidos cores na instância das threads. Em relação a carga pode ser feita de forma estática ou dinâmica, no código análise apenas a definição foi feita. 
``` c
pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
``` 

### Questão 2
- Considerando o tempo (em microssegundos) mostrado na saída do programa, qual foi a aceleração (speedup) com o uso de threads?

De forma clara podemos dizer que caiu pela metade, sendo no primeiro caso (1 Thread) 6176565 usec e (2 Thread(s) ) 3380745 usec, mais precisamente 54,73% de aceleração. Podemos citar como uma explicação o efeito da memória cache. 

### Questão 3
- A aceleração se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão, você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

|                    |               |                |                  |                  | 
|--------------------|---------------|----------------|------------------|------------------| 
| Pthread - 1 Thread |               |                |                  |                  | 
|                    | Repetições    | Repetições     | Repetições       | Repetições       | 
| worksizetotal      | 10 repetições | 100 repetições | 1000 repetições  | 2000 repetições  | 
| 1000               | 1029          | 2867           | 7925             | 30458            | 
| 10000              | 2576          | 5263           | 35668            | 65186            | 
| 100000             | 4029          | 41644          | 310532           | 631185           | 
|                    |               |                |                  |                  | 
|                    |               |                |                  |                  | 
| Pthread - 2 Thread |               |                |                  |                  | 
| worksizetotal      | 10 repetições | 100 repetições | 1.000 repetições | 2.000 repetições | 
| 1000               | 601           | 2745           | 9953             | 16236            | 
| 10000              | 3729          | 24927          | 62200            | 96562            | 
| 100000             | 8307          | 58282          | 332088           | 633128           | 
|                    |               |                |                  |                  | 
|                    |               |                |                  |                  | 
| Pthread - 4 Thread |               |                |                  |                  | 
| worksizetotal      | 10 repetições | 100 repetições | 1.000 repetições | 2.000 repetições | 
| 1000               | 1054          | 4190           | 9795             | 16299            | 
| 10000              | 4035          | 12794          | 50442            | 98935            | 
| 100000             | 13478         | 66287          | 512976           | 1026511          | 




### Questão 4
- Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.



### Questão 5
- Explique as diferenças entre pthreads_dotprod.c e pthreads_dotprod2.c. Com as linhas removidas, o programa está correto?

A diferença do programa pthreads_dotprod.c em relação ao pthreads_dotprod2.c, é que o primeiro realiza um bloqueio na variável mutexsum até a soma seja realizada e ao final desbloqueia o processo.
``` c
pthread_mutex_lock (&mutexsum); //LINHA EXTRA 1

//bloqueia o processo até que seja realizado o somatório 
dotdata.c += mysum;

//após a realização é desbloqueado 
pthread_mutex_unlock (&mutexsum); //LINHA EXTRA 2
```

As linhas removidas são o controle por semáforo da variável responsável pela soma. O programa executa o resultado correto, pois não existe uma dependência do resultado, que caso houvesse um erro provavelmente poderia acontecer. 


## Parte II: OpenMP

### Questão 2

|                   |               |                |                  |                  | 
|-------------------|---------------|----------------|------------------|------------------| 
| Openmp - 1 Thread |               |                |                  |                  | 
| worksizetotal     | 10 repetições | 100 repetições | 1.000 repetições | 2.000 repetições | 
| 1000              | 176           | 1813           | 6072             | 9928             | 
| 10000             | 1404          | 16787          | 61228            | 69508            | 
| 100000            | 298550        | 32943          | 323363           | 614065           | 
|                   |               |                |                  |                  | 
|                   |               |                |                  |                  | 
| Openmp - 2 Thread |               |                |                  |                  | 
| worksizetotal     | 10 repetições | 100 repetições | 1.000 repetições | 2.000 repetições | 
| 1000              | 52            | 477            | 7308             | 6005             | 
| 10000             | 1308          | 6482           | 20083            | 56159            | 
| 100000            | 2336          | 16885          | 179125           | 299036           | 
|                   |               |                |                  |                  | 
|                   |               |                |                  |                  | 
| Openmp - 4 Thread |               |                |                  |                  | 
| worksizetotal     | 10 repetições | 100 repetições | 1.000 repetições | 2.000 repetições | 
| 1000              | 457           | 1156           | 9282             | 17914            | 
| 10000             | 1768          | 3667           | 21883            | 31576            | 
| 100000            | 4007          | 20028          | 124338           | 282788           | 
