#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <queue>

using namespace std;

struct Graph {
    int V;
    vector< vector<long> > vertex;
    Graph(int v) {
        V = v;
        vertex.resize(V+1);
    }
    void addEdge(long src, long dst) {
        vertex[src].push_back(dst);
    }
};

void dfs(Graph & g, long s, vector<bool> & visited, stack<long> &ts) {
    visited[s] = true;

    for(auto neigh : g.vertex[s]) {
        if(visited[neigh])
            continue;
        dfs(g,neigh, visited, ts);
    }
    ts.push(s);
}

void topological_sort(Graph & g) {
    vector<bool> visited(g.V + 1, false);
    stack<long> s;
    for(int i = 1; i <= g.V; i++) {
        if(visited[i])
            continue;
        dfs(g, i, visited, s);
    }

    cout << "Topological sort: " << endl;
    while(s.size()) {
        cout << s.top() << " ";
        s.pop();
    }
}

int main() {
    Graph g(5);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,4);
    g.addEdge(3,4);
    g.addEdge(1,5);
    g.addEdge(4,5);
    topological_sort(g);
    cout << endl;
    return 0;
}
