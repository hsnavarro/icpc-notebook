// Pollard Rho - O(n^1/4)

mt19937_64 llrand((int) chrono::steady_clock::now().time_since_epoch().count());

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; };

ll addmod(ll a, ll b, ll mod) {
  if(a >= mod - b) return a + b - mod;
  return a + b;
}

ll mulmod(ll a, ll b, ll mod) {
  ll ans = 0;
  while(b) {
    if(b & 1) ans = addmod(ans, a, mod);
    a = addmod(a, a, mod);
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

// finds prime divisor for n
ll rho(ll n) {
  if(n == 1 or isprime(n)) return n;
  if(n % 2 == 0) return 2;
  while(1) {
    ll x = llrand() % (n - 2) + 2, c = llrand() % (n - 2) + 1;
    ll y = x, d = 1;
    while(d == 1) {
      x = addmod(mulmod(x, x, n), c, n);
      y = addmod(mulmod(y, y, n), c, n);
      y = addmod(mulmod(y, y, n), c, n);
      d = gcd(abs(x - y), n);
    }
    if(d != n) return d;
  }
}

void factor(ll n, vector<ll>& v) {
  if (n == 1 or isprime(n)) return v.pb(n);
  ll f = rho(n);
  factor(f, v), factor(n/f, v);
}
