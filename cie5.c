#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int data[4];       // Array at process 0
    int recv_num;      // Each process receives one number
    int squared;       // Squared value
    int result[4];     // Gathered result at process 0

    MPI_Init(&argc, &argv);                 // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get total number of processes

    if (size != 4) {
        if (rank == 0) {
            printf("This program requires exactly 4 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Initialize array at process 0
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
    }

    // Scatter the array to all processes
    MPI_Scatter(data, 1, MPI_INT, &recv_num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process squares its received number
    squared = recv_num * recv_num;
    printf("Process %d got %d  squared = %d\n", rank, recv_num, squared);

    // Gather squared values back to process 0
    MPI_Gather(&squared, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered result at Process 0: [");
        for (int i = 0; i < 4; i++) {
            printf("%d", result[i]);
            if (i < 3) printf(", ");
        }
        printf("]\n");
    }

    MPI_Finalize(); // Finalize MPI
    return 0;
}
