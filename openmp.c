#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    __int64_t total = 1e10; // Example amount
    int tn = 12;            // Threads

    __int64_t count = 0;
    double x, y;
#pragma omp parallel num_threads(tn)
    {
        unsigned seed = time(NULL);

#pragma omp for private(x, y) reduction(+ \
                                        : count)
        for (long long i = 0; i < total; i++)
        {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1)
            {
                count++;
            }
        }
    }
    double pi = 4 * (double)count / total;

    printf("[+] total = %lld\n", total);
    printf("[+] count = %lld\n", count);
    printf("[+] pi    = %f\n", pi);
    printf("[+] loss  = %e\n", acos(-1) - pi);
    printf("\nnum_threads = %d\n", tn);

    return 0;
}