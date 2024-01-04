/**
 * Realization of sieve of Eratosthenes algorithm in C++.
 * Algorithm finds all prime numbers in range [1, N]
 *
 * TIME: O(N * log(log(N)))
 * Memory: O(N)
 *
 * @author Kirill_Maglysh
*/

#include <vector>
#include <bitset>

using namespace std;
using ll = long long;

const int MAX_ROOT = 1e4;
const int MAX_N = MAX_ROOT * MAX_ROOT;

bitset<MAX_N> isNumComplex;

vector<int> getPrimeNumbers(int N) {
    vector<int> res;
    for (int d = 2; d < N; ++d) {
        if (!isNumComplex[d]) {
            res.push_back(d);
            if (d <= MAX_ROOT + 1) {
                for (int j = d * d; j < N; j += d) {
                    isNumComplex[j] = true;
                }
            }
        }
    }

    return res;
}