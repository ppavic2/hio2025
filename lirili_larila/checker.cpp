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
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <bitset>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

// Use one of the following functions to output the points to the contestant.
// The first accepts a double and outputs it.
// The second accepts a fraction and outputs it.

void finish(double score, const string& message) {
  cout << score << endl;
  cout << message << endl;
  exit(0);
}


const int N = 1e6 + 500;

int n, m;
vector<int> v[N];

void bfs(int start, vector<int> &dist) {
	dist = vector<int>(n + 1, -1);
	dist[start] = 0;
	queue<int> Q; Q.push(start);
	for(;!Q.empty();Q.pop()) {
		int cur = Q.front();
		for(int nxt : v[cur]) {
			if(dist[nxt] == -1) {
				dist[nxt] = dist[cur] + 1;
				Q.push(nxt);
			}
		}
	}
}

pair<int,int> count_pair(int u, int v) {
	vector<int> dist_u, dist_v;
	bfs(u, dist_u);
	bfs(v, dist_v);
	for(int i = 1;i <= n;i++)
		if(dist_u[i] == -1 || dist_v[i] == -1) return {-1, -1};
	int cnt_a = 0, cnt_b = 0;
	for(int i = 1;i <= n;i++) {
		if(dist_u[i] < dist_v[i]) cnt_a++;
		if(dist_v[i] < dist_u[i]) cnt_b++;
	}
	return {cnt_a, cnt_b};
}

// Helper functions.
 
/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream &fin, ifstream &foff, ifstream &fout) {
  const string WRONG_OUTPUT_FORMAT = "Wrong output format.";
  const string TEST_DATA_ERROR = "Official input or output error.";
  const string WRONG_N = "Invalid number of operations.";
  const string WRONG_LABEL = "Invalid register label.";
  const string WRONG_VALUE = "Invalid value of a register.";
  const string WRONG_ANS = "Wrong answer.";
  const string CORRECT = "Correct.";

  // Read official input
  int a, b;
  if (!(fin >> n >> m >> a >> b)) finish(0, TEST_DATA_ERROR);
  for (int i = 0;i < m;i++) {
  	int x, y;
  	if(!(fin >> x >> y)) finish(0, TEST_DATA_ERROR);
  	if(!(1 <= x && x <= n && 1 <= y && y <= n)) finish(0, TEST_DATA_ERROR);
  	v[x].push_back(y);
  	v[y].push_back(x);
  }
  int u_off, v_off, u_con, v_con;
  if (!(foff >> u_off >> v_off)) finish(0, TEST_DATA_ERROR);
  if (!(1 <= u_off && u_off <= n && 1 <= v_off && v_off <= n)) finish(0, TEST_DATA_ERROR);
  if (!(fout >> u_con >> v_con)) finish(0, WRONG_ANS);
  if (!(1 <= u_con && u_con <= n && 1 <= v_con && v_con <= n)) finish(0, WRONG_ANS);
  if (count_pair(u_off, v_off) != (pair<int,int>){a, b}) finish(0, TEST_DATA_ERROR);
  if (count_pair(u_con, v_con) != (pair<int,int>){a, b}) finish(0, WRONG_ANS);
  finish(1, CORRECT);
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
