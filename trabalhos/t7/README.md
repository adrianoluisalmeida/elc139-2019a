
# T7: Avaliação de desempenho de programas MPI

Para este trabalho, você vai precisar instalar o SimGrid, que é uma ferramenta científica utilizada para a simulação e o estudo de ambientes distribuidos. Para a instalação do SimGrid em distribuições Linux baseadas em Debian, basta a execução do comando abaixo:

```
sudo apt-get update && sudo apt-get install simgrid
```

**Alternativamente**, você pode baixar o codigo fonte do SimGrid compilá-lo e instalá-lo seguindo os passos seguintes:

1. Instale as dependências necessárias:
```
sudo apt-get install g++ libboost-all-dev cmake
```

2. Baixe o [código fonte](http://gforge.inria.fr/frs/download.php/file/37955/SimGrid-3.22.tar.gz);

3. Descompacte o arquivo baixado:
```
tar -xvf SimGrid-x.x.x.tar.gz
```

4. Acesse o diretório do arquivo descompactado:
```
cd SimGrid-x.x.x
```

5. Gere os Makefiles:
```
cmake -DCMAKE_INSTALL_PREFIX=/usr/local -Denable_smpi=on -Denable_documentation=off
```

6. Compile:
```
make
```

7. Instale:
```
make install
```

## Aquecimento

Para começar, exercite compilação e execução de programas MPI utilizando o SMPI:

1. Baixe o arquivo [hello_mpi.c](hello_mpi.c).

2. Compile o programa:
```
smpicc -o hello_mpi hello_mpi.c
```

3. Como a proposta do SMPI é simular um ambiente distribuído, para a execução do programa prossiga da seguinte forma e observe a saída:
  
```
smpirun -np 16 -hostfile cluster_hostfile.txt -platform cluster_crossbar.xml ./hello_mpi --cfg=smpi/host-speed:10000000
```

+ A opção "-np 16", assim como no MPI normal, especifica o número de processos MPI a serem usados.
+ A opção -hostfile [cluster_hostfile.txt](cluster_hostfile.txt), assim como no MPI normal, especifica o arquivo de hosts.
+ A opção -platform [cluster_crossbar.xml](cluster_crossbar.xml) especifica a configuração do ambiente a ser simulada.
+ O penúltimo parâmetro "./hello_mpi", refere-se ao nome do executável e os argumentos da linha de comando (nesse caso, não há nenhum argumento para o executável).
+ Por último, é especificado o poder de processamento (em flops) da máquina host do simulador.

## Parte 1
É fornecido o arquivo [sr_bcast.c](sr_bcast.c) com a função "sr_bcast", que implementa o MPI_Bcast usando MPI_Send e MPI_Recv. Utilizando o simulador, você deverá:

+ Implementar um programa para comparar a implementação do broadcast com send e receive (fornecida) com a função MPI_Bcast nativa do MPI;
+ Coletar e comparar (em forma de gráfico) os tempos de execução de cada uma das implementações do broadcast, variando o número de processos;
+ Lembre-se de realizar várias execuções para melhor confiança dos resultados (no mínimo 10 execuções com cada configuração).
+ As execuções devem ser realizadas no simulador SMPI utilizando os arquivos [cluster_crossbar.xml](cluster_crossbar.xml) e [cluster_hostfile.txt](cluster_hostfile.txt).
  
**Atenção:** Não esqueça de incluir dentre os parâmetros do smpirun as flags: "--cfg=smpi/coll_selector:ompi" e "--cfg=smpi/host-speed:10000000"

## Parte 2
É fornecido o arquivo [avg.c](avg.c) como um exemplo de programa que utiliza as funções MPI vistas até o momento. Basicamente esse programa realiza o cálculo da média dos valores de um vetor de forma distribuída e funciona da seguinte forma:

1. É gerado um vetor de tamanho n (passado por argumento para a função main) no processo raiz (rank 0);
2. Os valores das posições do vetor no processo raiz são distribuídos para os demais processos de forma que todos eles uma quantidade igual de valores;
3. Cada processo calcula a média do seu subconjunto de valores;
4. Por fim as médias calculadas em cada processo são reunidas novamente no processo raiz, o qual realiza a média desses valores recebidos, obtendo a média final.

O funcionamento desse algoritmo é melhor ilustrado na [figura](diagrama.png).

Utilizando o simulador SMPI com os arquivos [cluster_crossbar.xml](cluster_crossbar.xml) e [cluster_hostfile.txt](cluster_hostfile.txt) como parâmetros, realize execuções variando as configurações que descrevem as características do ambiente distribuido simulado. 

+ Realize execuções variando os valores de "bw" (largura de banda) e "lat" (latência) no arquivo [cluster_crossbar.xml](cluster_crossbar.xml);
+ Realize execuções variando o tamanho do vetor (passado por argumento para o executável);
+ Varie o tamanho do vetor apenas entre 100 e 3000 posições, caso contrário poderão haver incoerências na execução com o simulador, ou até mesmo um erro; 
+ Compare os tempos de execução (em forma de gráfico).

**Atenção:** Não esqueça de incluir dentre os parâmetros do smpirun as flags: "--cfg=smpi/coll_selector:ompi" e "--cfg=smpi/host-speed:10000000"


## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t7`, crie um documento `Entrega.md`, contendo:
 - Identificação da disciplina e do aluno;
 - Respostas para as partes 1 e 2, incluindo links para os códigos desenvolvidos;
 - Referências.


## Apresentação

As respostas do trabalho serão apresentadas e discutidas em aula no dia 30/05.


## Material de apoio


- [MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)  
- [A Comprehensive MPI Tutorial Resource](http://mpitutorial.com/)  
- [Tutorial MPI](https://computing.llnl.gov/tutorials/mpi/)  
- [SMPI CourseWare](https://simgrid.github.io/SMPI_CourseWare/)
- [SMPI - Describing the virtual platform](http://simgrid.gforge.inria.fr/simgrid/3.20/doc/platform.html)
