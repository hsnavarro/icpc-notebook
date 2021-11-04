#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <chrono>
#include <random>
#include <cassert>
using namespace std;

mt19937_64 llrand((int) chrono::steady_clock::now().time_since_epoch().count());

#ifndef ONLINE_JUDGE
  #define db(x) cerr << #x << " == " << x << endl
  #define dbs(x) cerr << x << endl
  #define _ << ", " << 
#else
  #define db(x) ((void)0)
  #define dbs(x) ((void)0)
#endif

using ull = unsigned long long;
using ll = long long;
using ld = long double;

const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f, MOD = 1e9+7;
const int N = 1e5+5;

vector<string> words;

template <int ALPHA_SIZE = 62>
struct Aho {
  struct Node {
    int p, char_p, link = -1, nxt[ALPHA_SIZE];
    int occur = 0;
    Node(int _p = -1, int _char_p = -1) : p(_p), char_p(_char_p) {
      fill(nxt, nxt + ALPHA_SIZE, -1);
    }
  };

  vector<int> strings;
  vector<Node> nodes = { Node() };
  int ans = 0;
  bool build_done = false;

  void clear() {
    strings.clear();
    nodes = { Node() };
    ans = 0;
    build_done = false;
  }

  // change this if different alphabet
  int remap(char c) {
    if (islower(c)) return c - 'a';
    if (isalpha(c)) return c - 'A' + 26;
    return c - '0' + 52;
  }

  void add(int i) {
    int u = 0;

    for (char ch : words[i]) {
      int c = remap(ch);
      if (nodes[u].nxt[c] == -1) {
        nodes[u].nxt[c] = (int)nodes.size();
        nodes.push_back(Node(u, c));
      }

      u = nodes[u].nxt[c];
    }

    nodes[u].occur = 1;
    strings.push_back(i);
  }

  void build() {
    build_done = true;
    queue<int> q;

    for (int i = 0; i < ALPHA_SIZE; i++) {
      if (nodes[0].nxt[i] != -1) q.push(nodes[0].nxt[i]);
      else nodes[0].nxt[i] = 0;
    }

    while(q.size()) {
      int u = q.front();
      q.pop();

      int j = nodes[nodes[u].p].link;
      if (j == -1) nodes[u].link = 0;
      else nodes[u].link = nodes[j].nxt[nodes[u].char_p];

      nodes[u].occur += nodes[nodes[u].link].occur;

      for (int i = 0; i < ALPHA_SIZE; i++) {
        if (nodes[u].nxt[i] != -1) q.push(nodes[u].nxt[i]);
        else nodes[u].nxt[i] = nodes[nodes[u].link].nxt[i];
      }
    }
  }

  int match(string &s) {
    if (!build_done) build();

    ans = 0;

    int u = 0;
    for (char ch : s) {
      int c = remap(ch);
      u = nodes[u].nxt[c];
      ans += nodes[u].occur;
    }

    return ans;
  }
};

const int M = 20;

struct SparseAho {
  Aho<26> nodes[M];
  int powers;

  void add(int idx) {
    int pow = 0;

    vector<int> to_clear;

    for (int i = 0; i < M; i++) {
      if (!((1 << i) & powers)) continue;
      if (pow == i) {
        pow++;
        powers ^= (1 << i);
        to_clear.push_back(i);
      }
    }

    powers |= (1 << pow);

    for (auto x : to_clear) {
      for (auto word_idx : nodes[x].strings) nodes[pow].add(word_idx);
      nodes[x].clear();
    }

    nodes[pow].add(idx);
  }

  int count(string &s) {
    int ans = 0;
    for (int i = 0; i < M; i++) if (powers & (1 << i)) ans += nodes[i].match(s);
    return ans;
  }
};

SparseAho additions, removes;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int m, op;
  cin >> m;
  string s;
  while(m--) {
    cin >> op >> s;
    if (op == 3) {
      cout << additions.count(s) - removes.count(s) << "\n";
      cout.flush();
    } else {
      int idx = (int)words.size();
      words.push_back(s);
      if (op == 1) additions.add(idx);
      else removes.add(idx);
    }
  }
}
