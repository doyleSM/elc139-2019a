#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
  int rank;     // "rank" do processo (0 a P-1)
  int numTasks; // n�mero de processos
  int tag = 0;  // "etiqueta" da mensagem
  int msg;      // msg que será enviada
  int dest;     // destino da msg
  int source;
  MPI_Status status; // "status" de uma opera��o efetuada

  // MPI_Init deve ser indestvocado antes de qualquer outra chamada MPI
  MPI_Init(&argc, &argv);

  // Descobre o "rank"  processo
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // Descobre o n�mero de processos
  MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
  if (numTasks < 2)
  {
    printf("preciso minimo de 2 processos\n");
    MPI_Finalize();
    return 1;
  }

  if (rank == 0)
  {
    msg = 10;
    dest = rank + 1;
    printf("Processo %d, Iniciando pipeline, mensagem inicial =  %d\n", rank, msg); // mostra mensagem

    MPI_Send(&msg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
  else if (rank != numTasks - 1)
  {
    source = rank - 1;
    dest = rank + 1;
    MPI_Recv(&msg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
    printf("Processo %d, recebi a mensagem %d\n", rank, msg); // mostra mensagem
    msg++;
    MPI_Send(&msg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
  else
  {
    source = rank - 1;
    MPI_Recv(&msg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
    //msg++;
    printf("Ultimo processo (%d), mensagem final %d\n", rank, msg); // mostra mensagem
  }
  MPI_Finalize(); // finaliza MPI
  return 0;
}
