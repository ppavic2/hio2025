// Checker for basic communication-style tasks to be used by HSIN evaluator.
//
// This task type assumes two actors exchanging a single message. The utility of
// this checker program is two-fold, as explained in the following (typical)
// sequence of events:
//
//   1) `./contestant_sol < off_in > actor_1_out`
//      The solution is ran using the official test case file as input.
//      The input file specifies that the contestant's program should take
//      the role of the first actor.
//   2) `./checker actor1 off_in off_config actor_1_out actor_2_in`
//      The checker validates the output from step 1) and generates the input
//      file for the second invocation of contestant's solution. If validation
//      fails, the checker outputs 0, ending the evaluation with WA verdict.
//   3) `./contestant_sol < actor_2_in > actor_2_out`
//      The solution is ran using the actor_2_in file generated by the first
//      checker invocation. That file specifies that the contestant's program
//      should take the role of the second actor
//   4) `./checker actor2 off_in off_config actor_1_out actor_2_in actor_2_out`
//      The checker validates the output from step 3) and judges the correctness
//      of the solution with stdout having standard semantics.
//
// This should *not* be used for CMS!
//
// Usage:
//     [checker] actor1 [official_input] [official_config] [actor_1_output]
//         [actor_2_input]
//
//     [checker] actor2 [official_input] [official_config] [actor_1_output]
//         [actor_2_input] [actor_2_output]
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
#include <unordered_map>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

// Use one of the following functions to output the points to the contestant.
// The first accepts a double and outputs it.
// The second accepts a fraction and outputs it.

void finish(double score) {
  cout << score << endl;
  exit(0);
}

void finish(llint points_awarded, llint points_max) {
  cout << points_awarded << "/" << points_max << endl;
  exit(0);
}

// Helper functions.

vector<string> split(const string &a, const string &delim) {
  vector<string> ans;
  int ptr = 0;
  for (size_t f_pos; (f_pos = a.find(delim, ptr)) != string::npos;) {
    ans.push_back(a.substr(ptr, f_pos - ptr));
    ptr = f_pos + delim.size();
  }
  ans.push_back(a.substr(ptr));
  return ans;
}

bool get_output(ifstream &fin, string &s) {
	return bool(fin >> s);
}
bool to_int(const string &s, int &x) {
	int sgn = 1, i = 0;
	x = 0;
	if (s.empty()) return 0;
	if (s[0] == '-') sgn = -1, ++i;
	for (; i < (int)s.length(); ++i) {
		x *= 10;
		if (s[i] < '0' || s[i] > '9') return 0;
		x += s[i] - '0';
	}
	x *= sgn;
	return 1;
}

// Main

const int N = 16;

int type, n, k, t;
int A[N], B[N];
vector<pair<string, int>> act1, act2;

int load_test_data(ifstream &fin, ifstream &fconf) {
	fconf >> n >> k;
	for (int i = 0; i < k; ++i) fconf >> A[i];
	for (int i = 0; i < k; ++i) fconf >> B[i];
	
	int solution = 0;
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < k; ++j) {
			solution += A[i] == B[j];
		}
	}
	
	fin >> type >> n >> k;
	for (int i = 0; i < k; ++i) fin >> A[i];
	fin >> t;
	
	return solution;
}

vector<string> states[2];
string current_state;

void gen_valid_states(int p, int c) {
	if ((int)current_state.length() == n) {
		if (p == c) states[0].push_back(current_state);
		if (p == c + 1) states[1].push_back(current_state);
		return ;
	}
	if (p + n - (int)current_state.length() < c) return ;
	if (c + 1 + n - (int)current_state.length() < p) return ;
	current_state += '.';
	gen_valid_states(p, c);
	current_state.back() = 'P';
	gen_valid_states(p + 1, c);
	current_state.back() = 'C';
	gen_valid_states(p, c + 1);
	current_state.pop_back();
}

int get_op(vector<pair<string, int>>& act, const string& state) {
	for (auto& p : act) {
		if (p.first == state) return p.second;
	}
	assert(0);
	return 0;
}

