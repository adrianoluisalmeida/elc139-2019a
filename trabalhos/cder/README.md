[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > Trabalhos

# Prática no Cluster da Georgia State University


## Preparação

Nesta aula prática, você vai acessar o cluster CDER da Georgia State University (GSU). Verifique suas credenciais recebidas por email a acesse o cluster via SSH:
```
ssh user@cderlogin.gsu.edu
```
Caso o acesso não funcione, avise a professora e faça a atividade junto com um colega.


## Parte 1: Execução de job

1. Copie o arquivo pthreads_dotprod.tar.gz para o cluster CDER. Descompacte o arquivo e compile o programa.
   ```
   wget https://github.com/AndreaInfUFSM/elc139-2019a/raw/master/trabalhos/cder/pthreads_dotprod.tar.gz
   tar xzvf pthreads_dotprod.tar.gz
   cd pthreads_dotprod
   make
   ```

2. O cluster da GSU usa um gerenciador chamado SLURM. Você usará comandos do SLURM para lançar e  acompanhar suas execuções. Para submeter um script para execução, use o comando `sbatch`:
   ``` 
   sbatch sbatch-pthreads.sh
   ```

3. Verifique a fila de jobs (se não aparecer seu job, pode ser que já tenha terminado):
   ```
   squeue
   ```

4. A título de curiosidade, verifique a fila com todos os jobs gerenciados pelo SLURM:
   ```
   squeue -all
   ```

5. Observe os arquivos com as saídas (.out e .err) do seu job.

6. Obtenha informações sobre os nodos do cluster:
   ```
   scontrol show nodes
   ```

## Parte 2: Execução do programa gerador de fractais

1. Crie um script de execução para o seu programa gerador de fractais, com pelo menos 2 casos com diferentes números de threads.

2. Submeta seu programa gerador de fractais para execução no cluster.


## Parte 3: Execução de benchmark OpenMP

Nesta parte, você vai executar um [benchmark para OpenMP](http://www.epcc.ed.ac.uk/research/computing/performance-characterisation-and-benchmarking/epcc-openmp-micro-benchmark-suite) no cluster. Esse benchmark faz medições do overhead de certas operações do OpenMP.

1. Baixe o benchmark no cluster:
   ```
   wget http://www.epcc.ed.ac.uk/sites/default/files/DOCUMENTS/openmpbench_C_v31.tar.gz
   ```

2. Edite o arquivo Makefile.defs e ajuste as variáveis CC (troque para gcc) e CFLAGS/LDFLAGS (acrescente -fopenmp em ambas).

3. Compile o benchmark:
   ```
   make
   ```

4. Faça um teste de execução do benchmark `schedbench` antes de submetê-lo para execução na fila:
   ```
   ./schedbench
   ```

5. Crie um script de execução que teste o benchmark para diferentes números de threads OpenMP. Consulte o README.txt do benchmark para ver como configurar o número de threads.

6. Verifique a saída da execução. Você nota diferenças de overhead entre as opções de schedule? Isso é afetado pelo número de threads?


## Material de apoio

- [CDER - Knowledge Base](https://help.rs.gsu.edu/display/PD/CDER)  
  Site com informações sobre o cluster CDER na GSU.

- [Slurm Workload Manager](https://slurm.schedmd.com/documentation.html)  
  Documentação oficial do Slurm.

- [Slurm Quick Start Tutorial](https://support.ceci-hpc.be/doc/_contents/QuickStart/SubmittingJobs/SlurmTutorial.html)  
  Tutorial sobre Slurm oferecido pela Université de Namur, na Bélgica.

