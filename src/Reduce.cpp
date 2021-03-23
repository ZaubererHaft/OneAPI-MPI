#include <mpi.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int send_buffer[2];
  send_buffer[0] = world_rank;
  send_buffer[1] = world_rank + 1;

  printf( "process %d is sending %d to reduction by sum\n", world_rank, world_rank);
  int receive_buffer[2];
  receive_buffer[0] = -1;
  receive_buffer[1] = -1;

  //use MPI_Allreduce to sent result to all processes
  MPI_Reduce(&send_buffer, &receive_buffer, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  printf("process %d receive_buffer[0]=%d, receive_buffer[1]=%d \n", world_rank, receive_buffer[0], receive_buffer[1]);

  MPI_Finalize();
}