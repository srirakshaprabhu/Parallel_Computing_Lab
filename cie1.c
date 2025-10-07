#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int isPrime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0) return 0;
    return 1;
}

int main() {
    int n = 20;
    int serialCount = 0, parallelCount = 0;
    double start, end;

    // Serial version
    start = omp_get_wtime();
    for (int i = 1; i <= n; i++) {
        if (isPrime(i)) serialCount++;
    }
    end = omp_get_wtime();
    printf("Serial Count of primes = %d\n", serialCount);
    printf("Execution time (serial): %.5f seconds\n", end - start);

    // Parallel version with dynamic scheduling
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:parallelCount)
    for (int i = 1; i <= n; i++) {
        if (isPrime(i)) parallelCount++;
    }
    end = omp_get_wtime();
    printf("Parallel Count of primes = %d\n", parallelCount);
    printf("Execution time (parallel): %.5f seconds\n", end - start);

    return 0;
}



