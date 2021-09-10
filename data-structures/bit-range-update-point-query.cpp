// Binary Indexed Tree
// Range Update and Point Query
// Update - O(log n)
// Query - O(log n)

int bit[N];

void add(int p, int v) {
    for (p+=2; p<N; p+=p&-p) bit[p] += v;
}

void update(int l, int r, int val) { add(l, val), add(r+1, -val); }

int query(int p) {
    int r = 0;
    for (p+=2; p; p-=p&-p) r += bit[p];
    return r;
}
