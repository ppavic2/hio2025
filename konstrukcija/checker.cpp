// Checker to be used by HSIN evaluator.
//
// This should *not* be used for CMS!
//
// Usage: [checker] [input] [official_output] [contestant_output] [configuration_file (optional)]
//
// Output (stdout):
//     Score.
//     Textual description (optional).
//
// Score should be output as an integer (0 or 1), or a real (between 0.0 and
// 1.0) or a fraction (between `0/1` and `1/1`, you don't have to
// simplify/reduce the fraction).

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

// Use one of the following functions to output the points to the contestant.
// The first accepts a double and outputs it.
// The second accepts a fraction and outputs it.

void finish(double score, const string& message) {
  cout << score << endl;
  cout << message << endl;
  exit(0);
}

// Helper functions.

int n;
int a[25];
int pos[(1 << 20)];
int vis[(1 << 20)];

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream &fin, ifstream &foff, ifstream &fout) {
  const string TEST_DATA_ERROR = "Official input or output error.";
  const string WRONG_ANS = "Wrong answer.";
  const string CORRECT = "Correct.";
  // Read official input
  if (!(fin >> n)) finish(0, TEST_DATA_ERROR);
  for(int i = 0;i < n;i++)
    if(!(fin >> a[i])) finish(0, TEST_DATA_ERROR);

  int flag = 1;
  for(int i = 0;i < n;i++)
    if((a[i] & 1) && n > 1) flag = 0;
  memset(pos, -1, sizeof pos);
  for(int i = 0;i < n;i++)
    pos[(1 << i)] = i;

  // Read official output

  // Read contestant's output
  if(flag == 0) {
    int val;
    if(!(fout >> val)) finish(0, WRONG_ANS);
    if(val != -1) finish(0, WRONG_ANS);
  } else {
    for(int i = 0;i < (1 << (n - 1));i++) {
      int x, y;
      if(!(fout >> x >> y)) finish(0, WRONG_ANS);
      if(x < 0 || x >= (1 << n)) finish(0, WRONG_ANS);
      if(y < 0 || y >= (1 << n)) finish(0, WRONG_ANS);
      if(vis[x] || vis[y]) finish(0, WRONG_ANS);
      if(pos[x ^ y] == -1) finish(0, WRONG_ANS);
      if(a[pos[x ^ y]] == 0) finish(0.20, WRONG_ANS);
      a[pos[x ^ y]]--;
      vis[x] = vis[y] = 1; 
    }
  }
  finish(1, CORRECT);
  // The function MUST terminate before this line via finish()!
}

int main(int argc, char *argv[]) {
  assert(argc >= 4);

  ifstream fin(argv[1]);
  ifstream foff(argv[2]);
  ifstream fout(argv[3]);

  // Optional, uncomment when using the configuration file for additional
  // information about the testcase.
  // ifstream fconf(argv[4]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, foff, fout);

  // Checker must terminate via finish() before exiting!
  assert(false);
  return 0;
}
