#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    long long total = 1e8;

    long long count = 0;
    double x, y;
    for (long long i = 0; i < total; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1)
        {
            count++;
        }
    }
    double pi = 4 * (double)count / total;

    printf("[+] total = %lld\n", total);
    printf("[+] count = %lld\n", count);
    printf("[+] pi    = %f\n", pi);
    printf("[+] loss  = %e\n", acos(-1) - pi);

    return 0;
}