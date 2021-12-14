// Centroid Decomposition - O(nlog n)
int n, sz[N], forb[N], par[N];
vector<int> adj[N];

int get_sz(int u, int p = -1) {
  sz[u] = 1;
  for(int v : adj[u])
    if(v != p and !forb[v]) sz[u] += get_sz(v, u);
  
  return sz[u];
}

int cent(int amt, int u, int p = -1) {
  for(int v : adj[u]) {
    if(v == p or forb[v]) continue;
    if(sz[v] > amt/2) return cent(amt, v, u);
  }
  return u;
}

void decomp(int u = 1, int p = -1) {
  int cen = cent(get_sz(u), u);
  forb[cen] = 1;
  if(p != -1) par[cen] = p;

  for(int v : adj[u]) 
    if(!forb[v]) decomp(v, cen);
}

// in main
decomp();
