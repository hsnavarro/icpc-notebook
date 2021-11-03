//Union-Find
//Union and Find - O(alpha n)

struct UnionFind {
  vector<int> par, sz;

  UnionFind(int _n) : par(_n + 1), sz(_n + 1, 1) {
    for (int i = 0; i <= _n; i++) par[i] = i;
  }

  int find(int a) { return a == par[a] ? a : par[a] = find(par[a]); }

  void unite(int a, int b) {
    if ((a = find(a)) == (b = find(b))) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
  }
};
