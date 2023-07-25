/**
 * Realization of Dijkstra algorithm in C++.
 * Algorithm finds values of the shortest paths from the one vertex to all other AND
 * a path (vector of vertexes) from start to finish.
 *
 * TIME: O(V*logE)
 * Memory: O(V)
 *
 * @author Kirill_Maglysh
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using ll = long long;

const ll INF18 = 1e18;
class Dijkstra {
private:
    int V;
    bool directed;
    vector<vector<pair<int, ll>>> graph;

public:
    explicit Dijkstra(int V, bool directed = false) : V(V), directed(directed) {
        graph.resize(V);
    }

    explicit Dijkstra(vector<vector<pair<int, ll>>> graph, bool directed = false) : graph(std::move(graph)),
                                                                                    V(int(graph.size())),
                                                                                    directed(directed) {}

    void addEdge(int v, int u, ll weight) {
        graph[v].emplace_back(u, weight);
        if (!directed) {
            graph[u].emplace_back(v, weight);
        }
    }

    vector<ll> shortestDistsFrom(int start) {
        vector<ll> dist(V, INF18);
        vector<bool> used(V, false);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

        dist[start] = 0;
        pq.emplace(0, start);
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            used[u] = true;

            for (auto& edge : graph[u]) {
                int v = edge.first;
                ll weight = edge.second;

                if (!used[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        return dist;
    }

    pair<ll, vector<int>> shortestPathFrom(int start, int finish) {
        vector<ll> dist(V, INF18);
        vector<bool> used(V, false);
        vector<int> parents(V, -1);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

        dist[start] = 0;
        pq.emplace(0, start);
        while (!pq.empty()) {
            int from = pq.top().second;
            pq.pop();

            used[from] = true;

            for (auto& edge : graph[from]) {
                int to = edge.first;
                ll weight = edge.second;

                if (!used[to] && dist[from] + weight < dist[to]) {
                    dist[to] = dist[from] + weight;
                    parents[to] = from;
                    pq.emplace(dist[to], to);
                }
            }
        }

        if (dist[finish] == INF18) {
            return {-1, {}};
        }

        int cur = finish;
        vector<int> path;
        path.push_back(finish);
        while (cur != start) {
            cur = parents[cur];
            path.push_back(cur);
        }

        reverse(path.begin(), path.end());
        return {dist[finish], path};
    }
};
