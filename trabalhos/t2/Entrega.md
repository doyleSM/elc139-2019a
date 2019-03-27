[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T2

# Programação Paralela Multithread

Nome: Gabriel Doyle Balk
[Especificações do sistema](specs.txt)

[Pthreads](#Pthreads)
[OpenMP](#openmp)

# Pthreads

1. Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).

#### Particionamento

Com base no exemplo dado

```
./pthreads_dotprod 2 500000 2000
```

O trecho de código abaixo mostra que o tamanho do vetor é calculado de acordo com o numero de threads inserido, no exemplo dado teremos dois vetores com 500000 elementos cada

```
   dotdata.a = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.a, wsize*nthreads, 0.01);
   dotdata.b = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.b, wsize*nthreads, 1.0);
```

e o particionamento é feito da seguinte maneira:
quando criamos as threads em

```
for (i = 0; i < nthreads; i++) {
   pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
}
```

chamamos dotprod_workder enviando o 'id' de cada thread, como no exemplo citado anteriormente, temos duas threads (0 e 1)

```
void *dotprod_worker(void *arg){
   int i, k;
   long offset = (long) arg;
   double *a = dotdata.a;
   double *b = dotdata.b;
   int wsize = dotdata.wsize;
   int start = offset*wsize;
   int end = start + wsize;
   double mysum;
}
```

a primeira thread terá:

```
offset = 0
wsize = 500000
start = 0 * 500000 = 0
end = 0 + 500000 = 500000
```

e a segunda thread:

```
offset = 1
wsize = 500000
start = 1 * 500000 = 500000
end = 500000 + 500000 = 1000000
```

a distribuição da carga entre as threadas é dada pelo código abaixo

```
for (k = 0; k < dotdata.repeat; k++) {
    mysum = 0.0;
    for (i = start; i < end ; i++)  {
        mysum += (a[i] * b[i]);
    }
}
```

ambas as threads terão o mesmo numero de repetições já que o dotdata.repeat
é igual para ambas.
mas o **for interno é onde realmente a carga é dividida** .
ainda com o mesmo exemplo temos:
a primeira* thread executará de start = 0 até 499999 (end < 500000)
e a segunda* thread executatá de start = 500000 até 999999 (end < 1000000)
garantindo assim que ambas operem em cima do mesmo numero de dados

\* Primeira e segunda de acordo com a ordem de criação, na pŕatica não temos como garantir qual delas será executada primeiro, pois depende do escalonador.

#### Comunicação

A comunicação é feita onde são somadas as parcias de cada thread, como mostra o trecho abaixo:

```
pthread_mutex_lock (&mutexsum);
dotdata.c += mysum;
pthread_mutex_unlock (&mutexsum);
```

#### Aglomeração

A aglomeração é feita nas somas das várias multiplicações de cada thread, afim de ter uma parcial. como no trecho abaixo.

```
for (k = 0; k < dotdata.repeat; k++) {
    mysum = 0.0;
    for (i = start; i < end ; i++)  {
        mysum += (a[i] * b[i]);
    }
}
```

#### Mapeamento

o mapeamento é feito de forma estática, como é mostrado no código abaixo, onde criamos as threads e como dito no particionamento, chamamos a função dotprod_workder que passa o mesmo tamanho de worksize para todas as threads, não há um balanceamento caso alguma thread termine antes de outra.

```
for (i = 0; i < nthreads; i++) {
   pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
}
```

2. Considerando o tempo (em microssegundos) mostrado na saída do programa, qual foi a aceleração (speedup) com o uso de threads?

Média de 5 execuções

Speedup = TSeq / TPar
Speedup = 6312160 usec / 3311287 usec = 1.90

A aceleração foi de ~ 1.90.

3. A aceleração se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão, você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

| Vetor    | Repetições | 1 Thread | 2 Threads | 4 Threads |
| -------- | ---------- | -------- | --------- | --------- |
| 1000000  | 1000       | 3125604  | 1713023   | 1362928   |
| 1000000  | 2000       | 6231789  | 3314419   | 2735857   |
| 1000000  | 3000       | 9352403  | 4870448   | 4157044   |
| 3000000  | 1000       | 9379908  | 4897896   | 4504889   |
| 300000   | 2000       | 18796851 | 9771083   | 9049266   |
| 3000000  | 3000       | 28219169 | 14647455  | 13747390  |
| 10000000 | 1000       | 31354402 | 16323965  | 14939473  |
| 10000000 | 2000       | 62897084 | 33822323  | 30412280  |
| 10000000 | 3000       | 93976112 | 54427782  | 46721233  |

Com base na tabela abaixo, vemos claramente que houve um ganho significativo com o acrescimo de uma thread em relação ao sequencial, porém com a passagem de duas para quatro threads o ganho não foi tão significativo. Também é possível notar que o ganho com 4 threads caiu conforme o tamanho do vetor ia aumentando.

| Vetor    | Repetições | 2 Threads(Speedup) | 4 Threads(Speedup) |
| -------- | ---------- | ------------------ | ------------------ |
| 1000000  | 1000       | 1.82               | 2.29               |
| 1000000  | 2000       | 1.88               | 2.27               |
| 1000000  | 3000       | 1.92               | 2.24               |
| 3000000  | 1000       | 1.91               | 2.08               |
| 3000000  | 2000       | 1.92               | 2.07               |
| 3000000  | 3000       | 1.92               | 2.05               |
| 10000000 | 1000       | 1.92               | 2.09               |
| 10000000 | 2000       | 1.85               | 2.06               |
| 10000000 | 3000       | 1.72               | 2.01               |

5. Explique as diferenças entre [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c). Com as linhas removidas, o programa está correto?

O programa `pthreads_dotprod.c` usa mutex para exclusão mútua no acesso à váriavel
`dotdata.c` enquanto o `pthreads_dotprod2.c` deixa o acesso livre.
O programa não está correto, pois em casos raros é possível que as duas variáveis leiam o valor de `dotdata.c` ao mesmo tempo fazendo com que a soma seja inconsistente.

# OpenMP

2. Avalie o desempenho do programa em OpenMP, usando os mesmos dados/argumentos do programa com threads POSIX.

- [Aprendendo a usar a estrutura OpenMP com GCC](https://www.ibm.com/developerworks/br/aix/library/au-aix-openmp-framework/index.html)
- [Introdução ao OpenMPM](https://www.dcc.fc.up.pt/~fds/aulas/PPD/0708/intro_openmp-1x2.pdf)
