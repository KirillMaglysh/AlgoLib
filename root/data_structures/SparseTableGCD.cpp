/**
 * Realization of Sparse Table data structure in C++ for GCD query.
 *
 * TIME: O(N*logN) building + O(log_2(Max_A)) ask
 * Memory: N*logN
 *
 * @author Kirill_Maglysh
*/

#include <vector>
#include <algorithm>

using namespace std;

class SparseTable {
private:
    vector<vector<int>> st;
    vector<int> log2;
public:
    explicit SparseTable(vector<int>& src) {
        int n = int(src.size());
        log2.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            log2[i] = log2[i >> 1] + 1;
        }
        st.resize(log2[n] + 1, vector<int>(n));
        for (int i = 0; i < n; i++) {
            st[0][i] = src[i];
        }
        for (int j = 1; j <= log2[n]; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = __gcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int ask(int l, int r) {
        int j = log2[r - l + 1];
        return __gcd(st[j][l], st[j][r - (1 << j) + 1]);
    }
};
