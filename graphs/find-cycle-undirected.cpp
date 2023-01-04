#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, a, b;
vector<int> adj[N];
bool vis[N];
int par[N];
vector<int> cycle;

void dfs(int u = 1, int p = -1) {
  vis[u] = true;
  par[u] = p;

  for (auto v : adj[u]) if (cycle.empty() and v != p) {
    if (vis[v]) {
      cycle.push_back(v);
      for (int x = u; x != v; x = par[x])  {
        cycle.push_back(x);
      }

      cycle.push_back(v);

    } else dfs(v, u);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  while (m--) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i, -1);

  if (!cycle.size()) {
    cout << "IMPOSSIBLE\n";
  } else {
    cout << cycle.size() << "\n";
    for (auto x : cycle) cout << x << " ";
    cout << "\n";
  }
}
