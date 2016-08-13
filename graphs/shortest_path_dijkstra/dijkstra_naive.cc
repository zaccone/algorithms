#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>

/* Naive implementation of Dij shortest path algorithm */

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
    int source;
    vector<list<Vertex>> vertexes;
    vector<int> dist;
    vector<bool> visited;

    Graph(int v,int source): V(v), source(source) {
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

    int minDistance() {
        int candidate_dist = INF;
        int bestIdx;
        for(int i = 1; i <= V; i++) {
            if(visited[i] == false && candidate_dist > dist[i]) {
                bestIdx = i;
                candidate_dist = dist[i];
            }
        }
        return bestIdx;
    }

    void shortestPath() {
        for(int v = 1; v < V; v++) {
            int u = minDistance();
            visited[u] = true;

            for(auto neighbor : vertexes[u]) {
                if(visited[neighbor.v])
                    continue;

                if(dist[u] != INF && dist[u] + neighbor.weight < dist[neighbor.v]) {
                    dist[neighbor.v] = dist[u] + neighbor.weight;
                }
            }
        }
    }
};

int main() {

    ifstream ifs("./input.txt", ifstream::in);
    Graph * graph = new Graph(VERTEXES, 1);
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
    delete graph;
    return 0;

}
