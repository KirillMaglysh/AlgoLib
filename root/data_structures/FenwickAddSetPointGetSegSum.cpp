/**
 * Realization of Fenwick tree data structure in C++ for ADD/SET in point and sum query on segment.
 *
 * TIME: O(N) building + O(logN) ask
 * NOTE: ask is very fast, much more faster than SegmentTree or Binary Trees
 * Memory: N
 *
 * @author Kirill_Maglysh
*/

#include <vector>

using namespace std;

using ll = long long;

class FenwickTree {
private:
    int sz;
    vector<int> tree;
public:
    explicit FenwickTree(int sz) : sz(sz) {
        tree.resize(sz);
    }

    explicit FenwickTree(const vector<int>& src) : sz(int(src.size())) {
        tree.resize(sz);
        for (int i = 0; i < sz; ++i) {
            add(i, src[i]);
        }
    }

    void add(int pos, int val) {
        while (pos < sz) {
            tree[pos] += val;
            pos |= (pos + 1);
        }
    }

    void set(int pos, int val) {
        add(pos, val - getSum(val));
    }

    int getSum(int l, int r) {
        return getSum(r) - getSum(l - 1);
    }

    int getSum(int r) {
        int sum = 0;
        while (r >= 0) {
            sum += tree[r];
            r = (r & (r + 1)) - 1;
        }

        return sum;
    }
};
