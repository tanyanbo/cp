//
// Created by tanya on 2022/5/4.
//

#ifndef ALGO_DATA_STRUCTURES_SEGMENTTREE_H_
#define ALGO_DATA_STRUCTURES_SEGMENTTREE_H_

#include <vector>

typedef long long ll;

using namespace std;

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

#endif //ALGO_DATA_STRUCTURES_SEGMENTTREE_H_
