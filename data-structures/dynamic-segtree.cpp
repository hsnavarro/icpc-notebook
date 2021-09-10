const int SIZE = 1e9;

// const int M = Q log SIZE_INTERVAL; 

const int M = 1e7 + 5;

int cnt, st[M], lz[M], lc[M], rc[M];

int id(int x) { return !x ? ++cnt : x; }

void push(int p, int l, int r) {
  if (lz[p]) {

    st[p] += (r - l + 1) * lz[p];

    if (l != r) {
      lc[p] = id(lc[p]);
      rc[p] = id(rc[p]);

      lz[lc[p]] += lz[p];
      lz[rc[p]] += lz[p];
    }

    lz[p] = 0;
  }
}

void update(int i, int j, int x, int p = 0, int l = 1, int r = SIZE) {
  push(p, l, r);
  if (r < i or l > j) return;
  if (i <= l and r <= j) { lz[p] = x, push(p, l, r); return; }
  int mid = (l + r) / 2;
  lc[p] = id(lc[p]);
  rc[p] = id(rc[p]);

  update(i, j, x, lc[p], l, mid);
  update(i, j, x, rc[p], mid + 1, r);

  st[p] = st[lc[p]] + st[rc[p]];
}

int query(int i, int j, int p = 0, int l = 1, int r = SIZE) {
  push(p, l, r);
  if (r < i or l > j) return 0;
  if (i <= l and r <= j) return st[p];
  int mid = (l + r) / 2;
  lc[p] = id(lc[p]);
  rc[p] = id(rc[p]);

  return query(i, j, lc[p], l, mid) + query(i, j, rc[p], mid + 1, r);
}
