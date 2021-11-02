//Union-Find with Rollback
//Union and find - O(log n)

int par[N], sz[N];
vector<pair<int, int>> old_par, old_sz;

int find(int a){ return par[a] == a ? a : find(par[a]); }

void unite(int a, int b){
    if(find(a) == find(b)) return;
    a = find(a), b = find(b);
    if(sz[a] < sz[b]) swap(a, b);
    old_par.push_back({b, par[b]});
    old_sz.push_back({a, sz[a]});
    sz[a] += sz[b], par[b] = a;
}

void roolback(){
    par[old_par.back().first] = old_par.back().second;
    sz[old_sz.back().st] = old_sz.back().second;
    old_par.pop_back();
    old_sz.pop_back();
}

//in main
for(int i = 0; i < N; i++) par[i] = i, sz[i] = 1;
