#include <cstdlib>
#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <vector>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int max = 100;
  srand(time(NULL));
  int length = (rand() % max) + 1;
  std::vector<int> buffer(length);

  for (int i = 0; i < length; i++) {
    buffer[i] = rand();
  }

  if (world_rank == 0) {
    printf("Process %d sends %d elements to %d\n", world_rank, length,
           world_rank + 1);
    MPI_Send(&buffer[0], length, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (world_rank == 1) {
    int received_length;
    MPI_Status status;
    // we receive at most max numbers!
    MPI_Recv(&buffer[0], max, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
             MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_INT, &received_length);

    printf("Process %d received %d elements from process %d\n", world_rank,
           received_length, status.MPI_SOURCE);
  }

  printf("Process %d continues its work\n", world_rank);

  MPI_Finalize();
}