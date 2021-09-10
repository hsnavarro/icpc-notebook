// Shortest Path Faster Algoritm O(VE)

int n, inq[N], dist[N];
vector<pair<int, int>> adj[N];

void spfa(int s) {
  memset(dist, 63, sizeof dist);
  queue<int> q;
  dist[s] = 0;
  q.push(s), inq[s] = 1;
  while(q.size()) {
    int u = q.front(); q.pop(); inq[u] = 0;
    for(auto x : adj[u]) {
      int v = x.st;
      int w = x.nd;
      if(dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          if(!inq[v]) q.push(v), inq[v] = 1;
      }
    }
  }
}
