// Merge-Sort Tree 
// Build: O(n log n)
// Query: O(log^2 n)
// Memory: O(n log n)

template <class T = int>
struct MergeSortTree {
  vector<vector<T>> st;
  int n;

  MergeSortTree(vector<T>& x) { 
    n = (int)x.size();
    st.resize(4 * n);
    build(1, 0, n - 1, x); 
  }

  void build(int p, int l, int r, vector<T> &x) {
    if (l == r) {
      st[p] = { x[l] };
      return;
    }

    int mid = (l + r) / 2;
    build(2 * p, l, mid, x);
    build(2 * p + 1, mid + 1, r, x);

    st[p].resize(r - l + 1);
    merge(st[2 * p].begin(), st[2 * p].end(),
          st[2 * p + 1].begin(), st[2 * p + 1].end(),
          st[p].begin());
  }
};

struct KthElement : MergeSortTree<int> {
  KthElement(vector<int>& x) : MergeSortTree<int>(x) {}

  int query_aux(int i, int j, int k, int p, int l, int r) {
    assert(k >= 1 and k <= r - l + 1);
    if (l == r) return st[p][0];

    vector<int>& left = st[2 * p];
    int amt = (int) (upper_bound(left.begin(), left.end(), j) - lower_bound(left.begin(), left.end(), i));

    int mid = (l + r) / 2;
    if (amt >= k) return query_aux(i, j, k, 2 * p, l, mid);
    return query_aux(i, j, k - amt, 2 * p + 1, mid + 1, r);
  }

  int query(int i, int j, int k) { return query_aux(i, j, k, 1, 0, n - 1); }
};