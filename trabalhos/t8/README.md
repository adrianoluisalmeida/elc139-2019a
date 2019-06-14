[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > Trabalhos

# T8: Geração de Imagem em Paralelo com CUDA


## Introdução


Neste trabalho, você vai paralelizar um programa que gera uma sequência de imagens representando uma ondulação, como no exemplo ao lado.

<img src="wave.gif" height="160px" align="right">

Você vai utilizar CUDA para programação paralela em GPU, no Google Colaboratory ou em alguma outra plataforma de execução à qual você tenha acesso e que disponha de uma GPU NVIDIA.


## Preparação

1. Baixe os arquivos da pasta [wave](wave), que contém o programa sequencial de referência para este trabalho. Este programa é uma adaptação de um código desenvolvido pelo professor Martin Burtscher, da Texas State University (EUA).

2. Compile o programa:
   ```
   g++ wave.cpp -o wave
   ```

3. Execute o programa para imagens de diferentes tamanhos e diferentes quantidades de frames:
   ```
   ./wave 512 32
   ./wave 512 64
   ./wave 1024 32
   ./wave 1024 64
   ```

4. O programa só grava imagens em arquivo para imagens pequenas (<= 256) e poucos frames (<= 100). É recomendável gerar algumas imagens quando estiver testando seu programa paralelo, para verificar se estão sendo geradas corretamente. Caso você deseje gerar uma animação, pode-se usar o seguinte comando do [ImageMagick](http://www.imagemagick.org):
   ```
   convert -delay 1x10 wave*.bmp wave.gif
   ```

5. Observe como os parâmetros de entrada influenciam no tempo de execução do programa.

6. Analise o código e identifique oportunidades de paralelismo, considerando que a arquitetura paralela de uma GPU permite que um grande número de threads trabalhe ao mesmo tempo.


## Parte 1

1. Implemente um programa nomeado `wavecuda1.cu`, em que cada frame seja computado em paralelo por uma thread diferente.

2. Analise o desempenho do programa, começando pela medição dos tempos de execução sequencial e paralela para pelo menos 4 diferentes entradas do programa, sendo: a) 1024 100, b) 1024 200 e outras 2 entradas à sua escolha. Compare os tempos obtidos. Use nvprof para analisar o perfil de execução em GPU. Explique seus resultados.


## Parte 2

1. Implemente um programa nomeado `wavecuda2.cu`, que aproveite melhor o paralelismo da GPU.

2. Analise o desempenho do segundo programa. 


## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t8`, crie um documento `Entrega.md`, contendo:
 - Identificação completa da disciplina e do aluno;
 - Links para os códigos desenvolvidos: `wavecuda1.cu` e `wavecuda2.cu` (**ATENÇÃO**: usar exatamente estes nomes, do contrário o trabalho **NÃO** será avaliado);
 - Link para **slides** explicando os programas implementados, descrevendo os experimentos realizados e discutindo os resultados obtidos. Os slides serão usados para apresentação do trabalho caso você seja sorteado para isso;
 - Referências.




## Material de apoio


- [CUDA C Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)  
  Guia da NVIDIA sobre programação em CUDA.
  
- [Experiência com grids, blocks e threads em CUDA](https://colab.research.google.com/drive/1uSTM6C0p4n4aAuvFksplqFxa4NG87rMp)  
  Notebook no Google Colab com um programa que permite experimentos variando as dimensões de grids e blocos.
