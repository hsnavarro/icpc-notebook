// Centroid Decomposition - O(nlog n)
int n, m, sz[N], forb[N], par[N];

void dfs(int u, int p) {
  sz[u] = 1;
  for(auto v : adj[u]) {
    if(v != p and !forb[v]) {
      dfs(v, u);
      sz[u] += sz[v];
    }
  }
}

int cent(int u, int p, int amt) {
  for(auto v : adj[u]) {
    if(v == p or forb[v]) continue;
    if(sz[v] > amt/2) return cent(v, u, amt);
  }
  return u;
}

void decomp(int u, int p) {
  dfs(u, -1);
  int cen = cent(u, -1, sz[u]);
  forb[cen] = 1;
  if(p != -1) par[cen] = p;

  for(auto v : adj[u]) 
    if(!forb[v]) decomp(v, cen);
}

// in main
// decomp(1, -1);
