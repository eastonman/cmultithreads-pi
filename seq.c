#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    srand(time(NULL)); // Initial Seed
    mpz_t total;
    mpz_init_set_d(total, 1e8); // Sample Amount
    mpz_t count;
    mpz_init_set_ui(count, 0); // Points in area

    double x, y; // Point location

    mpz_t i;
    mpz_init_set_ui(i, 0);
    mpz_t temp;
    mpz_init(temp);
    mpz_t one;
    mpz_init_set_ui(one, 1);
    for (; mpz_cmp(i, total) == -1; mpz_add(temp, i, one), mpz_swap(temp, i))
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1)
        {
            mpz_add(temp, count, one);
            mpz_swap(temp, count);
        }
    }
    mpz_t four;
    mpz_init_set_ui(four, 4);
    mpf_t pi;
    mpf_init(pi);
    mpz_mul(temp, count, four);
    mpf_t tempf, totalf;
    mpf_init(tempf);
    mpf_init(totalf);
    mpf_set_z(tempf, temp);
    mpf_set_z(totalf, total);
    mpf_div(pi, tempf, totalf);

    gmp_printf("%Ff\n", pi);
    mpz_clears(total, count, temp, i, one, four, NULL);
    return 0;
}
