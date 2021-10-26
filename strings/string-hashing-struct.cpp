// String Hashing
// Rabin Karp - O(n + m)
template <int N>
struct Hash {
  int hs[N];
  static vector<int> mods;

  static int add(int a, int b, int mod) { return a >= mod - b ? a + b - mod : a + b; }
  static int sub(int a, int b, int mod) { return a - b < 0 ? a - b + mod : a - b; }
  static int mul(int a, int b, int mod) { return 1ll * a * b % mod; }

  Hash(int x = 0) {
    fill(hs, hs + N, x);
  }

  bool operator==(const Hash& b) {
    for (int i = 0; i < N; i++) if (hs[i] != b.hs[i]) return false;
    return true;
  }

  bool operator!=(const Hash& b) {
    return !(*this == b);
  }

  Hash operator+(const Hash& b) {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = add(hs[i], b.hs[i], mods[i]);
    return ans;
  }

  Hash operator-(const Hash& b) {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = sub(hs[i], b.hs[i], mods[i]);
    return ans;
  }

  Hash operator*(const Hash& b) {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = mul(hs[i], b.hs[i], mods[i]);
    return ans;
  }

  Hash operator+(int b) {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = add(hs[i], b, mods[i]);
    return ans;
  }

  Hash operator*(int b) {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = mul(hs[i], b, mods[i]);
    return ans;
  }

  friend Hash operator*(int a, const Hash& b) {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = mul(b.hs[i], a, b.mods[i]);
    return ans;
  }
};

template<int N> vector<int> Hash<N>::mods = { (int) 1e9 + 9, (int) 1e9 + 33, (int) 1e9 + 87 }; 

template<int N>
struct PolyHash {
  vector<Hash<N>> h, p;

  PolyHash(string& s, int pr = 313) {
    int sz = (int)s.size();
    p.resize(sz + 1);
    h.resize(sz + 1);

    p[0] = 1, p[1] = pr;
    for (int i = 1; i <= sz; i++) {
      h[i] = pr * h[i - 1] + s[i - 1];
      p[i] = pr * p[i - 1];
    }
  }

  Hash<N> fhash(int l, int r) {
    l++, r++;
    return h[r] - h[l-1] * p[r - l + 1];
  }

  Hash<N> shash(string& s) {
    Hash<N> ans;
    for (int i = 0; i < (int)s.size(); i++) ans = p[1] * ans + s[i];
    return ans;
  }

  friend int rabin_karp(string& s, string& pt) {
    PolyHash hs = PolyHash(s);
    Hash<N> hp = hs.shash(pt);
    int cnt = 0;
    for (int i = 0, m = (int)pt.size(); i + m <= (int)s.size(); i++) {
      if (hs.fhash(i, i + m - 1) == hp) {
        // match at i
        cnt++;
      }
    }
    
    return cnt;
  }
};