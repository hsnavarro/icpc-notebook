// Fast Exponential - O(log b)
ll fexp (ll b, ll e, ll mod) {
  ll ans = 1;
  while (e) {
    if (e&1) ans = (ans*b) % mod;
    b = (b*b) % mod;
    e = e/2;
  }
  return ans;
}

