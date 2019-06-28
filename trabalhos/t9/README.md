[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > Trabalhos

# T9: Maratona de Programação Paralela

Neste trabalho, equipes de (até) 2 alunos deverão resolver problemas da [Maratona de Programação Paralela de 2017](http://lspd.mackenzie.br/marathon/17/problems.html).

No site da maratona, há 5 problemas da competição e 1 de aquecimento. Todos os 6 problemas valem para este trabalho. Para cada problema, há um texto descritivo e um pacote com o código fonte de referência. Os nomes dos problemas são importantes na entrega e devem ser usados sem modificações: São eles: `sum`, `transitive_closure`, `eternity`, `mandelbrot`, `kmeans` e `shortest_superstring`. Os programas poderão ser paralelizados usando OpenMP, MPI e/ou CUDA. Outras otimizações de desempenho também são permitidas, desde que os problemas sejam resolvidos com paralelismo.


No arquivo [problemset.pdf](http://lspd.mackenzie.br/marathon/17/problemset.pdf), há instruções que são aplicadas para as maratonas que acontecem durante eventos como WSCAD ou ERAD. As equipes devem ler essas instruções com atenção. Para a disciplina, usaremos essas instruções com algumas especializações descritas abaixo.


## Entrega

No repositório de cada integrante da equipe, deve haver uma pasta `trabalhos/t9`. Dentro desta pasta, deve haver um pasta para cada problema resolvido, usando o nome **exato** do problema. Para cada problema, devem ser entregues 3 arquivos nomeados de acordo com o problema: um arquivo problema.zip com o código-fonte, um Makefile e um script run-problema.sh para submissão de job no SLURM  (**substitua `problema` pelo nome do problema**). 

Por exemplo, para entregar o problema `mandelbrot`, devem ser entregues os arquivos `mandelbrot.zip`, `Makefile` e `run-mandelbrot.sh`.

O script deverá compilar o código usando make e depois executar o programa. Pode-se usar opções de compilação e execução que favoreçam o desempenho de cada solução.


## Execução
Os programas serão executados no cluster CDER da Georgia State University,
O tempo será medido com o comando `/usr/bin/time -f%e` (ou equivalente no bash). A medição de tempo será inserida nos scripts de submissão de jobs após a entrega do trabalho.

Somente alguns nós permitem executar um programa com CUDA. Os seguintes nós foram testados com sucesso: cder01 e cder02. Os nós cder27 e cder28 também possuem GPUs (veja especificações aqui: https://help.rs.gsu.edu/display/PD/CDER), mas aparentemente há restrições para alocá-los (submissão fica pendente). Para submeter um job em cder01, por exemplo, entre neste nó por ssh e submeta o script:
```
ssh cder01
sbatch --nodelist=cder01 run-problema.sh
```

Para calcular o speedup de cada problema resolvido, será feita uma média dos tempos de execução. O número de rodadas poderá variar dependendo do problema (em geral, 3 rodadas), mas todas as equipes que resolverem um mesmo problema terão seus programas executados o mesmo número de vezes.




