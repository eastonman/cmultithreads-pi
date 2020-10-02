#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int world_size, my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    __int64_t total;
    __int64_t local_total;
    __int64_t count;
    __int64_t local_count = 0;
    double x, y;

    srand(time(NULL));

    if (my_rank == 0)
    {
        total = 1e10 + 2;
        if (argc >= 2)
        {
            total = atoi(argv[1]);
        }

        local_total = total / world_size;
    }

    MPI_Bcast(&local_total, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    for (__int64_t i = 0; i < local_total; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1)
        {
            local_count++;
        }
    }
    MPI_Reduce(&local_count, &count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    double pi = 4 * (double)count / total;

    if (my_rank == 0)
    {
        printf("[+] total = %lld\n", world_size * local_total);
        printf("[+] count = %lld\n", count);
        printf("[+] pi    = %f\n", pi);
        printf("[+] loss  = %e\n", acos(-1) - pi);
        printf("\nProcesses = %d\n", world_size);
    }

    MPI_Finalize();
    return 0;
}