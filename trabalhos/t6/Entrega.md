[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T6

# Comunicação coletiva em MPI

Nome: Gabriel Doyle Balk

# Parte 1

[Implementação do programa](matrix_mpi_collective.c)
<br/>

O trecho abaixo que possui um if else para descobrir quando processo numero zero está executando e também calculando o tamanho que cada processo deve calcular foi removido.

no if, o programa executa um laço, envia faz um SEND a matriz B e envia sucessivamente para cada processo e faz o mesmo com o tamanho do que cada processo vai calcular, também passando o ponto de inicio e final de cálculo.

no else os processos esperam as mensagens com tanto com a matriz B quanto com a matriz A e as posições para calculo.

```
if (myrank == 0)
  {
    for (int i = 1; i < nproc; ++i)
    {
      int lFrom = i * SIZE / nproc;
      int lTo = (i + 1) * SIZE / nproc;
      //printf("slice log: %d, %d\n", lFrom, lTo);
      // Broadcast B to other process
      MPI_Send(B, SIZE * SIZE, MPI_INT, i, tag_A, MPI_COMM_WORLD);
      // Send "Total of lines" / "Number of process" lines to other process
      MPI_Send(A[lFrom], (lTo - lFrom) * SIZE, MPI_INT, i, tag_B, MPI_COMM_WORLD;
    }
  }
  else
  {
    MPI_Recv(B, SIZE * SIZE, MPI_INT, MPI_ANY_SOURCE, tag_A, MPI_COMM_WORLD, &status);
    MPI_Recv(A[from], (to - from) * SIZE, MPI_INT, MPI_ANY_SOURCE, tag_B, MPI_COMM_WORLD, &status);
  }

```

Todo o código acima foi trocado pelo código abaixo, onde o MPI_Bcast, é responsavel pelo envio e recebimento da matriz B a todos os processos, e o ele é 'disparado' pelo processo root(processo 0).
Não é mais preciso executar o MPI_Send i vezes, a diretiva MPI_Bcast identifica quantos e quais processos o programa possui e faz o envio e recebimento automaticamente.

já o Scatter é responsável pelo envio e recebimento da matriz A para todos os processos e ele é 'disparado' pelo processo root(processo 0) também.
Onde fazia-se MPI_Send i vezes, agora só é preciso o MPI_Scatter e enviar como parâmetros a Matriz A, qual o tamanho será enviado e também a partir de que posição o processo vai receber e também quantos elementos.

```
  MPI_Bcast(B, TAM, MPI_INT, root, MPI_COMM_WORLD);
  MPI_Scatter(A, TAM / nproc, MPI_INT, A[from], TAM / nproc, MPI_INT, root, MPI_COMM_WORLD);
```

# Referências

- [MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)
- [Exemplos de comunicação](exemplos/)
