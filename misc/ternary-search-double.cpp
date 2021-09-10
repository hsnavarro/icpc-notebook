// Ternary Search - O(log n)

double ternary_search_min (double l, double r){
    double mid1, mid2;
    for(int i = 0; i < 100; i++){
        mid1 = (r-l)/3 + l;
        mid2 = mid1 + (r-l)/3;
        if(func(mid2) < func(mid1)) l = mid1;
        else r = mid2;
    }
    return l;
}

double ternary_search_max (double l, double r){
    double mid1, mid2; 
    for(int i = 0; i < 100; i++){
        mid1 = (r-l)/3 + l;
        mid2 = mid1 + (r-l)/3;
        if(func(mid2) > func(mid1)) l = mid1;
        else r = mid2;
    }
    return l;
}
