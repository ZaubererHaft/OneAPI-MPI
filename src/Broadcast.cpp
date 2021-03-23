#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int root = 0;
  if (world_rank == 0) {
    root = -1;
  }

  // we are continuing as soon as the value was received
  MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);
  printf("Root is %d\n", root);

  // with barrier we sync with all processes
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();
}