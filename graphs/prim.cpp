// Prim - MST O(ElogE)

int cost, vis[N];
vector<pii> adj[N];
priority_queue<pii> pq;

void prim(int s = 1){
    pq.push({0, s});
    while(!pq.empty()){
        int ud = -pq.top().st;
        int u = pq.top().nd;
        pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        cost += ud;
        for(auto x : adj[u]){
            int v = x.st;
            int w = x.nd;
            if(!vis[v]) pq.push({-w, v});
        }
    }
}
