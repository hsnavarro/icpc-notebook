// Dinic - O(n^2 * m)
// Max flow


const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct edge { int v, c, f; };

int n, s, t, h[N], st[N];
vector<edge> edgs;
vector<int> g[N];

// directed from u to v with cap(u, v) = c
void add_edge(int u, int v, int c) {
  int k = edgs.size();
  edgs.push_back({v, c, 0});
  edgs.push_back({u, 0, 0});
  g[u].push_back(k);
  g[v].push_back(k+1);
}

int bfs() {
  memset(h, 0, sizeof h);
  h[s] = 1;
  queue<int> q;
  q.push(s);
  while(q.size()) {
    int u = q.front(); q.pop();
    for(auto i : g[u]) {
      int v = edgs[i].v;
      if(!h[v] and edgs[i].f < edgs[i].c)
        h[v] = h[u] + 1, q.push(v);
    }
  }
  return h[t];
}

int dfs(int u, int flow) {
  if(!flow or u == t) return flow;
  for(int &i = st[u]; i < g[u].size(); i++) {
    edge &dir = edgs[g[u][i]], &rev = edgs[g[u][i]^1];
    int v = dir.v;
    if(h[v] != h[u] + 1) continue;
    int inc = min(flow, dir.c - dir.f);
    inc = dfs(v, inc);
    if(inc) {
      dir.f += inc, rev.f -= inc;
      return inc;
    }
  }
  return 0;
}

int dinic() {
  int flow = 0;
  while(bfs()) {
    memset(st, 0, sizeof st);
    while(int inc = dfs(s, INF)) flow += inc;
  }
  return flow;
}
