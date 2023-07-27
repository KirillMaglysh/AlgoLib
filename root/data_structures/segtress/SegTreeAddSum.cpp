#include <vector>

using namespace std;
using ll = long long;

class SegTree {
private:
    const ll INF18 = 1e18;
    vector<ll> tree;
    vector<ll> storage;
    int sz;

    void build(int root, int l, int r, const vector<ll>& src) {
        if (l == r) {
            tree[root] = src[l];
            return;
        }

        int m = (l + r) >> 1;
        int lRoot = (root << 1) + 1;
        int rRoot = (root << 1) + 2;
        build(lRoot, l, m, src);
        build(rRoot, m + 1, r, src);
        tree[root] = tree[lRoot] + tree[rRoot];
    }

    ll geSum(int root, int l, int r, int sL, int sR) {
        push(root, l, r);
        if (sL <= l && r <= sR) {
            return tree[root];
        }

        if (l > sR || r < sL) {
            return 0;
        }

        int m = (l + r) >> 1;
        int lRoot = (root << 1) + 1;
        int rRoot = (root << 1) + 2;
        return geSum(lRoot, l, m, sL, sR) + geSum(rRoot, m + 1, r, sL, sR);
    }

    void add(int root, int l, int r, int sL, int sR, ll val) {
        push(root, l, r);
        if (sL <= l && r <= sR) {
            storage[root] += val;
            push(root, l, r);
            return;
        }

        if (l > sR || r < sL) {
            return;
        }

        int m = (l + r) >> 1;
        int lRoot = (root << 1) + 1;
        int rRoot = (root << 1) + 2;
        add(lRoot, l, m, sL, sR, val);
        add(rRoot, m + 1, r, sL, sR, val);
        tree[root] = tree[lRoot] + tree[rRoot];
    }

    void push(int root, int l, int r) {
        if (!storage[root]) {
            return;
        }

        tree[root] += storage[root] * (r - l + 1);
        if (l < r) {
            int lRoot = (root << 1) + 1;
            int rRoot = (root << 1) + 2;
            storage[lRoot] += storage[root];
            storage[rRoot] += storage[root];
        }

        storage[root] = 0;
    }

public:
    explicit SegTree(const vector<ll>& src) : sz(int(src.size())) {
        tree.resize((1 << (__lg(sz) + 2)));;
        storage.resize((1 << (__lg(sz) + 2)));;
        build(0, 0, sz - 1, src);
    }

    explicit SegTree(int sz) : sz(sz) {
        tree.resize((1 << (__lg(sz) + 2)));;
        storage.resize((1 << (__lg(sz) + 2)));;
    }

    ll geSum(int l, int r) {
        return geSum(0, 0, sz - 1, l, r);
    }

    void add(int l, int r, ll val) {
        add(0, 0, sz - 1, l, r, val);
    }
};
