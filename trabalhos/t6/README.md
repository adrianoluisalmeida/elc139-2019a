[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > Trabalhos

# T6: Comunicação coletiva em MPI


É fornecido um arquivo [matrix_mult_sr.c](matrix_mult_sr.c), que contém um código paralelizado usando send/receive. O mesmo gera duas matrizes A e B, depois multiplica as mesmas e gera a matriz C. No final são mostradas todas as matrizes.

## Parte 1

No código fornecido, são feitas várias chamadas de send/recv que podem ser trocadas por outras funções. Você deve descobrir quais são essas funções, fazer a alteração e testar se o resultado é o mesmo. (O programa gera sempre as mesmas matrizes, então o resultado deve ser sempre o mesmo).

## Parte 2

Leia o artigo [Send-receive considered harmful: Myths and realities of message passing](https://dl.acm.org/citation.cfm?id=963780) e escreva um resumo crítico relacionando os argumentos do autor com sua própria experiência de programação com MPI. Obs: artigo acessível pela rede da UFSM (caso esteja em outra rede, use proxy ou siga instruções [aqui](http://coral.ufsm.br/informatica/index.php/home/noticias/65-tutorial-para-acesso-ao-portal-de-periodicos-da-capes-ufsm)).

## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t8`, crie um documento `Entrega.md`, contendo:
 - Identificação da disciplina e do aluno;
 - Parte 1: explicação sobre as alterações e link para o código desenvolvido;
 - Parte 2: resumo crítico;
 - Referências.


## Apresentação

Os códigos-fonte deste trabalho deverão ser apresentado em aula no dia 14/06.


## Material de apoio


- [MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)  
- [A Comprehensive MPI Tutorial Resource](http://mpitutorial.com/)  
- [Exemplos de comunicação](exemplos/)


## Créditos

Parte deste trabalho foi formulada pelo mestrando Rudieri Colbek, em suas atividades de docência orientada.


