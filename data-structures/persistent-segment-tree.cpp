//Persistent Segment Tree
//Update and Query - O(log n)
//Space - O(n log n + q * log n)

//M -> n log n + q * log n

const int N = 2e5 + 5;

const int M = 1e7 + 5;

int n;
int st[M], lc[M], rc[M];
int cnt, v[N];

void init(int p = 0, int l = 1, int r = n) {
    if (l == r) { st[p] = v[l]; return; }

    int mid = (l + r) / 2;

    lc[p] = ++cnt;
    rc[p] = ++cnt;

    init(lc[p], l, mid);
    init(rc[p], mid + 1, r);

    st[p] = st[lc[p]] + st[rc[p]];
}

int query(int i, int j, int p, int l = 1, int r = n) {
    if (r < i or l > j) return 0;
    if (i <= l and r <= j) return st[p];

    int mid = (l + r) / 2;
    return query(i, j, lc[p], l, mid) + query(i, j, rc[p], mid + 1, r);
}

int update(int idx, int val, int p, int l = 1, int r = n) {
    int u = ++cnt;
    if (l == r) st[u] = val;
    else {
      int mid = (l + r) / 2;
      if (idx <= mid) {
        lc[u] = update(idx, val, lc[p], l, mid);
        rc[u] = rc[p];
      } else {
        lc[u] = lc[p];
        rc[u] = update(idx, val, rc[p], mid + 1, r);
      }
    }

    st[u] = st[lc[u]] + st[rc[u]];
    return u;
}
