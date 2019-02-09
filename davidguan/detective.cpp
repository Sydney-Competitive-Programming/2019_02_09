#include <bits/stdc++.h>
using namespace std;

typedef double f64;
typedef long long i64;
typedef int i32;
typedef pair<i32, i32> pi32;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef vector<i32> vi32;
typedef deque<i32> di32;

#define all(c) (c).begin(), (c).end()
#define REP(i, a, b) for (auto i = a; i < b; i++)
#define REPA(i, a, b, acc) for (auto i = a; i < b; i += acc)
#define PB push_back
#define PF push_front
#define TR(c, it) for (auto(it) = (c).begin(); (it) != (c).end(); (it)++)

i32 n, m;
//             ID                type                ID
unordered_map<i32, unordered_map<i32, unordered_set<i32>>> c;
unordered_map<i32, bool> h;
i32 couter = 0;
vector<unordered_map<i32, bool>> notSList;

void validate() {
  unordered_map<i32, bool> notS;
  // Check the claims about honest.
  REP(i, 1, n + 1) {
    TR(c[i][1], it) {
      if (h[i]) {
        if (!h[*it]) return;
      } else {
        if (h[*it]) return;
      }
    }
    TR(c[i][2], it) {
      if (h[i]) {
        if (h[*it]) return;
      } else {
        if (!h[*it]) return;
      }
    }

    TR(c[i][3], it) {
      if (notS.find(*it) != notS.end()) {
        if (notS[*it] == h[i]) {
          return;
        }
      } else {
        notS[*it] = !h[i];
      }
    }
  }
  i32 count = 0;
  TR(notS, it) {
    if (!it->second) count++;
    if (count > 1) {
      return;
    }
  }
  // out << "size" << notS.size() << "\n";

  // TR(notS, it) {
  //   out << it->first << " " << it->second << "\n";
  // }
  notSList.push_back(notS);

  // Check the claims about the stoler, at most one can be it.
}

void visit(i32 id) {
  if (id == n) {
    // You can uncomment code below to view the comb.
    // REP(i, 1, n + 1) {
    //   out << "  h[" << i << "] is: " << h[i];
    // }
    // out << "\n";

    validate();
    return;
  }

  h[id + 1] = true;
  visit(id + 1);
  h[id + 1] = false;
  visit(id + 1);
}

i32 main() {
  ios::sync_with_stdio(false);  // Makes IO faster, remove this line if C style scanf/printf needed.
  ifstream in("detectivein.txt");
  ofstream out("detectiveout.txt");
  in >> n >> m;

  REP(i, 0, m) {
    i32 x, y, t;
    in >> x >> y >> t;
    c[x][t].insert(y);
  }

  h[1] = true;
  visit(1);
  h[1] = false;
  visit(1);

  if (notSList.empty()) {
    out << "MISTAKE"
        << "\n";
    return 0;
  }

  set<i32> potential;
  set<i32> impossible;
  TR(notSList, s) {
    TR(*s, it) {
      if (it->second) {
        impossible.insert(it->first);
      } else {
        potential.insert(it->first);
      }
    }
  }

  if (potential.size()) {
    TR(potential, it) {
      out << *it << "\n";
    }
    return 0;
  }
  if (impossible.size() == n) {
    out << "MISTAKE"
        << "\n";
    return 0;
  }
  REP(i, 1, n + 1) {
    if (impossible.count(i)) continue;
    out << i << "\n";
  }
  return 0;
}
