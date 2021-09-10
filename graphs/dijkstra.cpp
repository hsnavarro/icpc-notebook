// Dijkstra - O((V+E)logE)

int dist[N];
vector<pii> adj[N];
priority_queue<pii> pq;

void dijkstra(int s){
    cl(dist, 63);
    dist[s] = 0;
    pq.push({0, s});
    while(!pq.empty()){
        int ud = -pq.top().st;
        int u = pq.top().nd;
        pq.pop();
        if(dist[u] < ud) continue;
        for(auto x : adj[u]){
            int v = x.st;
            int w = x.nd;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({-dist[v], v});
            }
        }
    }
}
