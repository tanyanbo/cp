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
//#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

class SegmentTree {
  int n;
  vector<ll> st, lazy;
  void build(int start, int end, int node, vector<int> &v) {
    if (start==end) {
      st[node] = v[start];
      return;
    }
    int mid = (start + end)/2;
    build(start, mid, node*2 + 1, v);
    build(mid + 1, end, node*2 + 2, v);
    st[node] = st[node*2 + 1] + st[node*2 + 2];
  }

  ll query(int start, int end, int l, int r, int node) {
    if (end < l or start > r)
      return 0;
    if (lazy[node]) {
      st[node] += lazy[node]*(end - start + 1);
      if (start!=end)
        lazy[node*2 + 1] += lazy[node], lazy[node*2 + 2] += lazy[node];
      lazy[node] = 0;
    }
    if (start >= l and end <= r)
      return st[node];
    int mid = (start + end)/2;
    ll q1 = query(start, mid, l, r, node*2 + 1);
    ll q2 = query(mid + 1, end, l, r, node*2 + 2);
    return q1 + q2;
  }

  void update(int start, int end, int l, int r, int node, int value) {
    if (lazy[node]) {
      st[node] += lazy[node]*(end - start + 1);
      if (start!=end) {
        lazy[node*2 + 1] += lazy[node], lazy[node*2 + 2] += lazy[node];
      }
      lazy[node] = 0;
    }
    if (start > r or end < l)
      return;
    if (start >= l and end <= r) {
      st[node] += value*(end - start + 1);
      if (start!=end) {
        lazy[node*2 + 1] += value, lazy[node*2 + 2] += value;
      }
      return;
    }
    int mid = (start + end)/2;
    update(start, mid, l, r, node*2 + 1, value);
    update(mid + 1, end, l, r, node*2 + 2, value);
    st[node] = st[node*2 + 1] + st[node*2 + 2];
  }
 public:
  explicit SegmentTree(vector<int> &v, int pad = 0) {
    int temp = 1;
    while (temp < v.size()) {
      temp *= 2;
    }
    n = temp;
    lazy = vector<ll>(4*n, 0);
    int sz = (int) v.size();
    for (int i = 0; i < temp - sz; i++)
      v.push_back(pad);
    st = vector<ll>(4*n);
    build(0, n - 1, 0, v);
  }

  ll query(int l, int r) {
    return query(0, n - 1, l, r, 0);
  }

  void update(int l, int r, int value) {
    update(0, n - 1, l, r, 0, value);
  }
};

void solve() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (auto &x : v)
    cin >> x;
  SegmentTree st{v};
  ll total = st.query(0, n - 1);
  vector<int> res(n);
  for (int i = n - 1; i >= 0; i--) {
    int idx = i + 1;
    res[i] = st.query(i, i) >= idx;
    st.update(i - (int) (total/idx) + 1, i, -1);
    total = st.query(0, i - 1);
  }
  for (int i = 0; i < n; i++)
    if (i!=n - 1)
      cout << res[i] << " ";
    else
      cout << res[i] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}