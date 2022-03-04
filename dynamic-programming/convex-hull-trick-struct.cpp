// Convex Hull Trick
 
// max / min (a_i + b_j + m_j * x_i)
// max: m_j increasing
// min: m_j decreasing
 
template <class T>
struct Line {
  T m, b;
  bool operator<(const Line& rhs) const { return b == rhs.b ? m < rhs.m : b > rhs.b; }
  bool operator>(const Line& rhs) const { return b == rhs.b ? m > rhs.m : b < rhs.b; }
  T eval(T x) { return m * x + b; }
  friend bool check(Line s, Line t, Line u) {
    T a = (s.b - t.b);
    T b = (s.b - u.b);

    T c = (t.m - s.m);
    T d = (u.m - s.m);
 
    if (__builtin_mul_overflow_p(a, b, (T)0)
      or __builtin_mul_overflow_p(c, d, (T)0)) return (ld)a / c < (ld)b / d;
 
    return a * d < b * c;
  }
};
 
template <class T, class C = less_equal<T>, class D = less<Line<T>>>
struct CHT {
  C cmp;
  D cmp2;
  int pos = 0;
  vector<Line<T>> hull;
 
  CHT(int _n = 0) { hull.reserve(_n); } 
 
  void sort_lines() { sort(hull.begin(), hull.end(), cmp2); }
 
  void push(T m, T b) { hull.push_back({ m, b}); }
 
  void add(T m, T b) {
    Line<T> s = { m, b };
    int nh = (int)hull.size();
    if (nh == 1 and hull[nh-1].b == s.b) {
      hull.pop_back();
      nh--;
    }
    if (nh > 0 and cmp(s.m, hull[nh-1].m)) return;
    while (nh >= 2 and !check(hull[nh-2], hull[nh-1], s)) {
      hull.pop_back();
      nh--;
      pos = min(pos, nh);
    }
    hull.push_back(s);
  }
 
  // x_i increasing
  T lin_query(T x) {
    if (pos == (int)hull.size()) return LINF;
    while (pos + 1 < (int)hull.size() and cmp(hull[pos].eval(x), hull[pos+1].eval(x))) pos++;
    return hull[pos].eval(x);
  }
 
  T query(T x) {
    int l = 0, r = (int)hull.size() - 1, mid;
    while (l != r) {
      mid = (l + r) / 2;
      if (cmp(hull[mid + 1].eval(x), hull[mid].eval(x))) r = mid;
      else l = mid + 1;
    }
    return hull[l].eval(x);
  }
};
 
template<class T> using MaxCHT = CHT<T>;
template<class T> using MinCHT = CHT<T, greater_equal<T>, greater<Line<T>>>;
