#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "data_structures/SegmentTree.h"
//#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

void solve() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (auto &x : v)
    cin >> x;
  ll total = accumulate(v.begin(), v.end(), 0ll);
  v.insert(v.begin(), 0);
  vector<int> res(n + 1);
  for (int i = n; i > 0; i--) {
    res[i] = v[i] >= i;
    for (int k = i; k >= max(1ll, i - total/i + 1); k--)
      v[k]--;
    total -= total/i;
    total -= v[i];
  }
  for (int i = 1; i <= n; i++)
    if (i!=n)
      cout << res[i] << " ";
    else
      cout << res[i] << "\n";
}

int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(nullptr);
//  int t;
//  cin >> t;
//  while (t--) {
//    solve();
//  }
  vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  SegmentTree segment_tree{v};
  segment_tree.update(0, 10);
  segment_tree.update(4, 10);
  cout << segment_tree.query(2, 6) << "\n";
  cout << segment_tree.query(4, 7) << "\n";
}