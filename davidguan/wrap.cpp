#include <bits/stdc++.h>
using namespace std;

typedef double f64;
typedef long long i64;
typedef int i32;
typedef vector<i32> vi32;
typedef deque<i32> di32;

#define all(c) (c).begin(), (c).end()
#define REP(i, a, b) for (auto i = a; i < b; i++)
#define TR(c, it) for (auto(it) = (c).begin(); (it) != (c).end(); (it)++)

i32 bestLineDistance(vector<string> line) {
  if (line.empty()) return 0;

  i32 ret = line[0].size();
  REP(i, 1, line.size()) {
    ret += 1 + line[i].size();
  }
  return ret;
}

i32 main() {
  ios::sync_with_stdio(false);  // Makes IO faster, remove this line if C style scanf/printf needed.
  ifstream in("wrapin.txt");
  ofstream out("wrapout.txt");

  char style;
  i32 w;
  in >> style >> w;

  // Get the words.
  vector<string> words;
  string line;
  while (getline(in, line)) {
    if (line == "#") break;

    i32 l = -1, r;
    string cur = "";
    REP(i, 0, line.size()) {
      if (line[i] == ' ') {
        if (cur != "") {
          words.push_back(cur);
          cur.clear();
        }
        continue;
      }
      cur += line[i];
      if (i == (line.size() - 1) && cur.size()) {
        words.push_back(cur);
      }
    }
  }

  vector<vector<string>> lines;
  vector<string> cur;
  // Get the lines.
  REP(i, 0, words.size()) {
    if ((bestLineDistance(cur) + words[i].size() + 1) <= w) {
      cur.push_back(words[i]);
    } else {
      lines.push_back(cur);
      cur.clear();
      cur.push_back(words[i]);
    }
  }
  if (cur.size()) lines.push_back(cur);

  // Justifies the line.
  if (style == 'L') {
    TR(lines, i) {
      REP(j, 0, (*i).size()) {
        if (j > 0) out << " ";
        out << (*i)[j];
      }
      out << "\n";
    }
  }
  if (style == 'R') {
    TR(lines, i) {
      i32 dist = bestLineDistance(*i);
      string spaces(w - dist, ' ');
      out << spaces;
      REP(j, 0, (*i).size()) {
        if (j > 0) out << " ";
        out << (*i)[j];
      }
      out << "\n";
    }
  }

  if (style == 'J') {
    REP(i, 0, lines.size()) {
      if (i == (lines.size() - 1)) {
        REP(j, 0, lines[i].size()) {
          if (j > 0) out << " ";
          out << lines[i][j];
        }
        out << "\n";
        continue;
      }

      i32 count = lines[i].size() - 1;
      i32 slots = w - bestLineDistance(lines[i]) + count;
      out << lines[i][0];
      REP(j, 1, lines[i].size()) {
        string spaces(slots / count + ((j <= slots % count) ? 1 : 0), ' ');
        out << spaces;
        out << lines[i][j];
      }
      out << "\n";
    }
  }
  return 0;
}
