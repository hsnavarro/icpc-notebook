// Heavy-Light Decomposition
// Query and Update Path - O(log^2 n)
// Query and Update Node - O(log n)

struct HLD {
  vector<int> heavy, par, h, head, pos, sz;
  int cur_pos = 0;

  SegTree<Node, int> st;

  HLD(vector<vector<int>>& adj) {
    int n = (int)adj.size();
    heavy = vector<int>(n, -1);
    par = vector<int>(n);
    h = vector<int>(n);
    head = vector<int>(n);
    pos = vector<int>(n);
    sz = vector<int>(n);

    st = SegTree<Node, int>(n);

    dfs(0, adj);
    decomp(0, 0, adj);
  }

  void dfs(int u, vector<vector<int>>& adj) {
    sz[u] = 1;
    int mx_sz = 0;
    for (int v : adj[u]) {
      if (v == par[u]) continue;
      par[v] = u, h[v] = h[u] + 1;
      dfs(v, adj);
      sz[u] += sz[v];
      if (sz[v] > mx_sz) mx_sz = sz[v], heavy[u] = v;
    }
  }

  void decomp(int u, int hd, vector<vector<int>>& adj) {
    head[u] = hd, pos[u] = cur_pos++;
    if (heavy[u] != -1) decomp(heavy[u], hd, adj);
    for (int v : adj[u]) if (v != par[u] and v != heavy[u]) decomp(v, v, adj);
  }

  Node query(int u, int v) {
    Node ans;
    for (; head[u] != head[v]; v = par[head[v]]) {
      if (h[head[u]] > h[head[v]]) swap(u, v);
      ans = Node(ans, st.query(pos[head[v]], pos[v]));
    }

    if (h[u] > h[v]) swap(u, v);
    ans = Node(ans, st.query(pos[u], pos[v]));
    return ans;
  }

  void update(int u, int v) {
    st.update(pos[u], v);
  }
};