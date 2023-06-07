/**
 * Realization of Least Common Ancestor algorithm (LCA) in C++, using BinUps technique.
 *
 * TIME: O(V*log(V) + Q * log(V))
 * Memory: V * log(V)
 *
 * (V == MAX_N)
 *
 * @author Kirill_Maglysh
*/

#include <vector>

using namespace std;

class LCA {
private:
    int V;
    int LOG;
    vector<vector<int>> up;
    vector<int> tin;
    vector<int> tout;
    vector<vector<int>> graph;
    int timer = 0;

    void buildDfs(int from, int p) {
        tin[from] = ++timer;
        up[0][from] = p;
        for (int lvl = 1; lvl < LOG; ++lvl) {
            up[lvl][from] = up[lvl - 1][up[lvl - 1][from]];
        }

        for (auto& to : graph[from]) {
            if (to == p) {
                continue;
            }

            buildDfs(to, from);
        }

        tout[from] = ++timer;
    }

public:
    explicit LCA(const vector<vector<int>>& graph, int root = 0) :
            V(int(graph.size())), LOG(__lg(V) + 1), graph(graph) {
        up.resize(LOG, vector<int>(V));
        tin.resize(V);
        tout.resize(V);
        up.resize(LOG, vector<int>(V));
        buildDfs(root, root);
    }

    bool isParent(int kid, int par) {
        return tin[par] <= tin[kid] && tout[par] >= tout[kid];
    }

    int lca(int v, int u) {
        if (isParent(u, v)) {
            return v;
        }

        if (isParent(v, u)) {
            return u;
        }

        for (int lvl = LOG - 1; lvl >= 0; --lvl) {
            if (!isParent(u, up[lvl][v])) {
                v = up[lvl][v];
            }
        }

        return up[0][v];
    }
};
