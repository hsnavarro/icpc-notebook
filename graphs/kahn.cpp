// Kahn - Topological Sort O(V + E)

const int N = 1e5+5;

vector<int> adj[N];
int n, in[N];

// For directed graph: in[x] == 0
// For undirected graph: in[x] <= 1

void kahn(){
  queue<int> q;
  for(int i = 1; i <= n; i++) if(!in[i]) q.push(i);

  while(q.size()){
    int u = q.front(); q.pop();
    for(auto x : adj[u]) if(in[x] and --in[x] == 0) q.push(x);
  }
}
