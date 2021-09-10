//Union-Find with Rollback
//Union and find - O(log n)

int par[N], sz[N];
vector<pii> old_par, old_sz;

int find(int a){ return par[a] == a ? a : find(par[a]); }

void unite(int a, int b){
    if(find(a) == find(b)) return;
    a = find(a), b = find(b);
    if(sz[a] < sz[b]) swap(a, b);
    old_par.pb({b, par[b]});
    old_par.pb({a, sz[a]});
    sz[a] += sz[b], par[b] = a;
}

void roolback(){
    par[old_par.top().st] = old_par.top().nd;
    sz[old_sz.top().st] = old_sz.top().nd;
    old_par.pop();
    old_sz.pop();
}

//in main
for(int i = 0; i < N; i++) par[i] = i, sz[i] = 1;
