// Binary Indexed Tree
// Point Update and Range Query
// Update - O(log n)
// Query - O(log n)

template <class T>
struct Bit {
  vector<T> bit;

  Bit(int _n = 0) : bit(_n + 3) {}

  void add(int p, T v) {
    for (p += 2; p < (int)bit.size(); p += p & -p) bit[p] += v;
  }

  T query(int p) {
    T r = 0;
    for (p += 2; p; p -= p & -p) r += bit[p];
    return r;
  }

  T query(int l, int r) { return query(r) - query(l - 1); }
};
