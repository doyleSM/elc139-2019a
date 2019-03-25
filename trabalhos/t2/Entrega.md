[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > T2

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

# OpenMP
