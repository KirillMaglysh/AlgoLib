/**
 * Realization of Fenwick tree data structure in C++ for ADD/SET in point and sum query on segment.
 *
 * TIME: O(N) building + O(logN) ask
 * NOTE: ask is very fast, much more than SegmentTree or Binary Trees
 * Memory: N
 *
 * @author Kirill_Maglysh
*/

#include <vector>

using namespace std;

using ll = long long;

class FenwickTree {
private:
    ll sz;
    vector<ll> tree;
public:
    explicit FenwickTree(ll sz) : sz(sz) {
        tree.resize(sz);
    }

    explicit FenwickTree(const vector<ll>& src) : sz(ll(src.size())) {
        tree.resize(sz);
        for (ll i = 0; i < sz; ++i) {
            add(i, src[i]);
        }
    }

    void add(ll pos, ll val) {
        while (pos < sz) {
            tree[pos] += val;
            pos |= (pos + 1);
        }
    }

    void set(ll pos, ll val) {
        add(pos, val - getSum(val));
    }

    ll getSum(ll l, ll r) {
        return getSum(r) - getSum(l - 1);
    }

    ll getSum(ll r) {
        ll sum = 0;
        while (r >= 0) {
            sum += tree[r];
            r = (r & (r + 1)) - 1;
        }

        return sum;
    }
};