void get_output(int t, vector<string>& states, ifstream &act_out, vector<pair<string, int>>& act) {
	for (int i = 0; i < t; ++i) {
		string out;
		string ans_type;
		int ans;
		
		if (!get_output(act_out, ans_type)) {
			finish(0);
		}

		if (ans_type != "!" && ans_type != "+") {
			finish(0);
		}
		
		if (!get_output(act_out, out)) {
			finish(0);
		}
		if (!to_int(out, ans)) {
			finish(0);
		}
		
		if (ans_type == "+") {
			if (ans < 1 || ans > (int)states[i].length()) {
				finish(0);
			}
			if (states[i][ans - 1] != '.') {
				finish(0);
			}
		} else {
			if (ans < 0 || ans > (int)states[i].length()) {
				finish(0);
			}
		}
		
		if (ans_type == "!") act.push_back({states[i], -ans});
		else act.push_back({states[i], ans});
	}
	
	act_out >> ws;
	if (act_out.peek() != EOF) finish(0);
}

/**
 * The main checking function for actor 1.
 * @param fin   official input (input stream)
 * @param fconf official config (input stream)
 * @param a1out actor 1 output (input stream)
 * @param a2in  actor 2 input (output stream)
 */
void check_a1(ifstream &fin, ifstream &fconf, ifstream &a1out, ofstream &a2in) {
	load_test_data(fin, fconf);
	
	gen_valid_states(0, 0);
	
	get_output(t, states[0], a1out, act1);
	
	a2in << 2 << '\n' << n << ' ' << k << '\n';
	for (int i = 0; i < k; ++i) {
		if (i) a2in << ' ';
		a2in << B[i];
	}
	a2in << '\n';
	a2in << (int)states[1].size() << '\n';
	for (string& state : states[1]) {
		a2in << state << '\n';
	}
	
	a2in.close();
	
	finish(1);
	// The function MUST terminate before this line via finish()!
}


/**
 * The main checking function for actor 2.
 * @param fin   official input (input stream)
 * @param fconf official config (input stream)
 * @param a1out actor 1 output (input stream)
 * @param a2in  actor 2 input (input stream)
 * @param a2out actor 2 output (input stream)
 */
void check_a2(ifstream &fin, ifstream &fconf, ifstream &a1out, ifstream &a2in,
              ifstream &a2out) {
	int solution = load_test_data(fin, fconf);
	
	gen_valid_states(0, 0);
	
	get_output(t, states[0], a1out, act1);
	
	a2in >> type >> n >> k;
	for (int i = 0; i < k; ++i) a2in >> B[i];
	a2in >> t;
	
	get_output(t, states[1], a2out, act2);
	
	string state = "";
	for (int i = 0; i < n; ++i) state += '.';
	
	bool turn = 0;
	int ans = -1;
	
	while (ans == -1) {
		int next_op;
		
		if (turn) next_op = get_op(act2, state);
		else next_op = get_op(act1, state);
		
		if (next_op > 0) {
			state[next_op - 1] = (turn? 'C' : 'P');
		} else {
			ans = -next_op;
		}
		turn ^= 1;
	}
	
	if (ans != solution) {
		finish(0);
	}
	
	finish(1);
	// The function MUST terminate before this line via finish()!
}

int main(int argc, char *argv[]) {
  assert(argc >= 6);

  ifstream fin(argv[2]);
  ifstream fconf(argv[3]);
  ifstream a1out(argv[4]);

  assert(!fin.fail() && !fconf.fail() && !a1out.fail());

  if (strcmp(argv[1], "actor1") == 0) {
    ofstream a2in(argv[5]);
    assert(!a2in.fail());
    check_a1(fin, fconf, a1out, a2in);
  }

  if (strcmp(argv[1], "actor2") == 0) {
    ifstream a2in(argv[5]);
    ifstream a2out(argv[6]);
    assert(!a2in.fail() && !a2out.fail());
    check_a2(fin, fconf, a1out, a2in, a2out);
  }

  assert(false);

  return 0;
}
