/*
    Author: Andrew Chin
    UIN: 425006084
    MATH 470-502
    Project: Pollard's p-1 Factorization Algorithm
*/

#include <stdio.h>
#include <numeric>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
using namespace std;

typedef long long int64;

/*--------------------------------------------------------------------------*/
/* Pollard's p-1 Factorization Algorithm */
/*--------------------------------------------------------------------------*/

// calculate x^e (mod m) using fast powering algorithm,
// also known as modular exponentiation
// "An Introduction to Mathematical Cryptography", Hoffstein et. al., pg. 53
int64 fastpower(int64 x, int64 e, int64 m) {
    int64 a = x;
    int64 b = 1;
    while (e > 0) {
        if ((e % 2) == 1)
            b = (b * a) % m;
        a = (a * a) % m;
        e = floor(e / 2);
        if (e <= 0)
            break;
    }
    return b;
}

// returns one factor of N (which is used to easily calculate the second factor)
// "An Introduction to Mathematical Cryptography", Hoffstein et. al., pg. 139
int64 pollards(int64 N) {
    int64 a = 2;
    int64 d;
    for (int j = 2; j < N; ++j) {
        a = fastpower(a, j, N);
        d = gcd(a-1, N);
        if (d > 1 && d < N)
            return d;
    }
    return 1;
}

// generate a random number in the interval [1,999999]
int64 randnum() {
    srand(time(NULL));
    return rand() % 999999 + 1;
}

/*--------------------------------------------------------------------------*/
/* HELPER FUNCTIONS */
/*--------------------------------------------------------------------------*/

// print the help text
void print_help() {
    printf("-------------------------------------------------------\n");
    printf("         Pollard's p-1 Factorization Algorithm\n");
    printf("-------------------------------------------------------\n");
    printf("USAGE: pollards [options] <inputs>\n");
    printf("OPTIONS:\n");
    printf("  -n <value> factor a specified value\n");
    printf("  -r         generate a random number to factor\n");
    printf("  -h         print this help menu\n");
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }
    // parse command line arguments
    int64 N, p;
    int opt = 0;
    while ((opt = getopt(argc, argv, "n:rh")) != -1) {
        switch (opt) {
            case 'n':
                N = (int64)atoll(optarg);
                break;
            case 'r':
                N = randnum();
                break;
            case 'h':
                print_help();
            default:
                return 0;
		}
    }
    p = pollards(N);
    if (p == 1)
        printf("N = %lld is prime (factors p = 1 and q = %lld).\n", N, N);
    else
        printf("N = %lld has factors p = %lld and q = %lld.\n", N, p, N/p);
}
