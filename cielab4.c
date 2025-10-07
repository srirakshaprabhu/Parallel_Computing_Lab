#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int arr[5];

    MPI_Init(&argc, &argv);                 // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get total number of processes

    if (rank == 0) {
        printf("Enter 5 integers: ");
        fflush(stdout); // Ensure prompt appears before input
        for (int i = 0; i < 5; i++) {
            scanf("%d", &arr[i]);
        }
    }

    // Broadcast the array from process 0 to all processes
    MPI_Bcast(arr, 5, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints the received array
    printf("Process %d received array: ", rank);
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    MPI_Finalize(); // Finalize MPI
    return 0;
}
