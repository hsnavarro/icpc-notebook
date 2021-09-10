// Parallel Binary Search - O(nlog n * cost to update data structure + qlog n * cost for bs condition)

struct query { int i, ans; /*+ query related info*/ };
vector<query> req;
int l_default, r_default, idx = l_default;

void pbs(vector<query>& qs, int l_pbs = l_default, int r_pbs = r_default){
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
        for(auto q : qs) req[q.i].ans = l_pbs;
        return;
    }

    vector<query> vl, vr;
    for (auto& q : qs) {
        if ( /* cond */ ) vl.pb(q);
        else vr.pb(q);
    }

    pbs(vl, l_pbs, mid);
    pbs(vr, mid + 1, r_pbs);
}