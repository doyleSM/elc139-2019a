#include <mpi.h>
#include <stdio.h>
#include <sys/time.h>
#define root 0
#define SIZE 8

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

long wtime()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000 + t.tv_usec;
}

void fill_matrix(int m[SIZE][SIZE])
{
  static int n = 0;
  int i, j;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      m[i][j] = n++;
}

void print_matrix(int m[SIZE][SIZE])
{
  int i, j = 0;
  for (i = 0; i < SIZE; i++)
  {
    printf("\n\t| ");
    for (j = 0; j < SIZE; j++)
      printf("%*d", 6, m[i][j]);
    printf("|");
  }
}

int main(int argc, char *argv[])
{
  int myrank, nproc, from, to, i, j, k;
  int TAM;
  long start_time, end_time;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* who am i */
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);  /* number of processors */

  if (SIZE % nproc != 0)
  {
    if (myrank == 0)
      printf("Matrix size not divisible by number of processors\n");
    MPI_Finalize();
    return -1;
  }

  from = myrank * SIZE / nproc;
  to = (myrank + 1) * SIZE / nproc;
  TAM = SIZE * SIZE;

  /* Process 0 fills the input matrices and broadcasts them to the rest */
  /* (actually, only the relevant stripe of A is sent to each process) */

  if (myrank == 0)
  {
    fill_matrix(A);
    fill_matrix(B);
  }
  start_time = wtime();
  //buff, tipo, tag, comm
  MPI_Bcast(B, TAM, MPI_INT, root, MPI_COMM_WORLD);
  MPI_Scatter(A[from], TAM / nproc, MPI_INT, A[from], TAM / nproc, MPI_INT, root, MPI_COMM_WORLD);

  printf("computing slice %d (from row %d to %d)\n", myrank, from, to - 1);
  for (i = from; i < to; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      C[i][j] = 0;
      for (k = 0; k < SIZE; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  MPI_Gather(C[from], TAM / nproc, MPI_INT, C, TAM / nproc, MPI_INT, root, MPI_COMM_WORLD);
  end_time = wtime();
  if (myrank == 0)
  {
    printf("tempo de execução: %ld\n\n", (long)(end_time - start_time));

    printf("\n\n");
    print_matrix(A);
    printf("\n\n\t       * \n");
    print_matrix(B);
    printf("\n\n\t       = \n");
    print_matrix(C);
    printf("\n\n");
  }

  MPI_Finalize();
  return 0;
}
