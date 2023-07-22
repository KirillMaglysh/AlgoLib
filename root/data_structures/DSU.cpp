/**
 * Realization of Disjoint Set Union data structure in C++.
 *
 * TIME: O(N) building + O(A) ask, where A is inverse ackerman function
 * Memory: N
 *
 * @author Kirill_Maglysh
*/

#include <vector>

using namespace std;

class DSU {
private:
    vector<int> szs;
    vector<int> parents;

public:
    explicit DSU(int sz) {
        szs.resize(sz, 1);
        parents.resize(sz);
        for (int i = 0; i < sz; ++i) {
            parents[i] = i;
        }
    }

    int getRoot(int v) {
        int root = v;
        while (parents[root] != root) {
            root = parents[root];
        }

        while (v != root) {
            int kid = v;
            v = parents[v];
            parents[kid] = root;
        }

        return root;
    }

    bool unite(int v, int u) {
        v = getRoot(v);
        u = getRoot(u);
        if (v == u) {
            return false;
        }

        if (szs[v] < szs[u]) {
            swap(v, u);
        }

        szs[v] += szs[u];
        parents[u] = v;
        return true;
    }
};
