// For a string A, substring of P
// D(A) is the set of indexes i such that A is a suffix of P[0..i]
// Each node represents a set D
 
// Suffix Automaton
// Build: O(|s| * ALPHA_SIZE)
// Match: O(|p|)
 
template<int ALPHA_SIZE = 62>
struct SuffixAutomaton {
  struct Node {
    int len, link, cnt, nxt[ALPHA_SIZE];
    Node(int _len = 0, int _link = 0, int _cnt = 1) : len(_len), link(_link), cnt(_cnt) {
      fill(nxt, nxt + ALPHA_SIZE, 0);
    };
  };
 
  // change this if different alphabet
  int remap(char c) {
    if (islower(c)) return c - 'a';
    if (isalpha(c)) return c - 'A' + 26;
    return c - '0' + 52;
  }
 
  vector<Node> nodes = { Node(), Node() };
  int last = 1;
 
  SuffixAutomaton() {}
 
  SuffixAutomaton(string &s) {
    nodes.reserve(2 * (int)s.size() + 2);
    add(s);
  }
 
  void add(char ch) {
    int c = remap(ch);
    int p, u = (int)nodes.size();
    nodes.push_back(Node(nodes[last].len + 1));
 
    for (p = last; p and !nodes[p].nxt[c]; p = nodes[p].link)
      nodes[p].nxt[c] = u;
 
    if (!p) nodes[u].link = 1;
    else {
      int q = nodes[p].nxt[c];
      if (nodes[p].len + 1 == nodes[q].len) nodes[u].link = q;
      else {
        int clone = (int)nodes.size();
        nodes.push_back(Node(nodes[p].len + 1, nodes[q].link, 0));
        copy(nodes[q].nxt, nodes[q].nxt + ALPHA_SIZE, nodes[clone].nxt);
        for (; p and nodes[p].nxt[c] == q; p = nodes[p].link)
          nodes[p].nxt[c] = clone;
        nodes[q].link = nodes[u].link = clone;
      }
    }
    last = u;
  }
 
  void add(string &s) { for (auto ch : s) add(ch); }
 
  bool match(string &p) {
    int u = 1;
    for (auto ch : p) {
      int c = remap(ch);
      u = nodes[u].nxt[c];
      if (!u) return false;
    }
    return true;
  }
};
