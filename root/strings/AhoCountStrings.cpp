/**
 * Realization of Aho-Corasick algorithm in C++.
 * Algorithm finds number of occurrences in the text for every string from vocabulary.
 *
 * TIME: O(a*|S|) for building, O(a*|T|+|S|) for counting
 * Memory: O(a*|S|)
 *
 * |S| - sum length of words in the vocabulary
 * |T| - length of the text
 * a - power of the alphabet
 *
 * <<!!WARNING>>
 *          YOU MUST CALL build() METHOD AFTER ADDING ALL THE WORDS
 * <<WARNING!!>>
 *
 * @author Kirill_Maglysh
*/

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int alpha = 26;

class Aho {
private:
    struct Vertex {
        Vertex *to[alpha] = {nullptr};
        Vertex *go[alpha] = {nullptr};
        Vertex *link = nullptr;
        Vertex *p;
        int cnt = 0;
        char pch;
        vector<int> ids;
        vector<Vertex *> linksFrom;

        explicit Vertex(char pch, Vertex *p) : pch(pch), p(p) {}
    };

    int cnt = 0;
    Vertex *tRoot = new Vertex(-1, nullptr);
    vector<ll> res;

    Vertex *link(Vertex *v) {
        if (!v->link) {
            if (v == tRoot || v->p == tRoot) {
                v->link = tRoot;
            } else {
                v->link = go(link(v->p), v->pch);
            }

            if (v != tRoot) {
                v->link->linksFrom.push_back(v);
            }
        }

        return v->link;
    }

    Vertex *go(Vertex *v, char c) {
        if (!v->go[c]) {
            if (v->to[c]) {
                v->go[c] = v->to[c];
            } else if (v == tRoot) {
                v->go[c] = tRoot;
            } else {
                v->go[c] = go(link(v), c);
            }
        }

        return v->go[c];
    }

    void buildLinks(Vertex *v) {
        link(v);
        for (const auto& nxt : v->to) {
            if (nxt) {
                buildLinks(nxt);
            }
        }
    }

    void dfsCalc(Vertex *v) {
        for (const auto& to : v->linksFrom) {
            if (to) {
                dfsCalc(to);
                v->cnt += to->cnt;
            }
        }

        for (const auto& id : v->ids) {
            res[id] = v->cnt;
        }
    }

public:
    void addWord(const string& word) {
        Vertex *v = tRoot;
        for (const auto& item : word) {
            char c = char(item - 'a');
            if (!v->to[c]) {
                v->to[c] = new Vertex(c, v);
            }

            v = v->to[c];
        }

        v->ids.push_back(cnt);
        ++cnt;
    }

    void build() {
        buildLinks(tRoot);
        res.resize(cnt);
    }

    vector<ll> countWords(const string& text) {
        Vertex *v = tRoot;
        for (const auto& item : text) {
            char c = char(item - 'a');
            v = go(v, c);
            ++v->cnt;
        }

        dfsCalc(tRoot);

        return res;
    }
};
