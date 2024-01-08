#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define BSIZE 1<<15

using namespace std;

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong() {
    long d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
        else if (d == 1) return x;
    }
    return -1;
}

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

struct Edge {
    int u, v;
    long long p, w;
    double weight;

    Edge(int u, int v, long long p, long long w) : u(u), v(v), p(p), w(w), weight(0) {}
};

struct UnionFind {
    vector<int> parent, rank;

    UnionFind(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x]) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;

        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
        return true;
    }
};

pair<long long, long long> calculateMST(int n, vector<Edge>& edgeList) {
    UnionFind uf(n + 1);
    long long totalCost = 0, totalWeight = 0;

    for (const Edge& edge : edgeList) {
        if (uf.unite(edge.u, edge.v)) {
            totalCost += edge.p;
            totalWeight += edge.w;
        }
    }

    long long gcdVal = gcd(totalCost, totalWeight);
    return {totalCost / gcdVal, totalWeight / gcdVal};
}

pair<long long, long long> findMaxRatioMST(int n, vector<Edge>& edgeList) {
    double low = 0, high = 1e9;
    pair<long long, long long> result;

    while (high - low > 1e-6) {
        double mid = (low + high) / 2;
        for (auto& edge : edgeList) {
            edge.weight = edge.p - mid * edge.w;
        }

        sort(edgeList.begin(), edgeList.end(), [](const Edge& a, const Edge& b) {
            return a.weight > b.weight;
        });

        pair<long long, long long> mstResult = calculateMST(n, edgeList);
        long long profit = mstResult.first;
        long long weight = mstResult.second;

        if (profit > mid * weight) {
            low = mid;
            result.first = profit;
            result.second = weight;
        } else {
            high = mid;
        }
    }

    long long gcdVal = gcd(result.first, result.second);
    return make_pair(result.first / gcdVal, result.second / gcdVal);
}

int main() {
    int N = readLong();
    int M = readLong();
    vector<Edge> edgeList;

    for (int i = 0; i < M; ++i) {
        int u = readLong();
        int v = readLong();
        long long p = readLong();
        long long w = readLong();
        edgeList.emplace_back(u, v, p, w);
    }

    pair<long long, long long> maxRatioResult = findMaxRatioMST(N, edgeList);
    long long maxProfit = maxRatioResult.first;
    long long maxWeight = maxRatioResult.second;

    cout << maxProfit << " " << maxWeight << endl;

    return 0;
}
