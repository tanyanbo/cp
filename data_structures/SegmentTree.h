//
// Created by tanya on 2022/5/4.
//

#ifndef ALGO_DATA_STRUCTURES_SEGMENTTREE_H_
#define ALGO_DATA_STRUCTURES_SEGMENTTREE_H_

#include <vector>

using namespace std;

class SegmentTree {
  int n;
  vector<int> st;
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

  int query(int start, int end, int l, int r, int node) {
    if (l > end or r < start)
      return 0;
    if (l <= start and r >= end)
      return st[node];
    int mid = (start + end)/2;
    int q1 = query(start, mid, l, r, node*2 + 1);
    int q2 = query(mid + 1, end, l, r, node*2 + 2);
    return q1 + q2;
  }

  void update(int start, int end, int idx, int node, int value) {
    int mid = (start + end)/2;
    if (start==end) {
      st[node] = value;
      return;
    }
    if (idx <= mid)
      update(start, mid, idx, node*2 + 1, value);
    else
      update(mid + 1, end, idx, node*2 + 2, value);
    st[node] = st[node*2 + 1] + st[node*2 + 2];
  }
 public:
  SegmentTree(vector<int> &v, int pad = 0) {
    int temp = 1;
    while (temp < v.size()) {
      temp *= 2;
    }
    n = temp;
    int sz = (int) v.size();
    for (int i = 0; i < temp - sz; i++)
      v.push_back(pad);
    st = vector<int>(4*n);
    build(0, n - 1, 0, v);
  }

  int query(int l, int r) {
    return query(0, n - 1, l, r, 0);
  }

  void update(int idx, int value) {
    update(0, n - 1, idx, 0, value);
  }
};

#endif //ALGO_DATA_STRUCTURES_SEGMENTTREE_H_
