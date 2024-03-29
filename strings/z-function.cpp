// Z-Function - O(n)

vector<int> zf(string& s){
  vector<int> z(s.size());
  for(int i = 1, l = 0, r = 0, n = (int)s.size(); i < n; i++){
    if(i <= r) z[i] = min(z[i-l], r - i + 1);
    while(i + z[i] < n and s[z[i]] == s[z[i] + i]) z[i]++;
    if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}
