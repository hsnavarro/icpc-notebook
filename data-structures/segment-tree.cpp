//Segment Tree (Range Query and Range Update)
//Update and Query - O(log n)
//Space - O(n)

int n, v[N], lz[4*N], st[4*N];

// n - size of the array (up to N)
void build(int p = 1, int l = 1, int r = n){
    if (l == r) { st[p] = v[l]; return; }
    build(2*p, l, (l+r)/2);
    build(2*p + 1, (l+r)/2 + 1, r);
    st[p] = st[2*p] + st[2*p + 1];
}

void push(int p, int l, int r){
  if (lz[p]) {
    st[p] = lz[p]*(r-l+1);
    if (l != r) lz[2*p] = lz[2*p + 1] = lz[p];
    lz[p] = 0;
  }
}

int query(int i, int j, int p = 1, int l = 1, int r = n){
    push(p, l, r);
    if (l > j or r < i) return 0;
    if (l >= i and j >= r) return st[p];
    return query(i, j, 2*p, l, (l+r)/2) + query(i, j, 2*p + 1, (l+r)/2 + 1, r);
}

void update(int i, int j, int v, int p = 1, int l = 1, int r = n){
    push(p, l, r);
    if (l > j or r < i) return;
    if (l >= i and j >= r) { lz[p] = v, push(p, l, r); return; }
    update(i, j, v, 2*p, l, (l+r)/2);
    update(i, j, v, 2*p+1, (l+r)/2+1, r);
    st[p] = st[2*p] + st[2*p + 1];
}
