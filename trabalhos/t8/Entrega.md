# T8: Geração de Imagem em Paralelo com CUDA

Disciplina: elc139 - Programação Paralela <br/>
Aluno: Adriano Luís de Almeida

## Parte 1

### 1.1 Implemente um programa nomeado wavecuda1.cu, em que cada frame seja computado em paralelo por uma thread diferente.

- Link do código implementado: [wavecuda1.cu](https://github.com/adrianoluisalmeida/elc139-2019a/blob/master/trabalhos/t8/wave/wavecuda1.cu)


*cudaMallocManaged* faz a alocação de memoria para substituir camada malloc do C e retorna um ponteiro acessível em qualquer processador
```
cudaMallocManaged(&pic, frames*width*width*sizeof(unsigned char));
```

```
calculate<<<1, frames>>>(width, frames, pic);
```
Como pode ser notado na chamada da função criada e nomeada como calculate, o número de frames é usado para a criação de threads, de acordo com o enunciado. 

Dentro do método calculate é utilizado mais duas chamadas como demonstrado abaixo:

```cu
int index = threadIdx.x;

int offset = blockDim.x;
```

*threadIdx.x* Índice de segmento dentro do bloco
*blockDim.x* Contém as dimensões do bloco


Após a execução de toda o método calculate *cudaDeviceSynchronize();* forçará o programa a garantir que os *kernels/memcpys* dos fluxos estejam completos antes de continuar.

```cu
cudaDeviceSynchronize();
```

#### 1.2 Analise o desempenho do programa, começando pela medição dos tempos de execução sequencial e paralela para pelo menos 4 diferentes entradas do programa, sendo: a) 1024 100, b) 1024 200 e outras 2 entradas à sua escolha. Compare os tempos obtidos. Use nvprof para analisar o perfil de execução em GPU. Explique seus resultados.

- Para rodar os testes foi criado um *notebook* no Google Colaboratory disponível [!AQUI!](https://colab.research.google.com/drive/1CzPMpda53H_z63G1d4_iMkgrX_h9u1dS#scrollTo=6AWymX21ISIV)
- Lembre-se: Para iniciar, faça uma cópia deste notebook clicando em File -> Save a copy in Drive. Faça o restante da prática usando sua cópia. Em Runtime -> Change runtime type, habilite o uso de GPU.

#### Testes e resultados WAVE:
!./wave 1024 100   
computing 100 frames of 1024 by 1024 picture   
compute time: 5.4348 s   

!./wave 1024 200   
computing 200 frames of 1024 by 1024 picture   
compute time: 11.0191 s   

!./wave 2048 100   
computing 100 frames of 2048 by 2048 picture   
compute time: 21.6637 s   

!./wave 2048 200   
computing 200 frames of 2048 by 2048 picture   
compute time: 42.2622 s   

#### Testes e resultados WAVECUDA1:
(Conforme a descrição foi utilzado nvprof, como presente no *notebook*. Para deixar mais *clean* os resultados, vou deixar sem a utilização do nvprof, mas pode ser executado usando ele no *notebook* );

!./wavecuda1 1024 100   
computing 100 frames of 1024 by 1024 picture   
compute time: 0.6502 s   

!nvprof ./wavecuda1 1024 200   
computing 200 frames of 1024 by 1024 picture   
compute time: 0.6784 s   

!./wavecuda1 2048 100   
computing 100 frames of 2048 by 2048 picture   
compute time: 2.0165 s   

!./wavecuda1 2048 200   
computing 200 frames of 2048 by 2048 picture   
compute time: 2.1749 s   

## Referências

[NVIDIA. CUDA C Programming Guide. 2019](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)   
[Mark Harris. An Even Easier Introduction to CUDA. 2017](https://devblogs.nvidia.com/even-easier-introduction-cuda/)   
[Mark Harris. Unified Memory for CUDA Beginners. 2017](https://devblogs.nvidia.com/unified-memory-cuda-beginners/)   
