// Min Cost Max Flow - O(n^2 * m^2)

struct edge { int v, f, c, w; };

vector<int> g[N];
vector<edge> edgs;
int s, t, inq[N], p[N], dist[N];

void add_edge(int u, int v, int c, int w) {
  int k = edgs.size();
  g[u].push_back(k);
  g[v].push_back(k+1);
  edgs.push_back({v, 0, c, w});
  edgs.push_back({u, 0, 0, -w});
}

int spfa() {
  memset(dist, 63, sizeof dist);
  queue<int> q;
  dist[s] = 0;
  q.push(s), inq[s] = 1;
  while(q.size()) {
    int u = q.front(); q.pop(); inq[u] = 0;
    for(auto i : g[u]) {
      edge dir = edgs[i];
      int v = dir.v;
      int w = dir.w;
      if(dir.f < dir.c and dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        p[v] = i;
        if(!inq[v]) q.push(v), inq[v] = 1;
      }
    }
  }

  if(dist[t] == INF) return 0;

  int inc = INF;
  for(int u = t; u != s; u = edgs[p[u]^1].v) {
    edge &dir = edgs[p[u]];
    inc = min(inc, dir.c - dir.f);
  }

  int aux = 0;
  for(int u = t; u != s; u = edgs[p[u]^1].v) {
    edge &dir = edgs[p[u]], &rev = edgs[p[u]^1];
    dir.f += inc;
    rev.f -= inc;
    aux += inc*dir.w;
  }

  return aux;
}

int mcmf() {
  int cost = 0;
  while(int inc = spfa()) cost += inc;
  return cost;
}
