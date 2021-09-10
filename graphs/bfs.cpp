// Breadth First Search O(V+E)

const int N = 1e5 + 5;

int vis[N];
vector<int> adj[N];
queue<int> q;

void bfs(int x){
    vis[x] = 1;
    q.push(x);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto v : adj[u]) if(!vis[v]) {
          vis[v] = 1, q.push(v);
        }
    }
}
