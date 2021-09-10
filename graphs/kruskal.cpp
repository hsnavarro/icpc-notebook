// Kruskal - MST O(ElogE)

// + Union-Find
/////////////////////////////////////////////
int par[N], sz[N];

//Path Compression
int find(int a) { return a == par[a] ? a : par[a] = find(par[a]); }

//Ranking
void unite(int a, int b){
    if(find(a) == find(b)) return;
    a = find(a), b = find(b);
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b], par[b] = a;
}

//in main
for(int i = 0; i < N; i++) par[i] = i, sz[i] = 1;
//////////////////////////////////////////////

vector<piii> edges;
// dist, node1, node2

sort(edges.begin(), edges.end());
int cost = 0;
for(auto e : edges) if(find(e.nd.st) != find(e.nd.nd)){
    cost += e.st, unite(e.nd.st, e.nd.nd);
}
