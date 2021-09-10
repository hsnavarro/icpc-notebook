// Mobius Function
// u(1) = 1
// u(p) = -1
// u(p^k) = 0, k >= 2
// u(a*b) = u(a)*u(b), for a,b co-primes

// Sum for d|n of u(d) = [n == 1]

// Calculate Mobius all integers - O(n log(log n))

int cmp[N], mob[N];
void mobius() {
  for(int i = 1; i < N; i++) mob[i] = 1;
  for(ll i = 2; i < N; i++) if(!cmp[i]) {
    for(ll j = i; j < N; j += i) cmp[j] = 1, mob[j] *= -1;
    for(ll j = i*i; j < N; j += i*i) mob[j] = 0;
  }
}

// Calculate Mobius for 1 integer - O(sqrt(n))
int mobius(int n) {
  if(n == 1) return 1;
  int p = 0;
  for(int i = 2; i*i <= n; i++) {
    if(n % i == 0) {
      n = n/i, p++;
      if(n % i == 0) return 0;
    }
  }
  if(n > 1) p++;
  return p&1 ? -1 : 1;
}
