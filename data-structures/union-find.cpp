//Union-Find
//Union and Find - O(alpha n)

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
