// Depth First Search O(V+E)

const int N = 1e5 + 5;

int vis[N];
vector<int> adj[N];

void dfs(int x){
    vis[x] = 1;
    for(auto u : adj[x]) if(!vis[u]) dfs(u);
}
