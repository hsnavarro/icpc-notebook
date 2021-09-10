// Sieve - O(n log(log n))

int cmp[N];
vector<int> p;

void sieve() {
  for(ll i = 2; i < N; i++) if(!cmp[i]) {
    p.push_back(i);
    for(ll j = i*i; j < N; j += i) cmp[j] = 1;
  }
}
