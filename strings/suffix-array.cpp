// Suffix Array

// Build: O(n log n)

struct SuffixArray {
  vector<int> sa, lcp_v;
  vector<vector<int>> cs;
  int n;

  int add(int a, int b) { return a + b >= n ? a + b - n : a + b; }
  int sub(int a, int b) { return a - b < 0 ? a - b + n : a - b; }

  SuffixArray(string &s, bool store_steps = false, bool build_lcp = true) {
    s += '$';
    n = (int)s.size();
    sa = sort_shifts(s, store_steps);
    if (build_lcp) {
      lcp_v = build_lcp_v(s);
      lcp_v.erase(lcp_v.begin());
    }
    sa.erase(sa.begin());
    s.pop_back();
  }

  // O (|s| log |s|)
  vector<int> sort_shifts(string &s, bool store_steps) {
    const int ALPHA_SIZE = 256;
    vector<int> p(n), c(n), cnt(ALPHA_SIZE);
    for (char ch : s) cnt[(int)ch]++;
    for (int i = 1; i < ALPHA_SIZE; i++) cnt[i] += cnt[i-1];

    for (int i = 0; i < n; i++) {
      cnt[s[i]]--;
      p[cnt[s[i]]] = i;
    }

    for (int i = 1; i < n; i++) 
      c[p[i]] = c[p[i-1]] + (s[p[i]] != s[p[i-1]]);

    if (store_steps) cs.push_back(c);

    vector<int> cn(n), pn(n);

    for (int k = 0; (1 << k) < n; k++) {
      int nclass = c[p[n - 1]] + 1;
      cnt.assign(nclass, 0);

      for (int i = 0; i < n; i++) {
        pn[i] = sub(p[i], (1 << k));
        cnt[c[i]]++;
      }

      for (int i = 1; i < nclass; i++) 
        cnt[i] += cnt[i - 1];

      for (int i = n-1; i >= 0; i--) {
        cnt[c[pn[i]]]--;
        p[cnt[c[pn[i]]]] = pn[i];
      }

      cn[p[0]] = 0;
      for (int i = 1; i < n; i++) {
        pair<int, int> a = { c[p[i]], c[add(p[i], (1 << k))] };
        pair<int, int> b = { c[p[i - 1]], c[add(p[i - 1], (1 << k))] };
        cn[p[i]] = cn[p[i - 1]] + (a != b);
      }

      swap(c, cn);
      if (store_steps) cs.push_back(c);
    }

    return p;
  }

  // O(|s|)
  vector<int> build_lcp_v(string &s) {
    vector<int> ans(n-1), rank(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;

    for (int i = 0, k = 0; i < n - 1; i++) {
      if (rank[i] == n - 1) continue;
      int j = sa[rank[i] + 1];
      while(s[i + k] == s[j + k]) k++;
      ans[rank[i]] = k;
      if (k) k--;
    }

    return ans;
  }

  // O(log |s|)
  int lcp(int i, int j) {
    if (i == j) return n - i - 1;

    int ans = 0;
    for (int k = (int)cs.size() - 1; k >= 0; k--) {
      if (cs[k][i] == cs[k][j]) {
        int val = (1 << k);
        ans += val, i += val, j += val;
      }
    }

    return ans;
  }

  int compare(int idx, string& s, string& p) {
    int sz_s = (int)s.size() - idx;
    int sz_p = (int)p.size();
    int sz = min(sz_s, sz_p);
    
    for (int i = 0; i < sz; i++) {
      if (s[i + idx] < p[i]) return -1;
      if (s[i + idx] > p[i]) return 1;
    }
    
    if (sz_s == sz_p) return 0;
    if (sz_s < sz_p) return -1;
    return 1;
  }
  
  // O(|p| log |s|)
  bool match(string& s, string &p) {
    int l = 0, r = (int)sa.size() - 1, mid;
    
    while (l != r) {
      mid = (l + r) / 2;
      if (compare(sa[mid], s, p) == -1) l = mid + 1;
      else r = mid;
    }
    
    if ((int)p.size() > (int)s.size() - sa[l]) return false;
    
    for (int i = 0; i < (int)p.size(); i++) {
      if (s[i + sa[l]] != p[i]) return false;
    }
    
    return true;
  }

  // O(|s|)
  ll diff_substr() {
    int sz = n - 1;
    ll ans = sz - sa[0];
    for (int i = 1; i < (int)sa.size(); i++) ans += sz - sa[i] - lcp_v[i - 1];
    return ans;
  }

  // O(|s|)
  ll diff_substr_sz_sum() {
    int sz = n - 1;
    auto sum = [](int l, int r) { return (1ll * (l + r) * (r - l + 1)) / 2; };
    ll ans = sum(1, sz - sa[0]);
    for (int i = 1; i < (int)sa.size(); i++) ans += sum(lcp_v[i - 1] + 1, sz - sa[i]);
    return ans;
  }
};
