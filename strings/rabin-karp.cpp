// Rabin-Karp (String Matching + Hashing)
const int MOD = 1e9+9;
const int B = 313;
char s[N], p[N];
int n, m; // n = strlen(s), m = strlen(p)

// Chance of collision for k generated values and N possible hash values
// e^(-k*(k-1)/2*N)

int rabin(){
  if(n < m) return 0;
  ull hp = 0, hs = 0, E = 1, oc = 0;
  for(int i = 0; i < m; i++){
    hp = ((hp*B)%MOD + p[i])%MOD;
    hs = ((hs*B)%MOD + s[i])%MOD;
    E = (E*B)%MOD;
  }

  if(hs == hp) oc++; //match at 0
  for(int i = m; i < n; i++){
    hs = ((hs*B)%MOD + s[i])%MOD;
    hs = (hs - s[i-m]*E%MOD + MOD)%MOD;
    if(hs == hp) oc++; //match at i-m+1
  }
  return oc;
}
