/*
    Author: Andrew Chin
    UIN: 425006084
    MATH 470-502
    Project: Pollard's p-1 Factorization Algorithm
    GitHub: https://github.com/4ndrewchin/cryptoproject
*/

#include <stdio.h>
#include <numeric>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
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
    int iterations = 0;
    for (int j = 2; j < N; ++j) {
        a = fastpower(a, j, N);
        d = gcd(a-1, N);
        ++iterations;
        if (d > 1 && d < N) {
            printf("iterations: %d\n", iterations);
            return d;
        }
    }
    printf("iterations: %d\n", iterations);
    return 1;
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

// generate a random number in the interval [1,999999]
int64 randnum() {
    srand(time(NULL));
    return rand() % 999999 + 1;
}

// return a string representing the time passed, in seconds and microseconds, between 2 intervals
string get_time_diff(timeval *tp1, timeval *tp2) {
    long sec = tp2->tv_sec - tp1->tv_sec;
    long musec = tp2->tv_usec - tp1->tv_usec;
    if (musec < 0) {
        musec += (int)1e6;
        sec--;
    }
    stringstream ss;
    ss<< "[Time: "<< sec << "." << musec << " sec]";
    return ss.str();
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
                return 0;
		}
    }
    timeval time_start, time_end; // timers
    gettimeofday(&time_start, 0); // start timer
    p = pollards(N);
    gettimeofday(&time_end, 0); // stop timer
    if (p == 1)
        printf("N = %lld is prime (factors p = 1 and q = %lld).\n", N, N);
    else
        printf("N = %lld has factors p = %lld and q = %lld.\n", N, p, N/p);
    printf("%s\n\n", get_time_diff(&time_start, &time_end).c_str());
}
