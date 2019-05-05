[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T5

# Primeiros passos com MPI

Nome: Gabriel Doyle Balk

# Parte 1

[Implementação em OpenMPI](openmpi.c) do programa que calcula repetidas vezes o produto escalar entre 2 vetores em openMP [versão OpenMP](https://github.com/doyleSM/elc139-2019a/blob/master/trabalhos/t2/openmp/openmp.c).

| Entrada                                  | Vetor    | Repetições | 1 Processo    | 2 Processos   | 4 Processos |
| ---------------------------------------- | -------- | ---------- | ------------- | ------------- | ----------- |
| mpirun -np (1,2,4) openmpi 1000000 1000  | 1000000  | 1000       | 3125991 usec  | 1660884 usec  | 1338731     |
| mpirun -np (1,2,4) openmpi 3000000 1000  | 3000000  | 1000       | 9672545 usec  | 5364396 usec  | 4297139     |
| mpirun -np (1,2,4) openmpi 10000000 1000 | 10000000 | 1000       | 31243911 usec | 18207751 usec | 14653807    |

Com base na tabela abaixo, vemos que houve um ganho bastante alto com 2 processos em relação ao sequencial, e um ganho melhor ainda com a passagem para 4 processos, também é possível notar, que o speedUp diminui pouco, mas diminui, com o aumento do tamanho do vetor

| Entrada                                  | Vetor    | Repetições | 2 Processos(Speedup) / eficiência | 4 Processos(Speedup) / eficiência |
| ---------------------------------------- | -------- | ---------- | --------------------------------- | --------------------------------- |
| mpirun -np (1,2,4) openmpi 1000000 1000  | 1000000  | 1000       | 1.88 / 94%                        | 2.33 / 58%                        |
| mpirun -np (1,2,4) openmpi 3000000 1000  | 3000000  | 1000       | 1.80 / 90%                        | 2.25 / 56,25%                     |
| mpirun -np (1,2,4) openmpi 10000000 1000 | 10000000 | 1000       | 1.71 / 85,5%                      | 2.13 / 53,25%                     |

# Parte 2

# Parte 3

Correções dos programas:<br/>
[Correção 1](mpi_corrigido1.c)<br/>
[Correção 2](mpi_corrigido2.c)

<!--
# Resultados

Os resultados do speedup e da eficiência podem ser encontrados nas tabelas abaixo:

[tabela](TabelaPar1.md) de comparação fractalpar1.cpp<br/>
[tabela](TabelaPar2.md) de comparação fractalpar2.cpp
-->
