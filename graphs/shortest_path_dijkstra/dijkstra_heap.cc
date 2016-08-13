#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

static const int VERTEXES = 200;
static const int INF = 1000000;


struct Vertex {
    int v;
    int weight;

    Vertex(int w, int v) {
        this->v = v;
        this->weight = w;
    }
};

struct Graph {
    int V;
    int source
    vector<list<Vertex>> vertexes;
    vector<int> dist;
    vector<bool> visited;
    priority_queue<pair<int,int>, vector<pair<int,int>> , greater<pair<int,int>>> q;

    Graph(int v, int source): V(v), source(source) {
        vertexes.resize(v+1);
        dist.resize(v+1, INF);
        visited.resize(v+1, false);
        dist[source] = 0;
        visited[0] = true;
    }

    void addEdge(int s, int e, int w) {
        vertexes[s].push_back(Vertex(w,e));
        vertexes[e].push_back(Vertex(w,s));
    }

    void shortestPath() {

        q.push(pair<int,int>(0,source));
        while(q.size()) {
            pair<int,int> vertex = q.top(); q.pop();
            int u = vertex.second;
            for(auto neigh: vertexes[u]) {
                if(neigh.weight + dist[u] < dist[neigh.v]) {
                    dist[neigh.v] = dist[u] + neigh.weight;
                    q.push(pair<int,int>(dist[neigh.v], neigh.v));
                }
            }
        }
    }
};

int main() {

    ifstream ifs("./input.txt", ifstream::in);
    Graph * graph = new Graph(VERTEXES);
    string token;
    string srcStr, dstStr, weightStr;
    for(string line; getline(ifs, line);) {
        istringstream ss(line);


        std::getline(ss, srcStr, '\t');
        int src = stoi(srcStr);
        while(std::getline(ss, token, '\t')) {
            istringstream sline(token);
            std::getline(sline, dstStr, ',');
            std::getline(sline, weightStr, ',');
            graph->addEdge(src, stoi(dstStr), stoi(weightStr));
        }
    }

    graph->shortestPath();
    for(auto i: graph->dist) {
        cout << i << endl;
    }
    cout << endl;
    return 0;

}
