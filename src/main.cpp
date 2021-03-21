#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int resultlen;
  int mpi_num_nodes;
  int mpi_my_rank;
  char mpi_hostname[MPI_MAX_PROCESSOR_NAME];
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_num_nodes);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_my_rank);
  MPI_Get_processor_name(mpi_hostname, &resultlen);
  fprintf(stderr, "NNODES=%d, MYRANK=%d, HOSTNAME=%s\n", mpi_num_nodes,
          mpi_my_rank, mpi_hostname);

  MPI_Finalize();
}