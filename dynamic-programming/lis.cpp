// Longest Increasing Subsequence - LIS (n log n)

// Not Decreasing -> change lower_bound to upper_bound

int lis(vector<int> &v) {
  vector<int> dp;
  for(int i = 0; i < v.size(); i++) {
    int l = lower_bound(dp.begin(), dp.end(), v[i]) - dp.begin();
    if(l == dp.size()) dp.pb(v[i]);
    else dp[l] = v[i];
  }
  return dp.size();
}
