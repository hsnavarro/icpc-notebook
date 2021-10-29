// String Hashing
// Rabin Karp - O(n + m)
template <int N = 3>
struct Hash {
  int hs[N];
  static vector<int> mods;

  static int add(int a, int b, int mod) { return a >= mod - b ? a + b - mod : a + b; }
  static int sub(int a, int b, int mod) { return a - b < 0 ? a - b + mod : a - b; }
  static int mul(int a, int b, int mod) { return 1ll * a * b % mod; }

  Hash(int x = 0) { fill(hs, hs + N, x); }

  bool operator<(const Hash& b) const {
    for (int i = 0; i < N; i++) if (hs[i] < b.hs[i]) return true;
    return false;
  }

  Hash operator+(const Hash& b) const {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = add(hs[i], b.hs[i], mods[i]);
    return ans;
  }

  Hash operator-(const Hash& b) const {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = sub(hs[i], b.hs[i], mods[i]);
    return ans;
  }

  Hash operator*(const Hash& b) const {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = mul(hs[i], b.hs[i], mods[i]);
    return ans;
  }

  Hash operator+(int b) const {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = add(hs[i], b, mods[i]);
    return ans;
  }

  Hash operator*(int b) const {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = mul(hs[i], b, mods[i]);
    return ans;
  }

  friend Hash operator*(int a, const Hash& b) {
    Hash ans;
    for (int i = 0; i < N; i++) ans.hs[i] = mul(b.hs[i], a, b.mods[i]);
    return ans;
  }

  friend ostream& operator<<(ostream& os, const Hash& b) {
    for (int i = 0; i < N; i++) os << b.hs[i] << " \n"[i == N - 1];
    return os;
  }
};

template <int N> vector<int> Hash<N>::mods = { (int) 1e9 + 9, (int) 1e9 + 33, (int) 1e9 + 87 }; 

template <int N = 3>
struct PolyHash {
  vector<Hash<N>> h, p;

  PolyHash(string& s, int pr = 313) {
    int sz = (int)s.size();
    p.resize(sz + 1);
    h.resize(sz + 1);

    p[0] = 1, h[0] = s[0];
    for (int i = 1; i < sz; i++) {
      h[i] = pr * h[i - 1] + s[i];
      p[i] = pr * p[i - 1];
    }
  }

  Hash<N> fhash(int l, int r) { 
    if (!l) return h[r]; 
    return h[r] - h[l - 1] * p[r - l + 1]; 
  }

  static Hash<N> shash(string& s, int pr = 313) {
    Hash<N> ans;
    for (int i = 0; i < (int)s.size(); i++) ans = pr * ans + s[i];
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