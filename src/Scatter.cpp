#include <cassert>
#include <cstdlib>
#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <vector>

int main(int argc, char *argv[]) {
  MPI_Init(NULL, NULL);

  const int array_size = argc > 1 ? atoi(argv[1]) : 8;
  const int root = 0;

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  assert(array_size % world_size == 0);

  const int chunksize = array_size / world_size;

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int *sendbuffer = nullptr;
  std::vector<int> recbuffer(chunksize, 0);

  if (world_rank == root) {
    std::cout << "scatter array of size " << array_size << " on " << world_size
              << " processes each with chunk size " << chunksize << std::endl;
    sendbuffer = new int[array_size];
    for (int i = 0; i < array_size; i++) {
      sendbuffer[i] = i;
    }
  }

  MPI_Scatter(sendbuffer, chunksize, MPI_INT, &recbuffer[0], chunksize, MPI_INT,
              root, MPI_COMM_WORLD);

  if (world_rank == root) {
    delete[] sendbuffer;
  }

  int lock = 0;

  if (world_rank > 0) {
    MPI_Recv(&lock, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  }

  std::cout << "process " << world_rank << " received values ";
  for (int i = 0; i < chunksize; i++) {
    std::cout << recbuffer[i] << ", ";
  }
  std::cout << std::endl;

  if (world_rank < world_size - 1) {
    MPI_Send(&lock, 1, MPI_INT, world_rank + 1, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}