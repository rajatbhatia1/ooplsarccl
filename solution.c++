// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <climits>
#include <vector>


using namespace std;

// ------------
// collatz_read
// ------------

std::vector<int> cache(0,0);

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int calc_collatz_(int n)
{
  int count = 1;
  int orig_n = n;
  while (n!=1) {
    if ((n<(int)cache.size()) && (cache[n]!=0)) {
      if ((int)cache.size()<=orig_n) {
	cache.resize(2*orig_n, 0);
      }
      // std::cout << "Caching " << orig_n << ":" << count + cache[n] - 1 
      // 		<< " at n=" << n << endl;
      cache[orig_n] = count + cache[n] - 1;
      return cache[orig_n];
    }
    if ((n % 2)==0) {
      n = n / 2;
    } else {
      n = 3 *n + 1;
    }
    ++count;
  }
  if ((int)cache.size()<=orig_n) {
    cache.resize(2*orig_n, 0);
  }
  cache[orig_n] = count;
  //  std::cout << "Caching " << orig_n << ":" << count << endl;
  return count;
}

int collatz_eval (int i, int j) {
  if (j<i) {
    std::swap(i,j);
  }
  int max_count = calc_collatz_(j);
  for (int n=i;n<j;n++) {
    max_count = std::max(max_count, calc_collatz_(n));
  }
  return max_count;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}

