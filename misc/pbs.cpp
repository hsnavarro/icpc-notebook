// Parallel Binary Search - O(nlog n * cost to update data structure + qlog n * cost for binary search condition)

struct Query { int i, ans; /*+ query related info*/ };
vector<Query> req;
int l_default, r_default, idx = l_default;

void pbs(vector<Query>& qs, int l_pbs = l_default, int r_pbs = r_default){
    int mid = (l_pbs + r_pbs) / 2;
    // mid = (L+R+1)/2 if different from simple upper/lower bound
    if(qs.empty()) return;

    while(idx < mid) {
        idx++;
        //add value to data structure
    }
    while(idx > mid) {
        //remove value to data structure
        idx--;
    }

    if(l_pbs == r_pbs) {
        for(auto& q : qs) req[q.i].ans = l_pbs;
        return;
    }

    vector<Query> vl, vr;
    for (auto& q : qs) {
        if ( /* cond */ ) vl.push_back(q);
        else vr.push_back(q);
    }

    pbs(vl, l_pbs, mid);
    pbs(vr, mid + 1, r_pbs);
}