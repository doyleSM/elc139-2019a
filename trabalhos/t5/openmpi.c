#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

typedef struct
{
  double *a;
  double *b;
  double c;
  int carga;
  int wsize;
  int repeat;
} dotdata_t;

dotdata_t dotdata;

/*
 * Funcao executada por um processo
 */
void dotprod_worker()
{
  int i, k;

  double *a = dotdata.a;
  double *b = dotdata.b;
  int carga = dotdata.carga;

  for (k = 0; k < dotdata.repeat; k++)
  {
    dotdata.c = 0.0;
    for (i = 0; i < carga; i++)
    {
      dotdata.c += (a[i] * b[i]);
    }
  }
}

/*
 * Tempo (wallclock) em microssegundos
 */
long wtime()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000 + t.tv_usec;
}

/*
 * Preenche vetor
 */
void fill(double *a, int size, double value)
{
  int i;
  for (i = 0; i < size; i++)
  {
    a[i] = value;
  }
}

/*
 * Funcao principal
 */
int main(int argc, char **argv)
{
  int numtasks, rank, dest, tag, source, rc;
  int wsize, repeat, carga, i;
  long start_time, end_time;
  double parteProc = 0.0;

  MPI_Status stat;

  if ((argc != 3))
  {
    printf("Uso: %s  <worksize> <repetitions>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  wsize = atoi(argv[1]);  // worksize = tamanho do vetor de cada thread
  repeat = atoi(argv[2]); // numero de repeticoes dos calculos (para aumentar carga)

  //divide a carga total entre os processos
  carga = wsize / numtasks;
  //se a divisao nao for inteira, o processo raiz fica com o excedente
  if (wsize % numtasks != 0)
  {
    if (rank == 0)
    {
      carga += wsize % numtasks;
    }
  }
  printf("Processo %d, wsize total %d, carga do proc %d\n", rank, wsize, carga);

  // Cria vetores
  dotdata.a = (double *)malloc(carga * sizeof(double));
  fill(dotdata.a, carga, 0.01);
  dotdata.b = (double *)malloc(carga * sizeof(double));
  fill(dotdata.b, carga, 1.0);
  dotdata.c = 0.0;
  dotdata.wsize = wsize;
  dotdata.carga = carga;
  dotdata.repeat = repeat;

  // Calcula c = a . b  medindo o tempo
  start_time = wtime();
  dotprod_worker();
  end_time = wtime();

  if (rank == 0)
  {
    printf("parte do processo %d = %f\n", rank, dotdata.c);
    for (i = 0; i < numtasks - 1; i++)
    {
      MPI_Recv(&parteProc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
      printf("parte do processo %d = %f\n", stat.MPI_SOURCE, parteProc);
      dotdata.c += parteProc;
    }
    printf("Produto escalar total = %f\n", dotdata.c);
    printf("Tempo = %ld usec\n", (long)(end_time - start_time));
  }
  else
  {
    MPI_Send(&dotdata.c, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }

  free(dotdata.a);
  free(dotdata.b);
  MPI_Finalize();

  return EXIT_SUCCESS;
}
