#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;

static const int VCOUNT = 200;

struct Edge {
    int src;
    int dst;
    Edge(int s, int d): src(s), dst(d) {};
};

class Graph {

    public:
        const int V = VCOUNT;
        int E;
        vector<Edge> edges;
        Graph(): E(0) {};
        void addEdge(int s, int d) {

            edges.push_back(Edge(s,d));
            E++;
        }
        vector<Edge> & getEdges() {return edges; }

};

struct Subset {
    int parent;
    int rank;
};

int find(vector<Subset> & subsets, int i) {
    if(subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void Union(vector<Subset> & subsets, int s1, int s2) {
    int s1parent = find(subsets, s1);
    int s2parent = find(subsets, s2);
    if(subsets[s1parent].rank < subsets[s2parent].rank) {
        subsets[s1parent].parent = s2parent;
    } else if(subsets[s2parent].rank < subsets[s1parent].rank) {
        subsets[s2parent].parent = s1parent;
    } else {
        subsets[s1parent].parent = s2parent;
        subsets[s2parent].rank++;
    }
}


int minCut(Graph & graph) {
    auto & edges = graph.getEdges();
    int V = graph.V;
    int E = edges.size();

    vector<Subset> subsets(V+1);
    for(int i = 1;i<=V;i++) {
        subsets[i].rank = 0;
        subsets[i].parent = i;
    }


    while(V > 2) {
        int i = rand() % E;

        //cout << "Wylosowano: " << i << endl;
        int s1 = find(subsets, edges[i].src);
        int s2 = find(subsets, edges[i].dst);

        if(s1 == s2)
            continue;
        Union(subsets, s1, s2);
        V--;
    }
    int mincut = 0;
    for(int i = 0; i < E; i++) {
        int s1 = find(subsets, edges[i].src);
        int s2 = find(subsets, edges[i].dst);

        if(s1 == s2)
            continue;
        mincut++;
    }
    return mincut;
}

int main() {
    Graph graph;
    ifstream ifs("./karger.txt", ifstream::in);

    string token;
    for(string line; getline(ifs, line);) {
        istringstream ss(line);
        std::getline(ss, token, ' ');
        int src = std::stoi(token);
        while(std::getline(ss,token, ' ')) {
            int dst = std::stoi(token);
            graph.addEdge(src,dst);
        }

    }

    int best = 200*200 + 1;

    srand(time(NULL));
    for(int i = 0; i < 1000; i++) {

        best = min(best, minCut(graph));
    }

    cout << "Min cut: " << best/2 << endl;

    return 0;

}
