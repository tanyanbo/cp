//
// Created by tanya on 2022/1/8.
//
#include "data_structures/Trie.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// vector<vector<int>> getGp(vector<int> nums, int r)
//{
//     unordered_map<int, vector<int>> m;
//     vector<vector<int>> res;
//     for (int i = 0; i<nums.siz(); ++i) {
//         if (m.find(nums[i])==m.end()) {
//             m[nums[i]*r].push_back(2);
//         }
//         else {
//             for (auto x: m[nums[i]]) {
//                 if (x==2){
//                     m[nums[i]*r].push_back(3);
//                     m[nums[i]].erase(2);
//                 } else {
//
//                 }
//
//             }
//
//             if (std::find(v.begin(), v.end(), 2)!=v.end()) {
//                 if (m.find(nums[i]*r)==m.end())
//                     m[nums[i]*r] = 3;
//                 m.erase(nums[i]);
//             }
//             else {
//                 vector<int> temp{nums[i]/r/r, nums[i]/r, nums[i]};
//                 m.erase(nums[i]);
//                 res.push_back(temp);
//             }
//         }
//     }
//     return res;
// }

int qbf(string s, vector<string> words, int cuts) {

  unordered_set<string> words_set;
  for (const auto &word : words) {
    words_set.insert(word);
  }
  int rec{INT32_MAX};
  for (int i = 0; i < s.length(); i++) {
    if (i == s.length() - 1) {
      if (words_set.count(s))
        return min(cuts, rec);
      else
        return min(rec, INT32_MAX);
    }
    string sub{s.substr(0, i + 1)};
    if (!words_set.count(sub))
      continue;
    rec = qbf(s.substr(i + 1, INT32_MAX), words, cuts + 1);
  }
  return INT32_MAX;
}

vector<bool> cuteCat(string document, vector<string> words) {
  Trie *trie = new Trie();
  vector<bool> res(words.size(), false);
  for (const auto &word : words) {
    trie->insert(word);
  }
  TrieNode *temp = trie->root;
  string cur;
  for (int i = 0; i < document.length(); i++) {
    if (!temp->m.count(document[i])) {
      temp = trie->root;
      cur = "";
      continue;
    }
    cur += document[i];
    if (temp->m[document[i]]->isTerminal) {
      for (int i = 0; i < words.size(); i++) {
        if (words[i] == cur) {
          res[i] = true;
          break;
        }
      }
      temp = trie->root;
      i = i - (int)cur.length() + 1;
      cur = "";
      continue;
    }
    temp = temp->m[document[i]];
  }
  return res;
}

int knapsack(vector<int> weights, vector<int> prices, int weight) {
  if (weights.size() == 1) {
    if (weights[0] <= weight)
      return prices[0];
    else
      return 0;
  }

  int noInc = knapsack(vector<int>(weights.begin() + 1, weights.end()),
                       vector<int>(prices.begin() + 1, prices.end()), weight);

  if (weight - weights[0] < 0)
    return noInc;

  int inc = knapsack(vector<int>(weights.begin() + 1, weights.end()),
                     vector<int>(prices.begin() + 1, prices.end()),
                     weight - weights[0]);

  return max(inc + prices[0], noInc);
}
//
// class Solution {
//    void helper(vector<vector<char>>& board, vector<vector<char>>& copyboard,
//            int x, int y,
//            bool& res,
//            vector<unordered_set<char>>& hor, vector<unordered_set<char>>&
//            ver, vector<unordered_set<char>>& grid)
//    {
//        for (int j = 0; j<9; j++) {
//            for (int i = 0; i<9; i++) {
//                if (board[j][i]!='.') {
//                    char num = board[j][i];
//                    hor[i].insert(num);
//                    ver[j].insert(num);
//                    grid[((j/3)*3)+(i/3)].insert(num);
//                }
//            }
//        }
//
//        set<char> possible{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
//        if (board[y][x]=='.') {
//            for (auto a: hor[x])
//                possible.erase(a);
//            for (auto a: ver[y])
//                possible.erase(a);
//            for (auto a: grid[((y/3)*3)+(x/3)])
//                possible.erase(a);
//            if (possible.empty()) {
//                if (x==0) {
//                    if (copyboard[y-1][8]=='.') {
//                        hor[8].erase(board[y-1][8]);
//                        ver[y-1].erase(board[y-1][8]);
//                        grid[(((y-1)/3)*3)+(8/3)].erase(board[y-1][8]);
//                        board[y-1][8] = '.';
//                    }
//                }
//                else {
//                    if (copyboard[y][x-1]=='.') {
//                        hor[x-1].erase(board[y][x-1]);
//                        ver[y].erase(board[y][x-1]);
//                        grid[((y/3)*3)+((x-1)/3)].erase(board[y][x-1]);
//                        board[y][x-1] = '.';
//                    }
//                }
//                return;
//            }
//            while (!possible.empty()) {
//                char popped = *(possible.begin());
//                possible.erase(popped);
//                board[y][x] = popped;
//                hor[x].insert(popped);
//                ver[y].insert(popped);
//                grid[((y/3)*3)+(x/3)].insert(popped);
//                if (y==8 && x==8) {
//                    res = true;
//                    return;
//                }
//                if (x==8)
//                    helper(board, copyboard, 0, y+1, res, hor, ver, grid);
//                else
//                    helper(board, copyboard, x+1, y, res, hor, ver, grid);
//                if (res) return;
//                if (possible.empty()) {
//                    if (x==0) {
//                        if (copyboard[y-1][8]=='.') {
//                            hor[8].erase(board[y-1][8]);
//                            ver[y-1].erase(board[y-1][8]);
//                            grid[(((y-1)/3)*3)+(8/3)].erase(board[y-1][8]);
//                            board[y-1][8] = '.';
//                        }
//                    }
//                    else {
//                        if (copyboard[y][x-1]=='.') {
//                            hor[x-1].erase(board[y][x-1]);
//                            ver[y].erase(board[y][x-1]);
//                            grid[((y/3)*3)+((x-1)/3)].erase(board[y][x-1]);
//                            board[y][x-1] = '.';
//                        }
//                    }
//                }
//            }
//        }
//        else {
//            if (x==8)
//                helper(board, copyboard, 0, y+1, res, hor, ver, grid);
//            else
//                helper(board, copyboard, x+1, y, res, hor, ver, grid);
//        }
//    }
// public:
//    void solveSudoku(vector<vector<char>>& board)
//    {
//        vector<unordered_set<char>> hor(9, unordered_set<char>{});
//        vector<unordered_set<char>> ver(9, unordered_set<char>{});
//        vector<unordered_set<char>> grid(9, unordered_set<char>{});
//
//        bool res{false};
//        auto copyboard = board;
//        helper(board, copyboard, 0, 0, res, hor, ver, grid);
//    }
//};
