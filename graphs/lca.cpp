// Lowest Common Ancestor - <O(nlog n), O(log n)>

const int N = 1e6;
const int M = 25; //m = log N

int anc[M][N], h[N], rt;
vector<int> adj[N];

void dfs(int x = rt, int p = -1, int ht = 0){
  anc[0][x] = p, h[x] = ht;
  for(auto v : adj[x]) if(v != p) dfs(v, x, ht+1);
}

void build(){
  dfs(), anc[0][rt] = rt;

  for(int j = 1; j < M; j++)
    for(int i = 1; i <= n; i++) // 1-indexed
      anc[j][i] = anc[j-1][anc[j-1][i]];
}

int lca(int u, int v){
  if(h[u] < h[v]) swap(u, v);
  for(int i = M-1; i >= 0; i--) if(h[u] - (1<<i) >= h[v]) u = anc[i][u];
  
  if(u == v) return u;
  for(int i = M-1; i >= 0; i--) if(anc[i][u] != anc[i][v])
    u = anc[i][u], v = anc[i][v];

  return anc[0][u];
}
