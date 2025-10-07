
// deadlock_mpi.c
#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank;
    char message[50];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Recv(message, 50, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received message: %s\n", message);
    } else if (rank == 1) {
        MPI_Recv(message, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message: %s\n", message);
    }

    MPI_Finalize();
    return 0;
}
