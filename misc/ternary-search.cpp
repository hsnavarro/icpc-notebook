// Ternary Search - O(log n)

int ternary_search_min (int l = 1, int r = N){
    int mid, mn = INF, idx;
    while(r - l > 5){
        mid = (l+r)/2;
        if(func(mid + 1) < func(mid)) l = mid;
        else r = mid + 1;
    }
    for(int i = l; i <= r; i++) if(func(i) < mn) mn = func(i), idx = i;
    return idx;
}

int ternary_search_max (int l = 1, int r = N){
    int mid, mx = -INF, idx;
    while(r - l > 5){
        mid = (l+r)/2;
        if(func(mid + 1) > func(mid)) l = mid;
        else r = mid + 1;
    }
    for(int i = l; i <= r; i++) if(func(i) > mx) mx = func(i), idx = i;
    return idx;
}
