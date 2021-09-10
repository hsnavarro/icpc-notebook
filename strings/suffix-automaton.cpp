#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int len[2*N], link[2*N], nxt[2*N][26], szt = 1, last = 1;

void add(string &s) {
  for(auto c : s) {
    int cur = ++szt, p = last, j = c - 'a';
    len[cur] = len[last] + 1;
    while(p and !nxt[p][j]) {
      nxt[p][j] = cur;
      p = link[p];
    }
    if(!p) link[cur] = 1;
    else {
      int q = nxt[p][j];
      if(len[p] + 1 == len[q]) link[cur] = q;
      else {
        int clone = ++szt;
        len[clone] = len[p] + 1;
        link[clone] = link[q];
        for(int i = 0; i < 26; i++) 
          if(nxt[q][i]) nxt[clone][i] = nxt[q][i];
        while(p and nxt[p][j] == q) {
          nxt[p][j] = clone;
          p = link[p];
        }
        link[q] = link[cur] = clone;
      }
    }
    last = cur;
  }
}


int main() {


}
