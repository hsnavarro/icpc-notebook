// Tarjan for SCC and Edge Biconnected Componentes - O(n + m)

vector<int> adj[N], st;
int num[N], low[N], vis[N], cnt, scc[N], sccn = 1;

void dfs(int u, int p) {
  num[u] = low[u] = ++cnt;
  st.push_back(u), vis[u] = 1;

  for(auto v : adj[u]) {
    if (!num[v]) dfs(v, u);
    // Uncomment below for biconnected components.
    if (vis[v]/* and v != p*/) low[u] = min(low[u], low[v]);
  }

  if (low[u] == num[u]) while(1) {
      int v = st.back(); st.pop_back();
      scc[v] = sccn, vis[v] = 0;
      if (v == u) { sccn++; break; }
  }
}

void tarjan(int n) { for(int i = 1; i <= n; i++) if (!num[i]) dfs(i, -1); }
