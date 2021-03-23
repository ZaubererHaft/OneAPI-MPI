#include <mpi.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int number;
  if (world_rank == 0) {
    number = -1;
    printf("Process %d waiting for process %d to ack\n", world_rank,
           world_rank + 1);
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (world_rank == 1) {
    MPI_Recv(&number, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received number %d from process 0\n", world_rank,
           number);
  }

  printf("Process %d continues its work\n", world_rank);

  MPI_Finalize();
}