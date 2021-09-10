const int SIZE = 1e9;

// const int M = Q log SIZE_INTERVAL; 

const int M = 1e7 + 5;

int cnt, st[M], lc[M], rc[M];

int id(int x) { return !x ? ++cnt : x; }

void update(int idx, int val, int p = 0, int l = 1, int r = SIZE) {
  if (l == r) { st[p] += val; return; }

  lc[p] = id(lc[p]);
  rc[p] = id(rc[p]);

  int mid = (l + r) / 2;
  if (idx <= mid) update(idx, val, lc[p], l, mid);
  else update(idx, val, rc[p], mid + 1, r);

  st[p] = st[lc[p]] + st[rc[p]];
}

int query(int i, int j, int p = 0, int l = 1, int r = SIZE) {
  if (r < i or j < l) return 0ll;
  if (i <= l and r <= j) return st[p];
  int mid = (l + r) / 2;
  lc[p] = id(lc[p]);
  rc[p] = id(rc[p]);

  return query(i, j, lc[p], l, mid) + query(i, j, rc[p], mid + 1, r);
}
