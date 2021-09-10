int c[N], cnt[N], sub[N], id[N], rev[N], ans, ord, q[N];
vector<int> adj[N];

void dfs(int u = 1, int p = -1) {
  id[u] = ++ord;
  rev[ord] = u;

  sub[u]++;
  for(auto v : adj[u]) 
    if(v != p) {
      dfs(v, u);
      sub[u] += sub[v];
    }
}

void solve(int u = 1, int p = -1, int cl = 0) {

  int bigCh = -1, mx = -1;
  for(auto v : adj[u]) 
    if(v != p and sub[v] > mx) bigCh = v, mx = sub[v];

  for(auto v : adj[u]) 
    if(v != p and v != bigCh) solve(v, u, 1);

  if(bigCh != -1) solve(bigCh, u, 0);

  if(!cnt[c[u]]) ans++;
  cnt[c[u]]++;

  for(auto v : adj[u]) {
    if(v != p and v != bigCh) {
      for(int i = id[v]; i < id[v] + sub[v]; i++) {
        if(!cnt[c[rev[i]]]) ans++;
        cnt[c[rev[i]]]++;
      }
    }
  }

  q[u] = ans;

   if(cl) {
    for(int i = id[u]; i < id[u] + sub[u]; i++) {
      if(cnt[c[rev[i]]] == 1) ans--;
      cnt[c[rev[i]]]--;
    }
  }
}