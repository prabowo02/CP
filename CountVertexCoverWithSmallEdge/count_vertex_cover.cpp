const int N = 64;

int n = N; // number of vertex
vector<int> edges[N]; // adjacency list

// Given a set of vertices, find the connected component where u belongs to it
long long bfs(int u, long long vertices) {
    long long vis = 1LL << u;
    queue<int> q;
    q.push(u);

    while (q.size()) {
        int u = q.front();
        q.pop();

        for (int v: edges[u]) {
            if (vertices >> v & 1); else continue;
            if (vis >> v & 1) continue;

            q.push(v);
            vis |= 1LL << v;
        }
    }

    return vis;
}

map<long long, unsigned long long> dp; // for memoization
// `vertices` is a set of vertex where the i-th bit is on if and only if the i-th vertex belongs to the set.
unsigned long long count_vertex_cover(long long vertices) {
    if (__builtin_popcountll(vertices) == 0) return 1; // Graph is empty, only one solution
    if (__builtin_popcountll(vertices) == 1) return 2; // Graph has only one vertex, obviously two solutions

    if (dp.find(vertices) != dp.end()) return dp[vertices];

    vector<long long> components;
    long long vis = 0;
    for (int i=0; i<n; i++) {
        if (vertices >> i & 1); else continue;
        if (vis >> i & 1) continue;

        components.push_back(bfs(i, vertices));
        vis |= components.back();
    }

    // graph is disconnected
    if (components.size() > 1) {
        unsigned long long ret = 1;
        for (long long component: components) {
            ret *= count_vertex_cover(component);
        }

        return dp[vertices] = ret;
    }

    int max_degree = -1;
    vector<int> heavy_vertices;

    for (int i=0; i<n; i++) {
        if (vertices >> i & 1); else continue;

        int degree = 0;
        for (int v: edges[i]) {
            if (vertices >> v & 1) ++degree;
        }

        if (degree > max_degree) {
            heavy_vertices = {i};
            max_degree = degree;
        } else if (degree == max_degree) {
            heavy_vertices.push_back(i);
        }
    }

    int heavy = heavy_vertices[rand() % heavy_vertices.size()];
    long long neighbor = 1LL << heavy;
    for (int v: edges[heavy]) if (vertices >> v & 1) neighbor |= 1LL << v;

    return dp[vertices] = 
        count_vertex_cover(vertices & ~(1LL << heavy)) + // heavy is in vertex_cover
        count_vertex_cover(vertices & ~neighbor); // heavy is not in vertex_cover
}
