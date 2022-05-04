//
// Created by tanya on 2022/3/20.
//

#include <bits/stdc++.h>
#include <iostream>
using namespace std::chrono;
using namespace std;

#include "mainWithTime.h"
int main1() {
  cout.setf(ios::fixed);
  auto start = high_resolution_clock::now();

  // start code here
  // end code here
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(end - start);
  cout << endl;
  cout << "Time taken: " << duration.count() << " microseconds";
  return 0;
}
