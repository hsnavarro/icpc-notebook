// Miller-Rabin - Primality Test O(iterations * log n * log n * log n)

// n = 2^s * d + 1

// For a base 'a' ('a' between 2 and n-2)
// a^d = 1 mod n
// a^(2^r * d) = -1 mod n ('r' between 0 and s-1)

ll mulmod(ll a, ll b, ll mod) {
  ll ans = 0;
  while(b) {
    if(b & 1) ans = (ans + a) % mod;
    a = (2*a) % mod;
    b = b/2;
  }
  return ans;
}

ll fexp(ll b, ll e, ll mod) {
  ll ans = 1;
  while(e) {
    if(e & 1) ans = mulmod(ans, b, mod);
    b = mulmod(b, b, mod);
    e = e/2;
  }
  return ans;
}

bool miller(ll a, ll n) {
  if(a >= n) return 1;
  ll s = 0, d = n-1;
  while(d%2 == 0 and d) d = d/2, s++; 
  ll x = fexp(a, d, n);
  if(x == 1 or x == n-1) return 1;
  for(int r = 0; r < s; r++, x = mulmod(x, x, n)) if(x == n-1) return 1;
  return 0;
}

bool isprime(ll n) {
  if(n == 1) return 0;
  int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (int i = 0; i < 12; ++i) if (!miller(base[i], n)) return 0;
  return 1;
}
