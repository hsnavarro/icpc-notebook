// Trie
// Build: O(sum size of strings)
// Memory: O(sum size of strings * ALPHA SIZE)

template <int ALPHA_SIZE = 62> 
struct Trie {
  struct Node {
    vector<int> nxt;
    int cnt = 0;
    Node() : nxt(ALPHA_SIZE, -1) {}
  };

  vector<Node> nodes = { Node() };

  // change this if different alphabet
  int remap(char c) {
    if (islower(c)) return c - 'a';
    if (isalpha(c)) return c - 'A' + 26;
    return c - '0' + 52;
  }

  void add(const string& s) {
    int u = 0;
    for (char ch : s) {
      int c = remap(ch);
      if (nodes[u].nxt[c] == -1) {
        nodes[u].nxt[c] = (int)nodes.size();
        nodes.push_back(Node());
      }
      
      u = nodes[u].nxt[c];
      nodes[u].cnt++;
    }
  }
};