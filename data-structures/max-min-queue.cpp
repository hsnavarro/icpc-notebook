// Monotonic Queue (aka Max/Min Queue) - Operations in O(1)

template <class T, class C = greater_equal<T>> 
struct MonoQueue {
  C cmp;
  T sum = 0;
  int l = 1, r = 0;
  deque<pair<T, int>> dq;

  void push(T x) {
    x -= sum;
    while (!dq.empty() and cmp(dq.back().first, x)) dq.pop_back();
    dq.push_back({x, ++r});
  }

  T query() { 
    assert(size() > 0);
    T val = dq.front().first;
    return val + sum;
  }

  void pop() { if (!dq.empty() and dq.front().second == l++) dq.pop_front(); }
  void clear() { sum = 0, l = 1, r = 0, dq.clear(); }
  void add(T x) { sum += x; }
  int size() { return r - l + 1; }
};

template <class T> using MinQueue = MonoQueue<T>;
template <class T> using MaxQueue = MonoQueue<T, less_equal<T>>;