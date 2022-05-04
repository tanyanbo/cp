//
// Created by tanya on 2022/3/5.
//

#ifndef ALGO_INDEXPQ_H
#define ALGO_INDEXPQ_H
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

template <class T, class Compare>

class IndexPQ {
  vector<int> heap;
  vector<int> qp;
  vector<T> keys;
  int siz;
  Compare comparator;

  void exch(int i, int j) {
    T temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    qp[heap[i]] = i;
    qp[heap[j]] = j;
  };

  bool comp(int i, int j) { return comparator(keys[heap[i]], keys[heap[j]]); };

  void swim(int k) {
    while (k > 1 && comp(k, k / 2)) {
      exch(k, k / 2);
      k = k / 2;
    }
  }

  void sink(int k) {
    while (2 * k <= siz) {
      int j = 2 * k;
      if (j < siz && comp(j + 1, j))
        j++;
      if (!comp(j, k))
        break;
      exch(k, j);
      k = j;
    }
  }

public:
  explicit IndexPQ(int maxN) {
    heap = vector<int>{0};
    keys = vector<T>(maxN + 1);
    qp = vector<int>(maxN + 1, -1);
    siz = 0;
    comparator = Compare();
  };

  bool contains(int i) { return qp[i] != -1; }

  T keyOfIndex(int i) {
    if (!contains(i))
      throw 1;
    return keys[i];
  }

  void changeKey(int i, T x) {
    if (!contains(i))
      throw 1;
    keys[i] = x;
    swim(qp[i]);
    sink(qp[i]);
  }

  void push(int i, T x) {
    keys[i] = x;
    heap.push_back(i);
    siz++;
    qp[i] = siz;
    swim(siz);
  };

  void pop() {
    int min = heap[1];
    exch(1, siz);
    heap.pop_back();
    siz--;
    sink(1);
    qp[min] = -1;
  }

  T top() { return keys[heap[1]]; }
  int topIndex() { return heap[1]; }
  int size() { return siz - 1; }
  bool empty() { return siz == 0; }
};
#endif // ALGO_INDEXPQ_H
