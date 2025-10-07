#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int sum_reduce = 0;
    int sum_allreduce = 0;

    MPI_Init(&argc, &argv);                 // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get total number of processes

    // Each process has its rank as the value
    int local_value = rank;

    // Use MPI_Reduce to compute sum at process 0
    MPI_Reduce(&local_value, &sum_reduce, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("MPI_Reduce result at Process 0: Sum of ranks = %d\n", sum_reduce);
    }

    // Use MPI_Allreduce to compute and share the sum with all processes
    MPI_Allreduce(&local_value, &sum_allreduce, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("MPI_Allreduce result at Process %d: Sum of ranks = %d\n", rank, sum_allreduce);

    MPI_Finalize(); // Finalize MPI
    return 0;
}
