#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmpxx.h>
#include <fstream>

#include "qs.h"

using namespace std;

extern uint32_t MINIMAL_BOUND;

// Input size threshold below which we resort to trial division.
const static uint32_t TRIAL_THRESHOLD = 100;

int main(int argc, char *argv[]) {
    ofstream fout("result_CG_300.txt", ios::app);
    clock_t time = clock();
    // Find some primes for trial division.
    vector<uint32_t> primes;
    uint32_t max = ceil(sqrt(TRIAL_THRESHOLD)) + 1;
    vector<bool> sieve(max, false);

    for (uint32_t p = 2; p < max; ++p) {
        if (sieve[p])
            continue;
        primes.push_back(p);
        for (uint32_t i = p; i < max; i += p)
            sieve[i] = true;
    }


    // Factor each of the 100 integers.
    mpz_class N(argv[1]);

    if (mpz_probab_prime_p(N.get_mpz_t(), 10)) {
        // N is prime.
        cout << N << endl;
    }

    stack<mpz_class> factors;
    factors.push(N);

    while (!factors.empty()) {
        mpz_class factor = factors.top();
        factors.pop();

        if (mpz_probab_prime_p(factor.get_mpz_t(), 10)) {
            // N is prime.
            cout << factor << endl;
            continue;
        }

        if (factor < TRIAL_THRESHOLD) {
            // Run trial division if below threshold.
            uint32_t smallFactor = factor.get_ui();
            for (uint32_t i = 0; i < primes.size(); ++i) {
                if (smallFactor % primes[i] == 0) {
                    factors.push(primes[i]);
                    factors.push(factor / primes[i]);
                    break;
                }
            }
        }
        else {
        mpz_class result = quadraticSieve(factor);
        factors.push(result);
        factors.push(factor/result);
        }
        cout << endl;
    }

    fout << strlen(argv[1]) << "\t\t";
    fout << (1000.0 * (clock() - time) / CLOCKS_PER_SEC) << endl;
    fout.close();

    return 0;
}