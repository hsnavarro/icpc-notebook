#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m;
int a, b;

vector<int> adj[N];
int vis[N];
int par[N];

vector<int> cycle;

void dfs(int u, int p) {
  vis[u] = 1;
  par[u] = p;

  for (auto v : adj[u]) if (cycle.empty() and vis[v] != 2) {
    if (vis[v] == 1) {
      cycle.push_back(v);

      for (int x = u; x != v; x = par[x]) {
        cycle.push_back(x);
      }

      cycle.push_back(v);
      reverse(cycle.begin(), cycle.end());
    } else dfs(v, u);
  }

  vis[u] = 2;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  while (m--) {
    cin >> a >> b;
    adj[a].push_back(b);
  }

  for (int i = 1; i <= n; i++) if (!vis[i]) {
    dfs(i, -1);
  }

  if (cycle.empty()) {
    cout << "IMPOSSIBLE\n";
  } else {
    cout << cycle.size() << "\n";
    for (auto v : cycle) cout << v << " ";
    cout << "\n";
  }
}
