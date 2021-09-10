// Khun (Maximum Bipartite Matching) - O(VE)

int n, cnt, vis[N], match[N], ans;
vector<int> adj[N];

bool find(int u){
  if(vis[u] == cnt) return false;
  vis[u] = cnt;
  for(auto v : adj[u]) if(!match[v] or find(match[v])) return match[v] = u;
  return false;
}

// Maximum Independent Set on bipartite graph
// MIS  = V - MATCH

// Minimum Vertex Cover  
// MVC = MATCH

// Minimum Path Cover on DAG
// MPC = V - MATCH

// TIP: If you don't know the sides of the bipartite graph, 
// run kuhn for all nodes and match = ans/2;

// in main (only for one of the sides)
for(int i = 1; i <= n; i++) ++cnt, ans += find(i);
