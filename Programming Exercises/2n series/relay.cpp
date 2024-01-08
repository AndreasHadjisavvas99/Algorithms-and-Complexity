#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <tuple>
#include <climits>

#define BSIZE 1 << 15
#define INF ULLONG_MAX

using namespace std;

class Node {
public:
    int vertex;
    unsigned long long int weight;

    Node(int _vertex, unsigned long long int _weight) : vertex(_vertex), weight(_weight) {}
};

class Graph {
    int V;
    list<Node>* adj;
    vector<int> paths;
    vector<tuple<int, int>> costs;

    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);

public:
    Graph(int V);
    ~Graph();

    void addEdge(int u, int v, unsigned long long int weight);
    void addCost(int p, int s);
    void shortestPath(int s);
    void printAdj();
    void printPaths();
    void printCosts();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<Node>[V];
    paths.reserve(V);
    costs.reserve(V - 1);
}

Graph::~Graph() {
    delete[] adj;
}

void Graph::addEdge(int u, int v, unsigned long long int weight) {
    Node node(v, weight);
    adj[u].push_back(node);
    paths[v] = u;
}

void Graph::addCost(int p, int s) {
    costs.push_back(tuple<int, int>(p, s));
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack) {
    visited[v] = true;

    for (const auto& node : adj[v]) {
        if (!visited[node.vertex]) {
            topologicalSortUtil(node.vertex, visited, Stack);
        }
    }

    Stack.push(v);
}

void Graph::shortestPath(int s) {
    stack<int> Stack, Helpstack;
    vector<unsigned long long int> dist(V);
    vector<unsigned long long int> atleast(V);
    vector<unsigned long long int> mins(V);

    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            topologicalSortUtil(i, visited, Stack);
        }
    }

    for (int i = 0; i < V; i++)
        dist[i] = INF;

    dist[s] = 0;
    atleast[s] = 0;
    mins[0] = 0;

    Helpstack = Stack;

    while (Stack.empty() == false) {
        int u = Stack.top();
        Stack.pop();

        list<Node>::iterator i;
        if (dist[u] != INF) {
            for (const auto& node : adj[u]) {
                if (dist[node.vertex] > dist[u] + node.weight)
                    dist[node.vertex] = dist[u] + node.weight;
            }
        }
    }

    for (int i = 0; i < V - 1; i++) {
        atleast[i + 1] = get<0>(costs[i]) + dist[i + 1] * get<1>(costs[i]);
    }

    Helpstack.pop();

    while (Helpstack.empty() == false) {
        int u = Helpstack.top();
        Helpstack.pop();

        unsigned long long int minimum = atleast[u];
        int current = paths[u];

        while (current != 0) {
            minimum = min(minimum, atleast[u] - dist[current] * get<1>(costs[u - 1]) + mins[current]);
            current = paths[current];
        }
        mins[u] = minimum;
    }

    cout << mins[1];
    for (int i = 2; i < V; i++)
        cout << " " << mins[i];
    cout << endl;

    delete[] visited;
}

void Graph::printAdj() {
    for (int v = 0; v < V; v++) {
        cout << v << " -> ";
        for (const auto& node : adj[v]) {
            cout << node.vertex << " ";
        }
        cout << endl;
    }
}

void Graph::printPaths() {
    for (int v = 0; v < V; v++) {
        cout << v << " -> " << paths[v] << endl;
    }
}

void Graph::printCosts() {
    for (const auto& tuple : costs) {
        cout << get<0>(tuple) << " " << get<1>(tuple) << endl;
    }
}

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong() {
    long d = 0L, x = 0L;
    char c;

    while (1) {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin))
                return x;
            bsize = fread(buffer, 1, BSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            d = 1;
        } else if (d == 1)
            return x;
    }
    return -1;
}

int main() {
    int N = readLong();

    int s = 0;

    if (N <= 8000) {
        Graph g(N);

        for (int i = 0; i < N - 1; i++) {
            int node1 = readLong();
            int node2 = readLong();
            unsigned long long int distance = readLong();
            (node1 < node2) ? g.addEdge(node1 - 1, node2 - 1, distance) : g.addEdge(node2 - 1, node1 - 1, distance);
        }

        for (int i = 0; i < N - 1; i++) {
            int p = readLong();
            int s = readLong();
            g.addCost(p, s);
        }

        g.shortestPath(s);
    } else {
        Graph l(N);

        for (int i = 0; i < N - 1; i++) {
            int node1 = readLong();
            int node2 = readLong();
            unsigned long long int distance = readLong();
            l.addEdge(node1 - 1, node2 - 1, distance);
        }

        for (int i = 0; i < N - 1; i++) {
            int p = readLong();
            int s = readLong();
            l.addCost(p, s);
        }

        l.shortestPath(s);
    }

    return 0;
}
