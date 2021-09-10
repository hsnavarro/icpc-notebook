//Segment Tree (Range Query and Point Update)
//NOT the Lazy Propagation version
//Update and Query - O(log n)
//Space - O(n)

int n, v[N], st[4*N];

// n - size of the array (up to N)
// You could do point update in all values of v, instead of using build
void build(int p = 1, int l = 1, int r = n){
    if(l == r) { st[p] = v[l]; return; }
    build(2*p, l, (l+r)/2), build(2*p + 1, (l+r)/2 + 1, r);
    st[p] = st[2*p] + st[2*p + 1];
}

int query(int i, int j, int p = 1, int l = 1, int r = n){
    if(l >= i and j >= r) return st[p];
    if(l > j or r < i) return 0;
    return query(i, j, 2*p, l, (l+r)/2) + query(i, j, 2*p + 1, (l+r)/2 + 1, r);
}

void update(int idx, int v, int p = 1, int l = 1, int r = n){
    if(l == r) { st[p] = v; return; }
    if(idx <= (l+r)/2) update(idx, v, 2*p, l, (l+r)/2);
    else update(idx, v, 2*p + 1, (l+r)/2 + 1, r);
    st[p] = st[2*p] + st[2*p + 1];
}
