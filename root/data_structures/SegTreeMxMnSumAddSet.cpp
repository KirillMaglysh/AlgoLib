/**
 * Realization of Segment tree data structure in C++ for MAX, MIN, SUM, ADD queries on segments [l, r] and set for pos.
 *
 * TIME: O(N) building + O(logN) ask
 * Memory: N * 4
 *
 * @author Kirill_Maglysh
*/

#include <vector>
#include <cassert>

using namespace std;

using ll = long long;

class SegTree {
private:
    struct Node {
        ll mn;
        ll mx;
        ll sum;
        ll lazy = 0;
    };

    ll def = 0;
    ll sz;
    vector<Node> tree;

    void build(ll root, ll l, ll r) {
        if (l == r) {
            tree[root] = {def, def, def};
            return;
        }

        ll m = (l + r) >> 1;
        ll lRoot = (root << 1) + 1;
        ll rRoot = (root << 1) + 2;
        build(lRoot, l, m);
        build(rRoot, m + 1, r);

        tree[root] = merge(tree[lRoot], tree[rRoot]);
    }

    void build(ll root, ll l, ll r, const vector<ll>& src) {
        if (l == r) {
            tree[root] = {src[l], src[l], src[l]};
            return;
        }

        ll m = (l + r) >> 1;
        ll lRoot = (root << 1) + 1;
        ll rRoot = (root << 1) + 2;
        build(lRoot, l, m, src);
        build(rRoot, m + 1, r, src);

        tree[root] = merge(tree[lRoot], tree[rRoot]);
    }

    Node merge(const Node& A, const Node& B) {
        return {
                min(A.mn, B.mn),
                max(A.mx, B.mx),
                A.sum + B.sum
        };
    }

    Node get(ll root, ll l, ll r, ll sL, ll sR) {
        push(root, l, r);
        if (sL <= l && r <= sR) {
            return tree[root];
        }

        ll m = (l + r) >> 1;
        ll lRoot = (root << 1) + 1;
        ll rRoot = (root << 1) + 2;
        if (sR <= m) {
            return get(lRoot, l, m, sL, sR);
        } else if (m < sL) {
            return get(rRoot, m + 1, r, sL, sR);
        } else {
            return merge(get(lRoot, l, m, sL, sR), get(rRoot, m + 1, r, sL, sR));
        }
    }

    void checkBorders(ll pos) {
        assert(0 <= pos && pos < sz);
    }

    void checkBorders(ll l, ll r) {
        assert(0 <= l && l <= r && r < sz);
    }

    void push(ll root, ll l, ll r) {
        if (!tree[root].lazy) {
            return;
        }

        tree[root].sum += tree[root].lazy * (r - l + 1);
        tree[root].mx += tree[root].lazy;
        tree[root].mn += tree[root].lazy;
        if (l < r) {
            ll lRoot = (root << 1) + 1;
            ll rRoot = (root << 1) + 2;
            tree[lRoot].lazy += tree[root].lazy;
            tree[rRoot].lazy += tree[root].lazy;
        }

        tree[root].lazy = 0;
    }

    Node getVal(ll root, ll l, ll r, ll pos) {
        push(root, l, r);

        if (l == r) {
            return tree[root];
        }

        ll m = (l + r) >> 1;
        if (pos <= m) {
            return getVal((root << 1) + 1, l, m, pos);
        } else {
            return getVal((root << 1) + 2, m + 1, r, pos);
        }
    }

    void add(ll root, ll l, ll r, ll sL, ll sR, ll val) {
        push(root, l, r);
        if (sL <= l && r <= sR) {
            tree[root].lazy += val;
            push(root, l, r);
            return;
        }

        ll m = (l + r) >> 1;
        ll lRoot = (root << 1) + 1;
        ll rRoot = (root << 1) + 2;
        if (sR <= m) {
            add(lRoot, l, m, sL, sR, val);
        } else if (m < sL) {
            add(rRoot, m + 1, r, sL, sR, val);
        } else {
            add(lRoot, l, m, sL, sR, val);
            add(rRoot, m + 1, r, sL, sR, val);
        }

        tree[root] = merge(tree[lRoot], tree[rRoot]);
    }

    void set(ll root, ll l, ll r, ll pos, ll val) {
        push(root, l, r);
        if (l == r) {
            tree[root] = {val, val, val, 0};
            return;
        }

        ll m = (l + r) >> 1;
        ll lRoot = (root << 1) + 1;
        ll rRoot = (root << 1) + 2;
        if (pos <= m) {
            set(lRoot, l, m, pos, val);
        } else {
            set(rRoot, m + 1, r, pos, val);
        }

        tree[root] = merge(tree[lRoot], tree[rRoot]);
    }

public:
    SegTree(ll sz, ll def = 0) : sz(sz), def(def) {
        tree.resize((1 << (__lg(sz) + 2)));
        build(0, 0, sz - 1);
    }

    SegTree(const vector<ll>& src, ll def = 0) : sz(ll(src.size())), def(def) {
        tree.resize((1 << (__lg(sz) + 2)));
        build(0, 0, sz - 1, src);
    }

    ll getMx(ll l, ll r) {
        checkBorders(l, r);
        return get(0, 0, sz - 1, l, r).mx;
    }

    ll getMn(ll l, ll r) {
        checkBorders(l, r);
        return get(0, 0, sz - 1, l, r).mn;
    }

    ll getSum(ll l, ll r) {
        checkBorders(l, r);
        return get(0, 0, sz - 1, l, r).sum;
    }

    ll getVal(ll pos) {
        checkBorders(pos);
        return getVal(0, 0, sz - 1, pos).sum;
    }

    void add(ll l, ll r, ll val) {
        checkBorders(l, r);
        add(0, 0, sz - 1, l, r, val);
    }

    void add(ll pos, ll val) {
        checkBorders(pos);
        add(pos, pos, val);
    }

    void set(ll pos, ll val) {
        checkBorders(pos);
        set(0, 0, sz - 1, pos, val);
    }
};
