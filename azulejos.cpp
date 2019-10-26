#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
int const MAX = 5e5 + 5;
int n, h, p;

struct Tile {
	int id, h, p;
}b[MAX], f[MAX];

bool cmp(Tile a, Tile b) {
	return a.p < b.p;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i].p);
	}
	for (int i = 0; i < n; i++) {
		b[i].id = i + 1;
		scanf("%d", &b[i].h);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &f[i].p);
	}
	for (int i = 0; i < n; i++) {
		f[i].id = i + 1;
		scanf("%d", &f[i].h);
	}
	sort(b, b + n, cmp);
	sort(f, f + n, cmp);

	vector<int> b_ans(n);
	vector<int> f_ans(n);
	set< pair<int, int> > b_s;
	set< pair<int, int> > f_s;
	set< pair<int, int> > ::iterator b_it;
	set< pair<int, int> > ::iterator f_it;
	int b_idx = 0, f_idx = 0;
	for (int i = 0; i < n; i++) {
		if (b_s.empty()) {
			while (b_idx < n) {
				b_s.insert(make_pair(b[b_idx].h, b[b_idx].id));
				b_idx++;
				if (b[b_idx].p != b[b_idx - 1].p) {
					break;
				}
			}
		}
		if (f_s.empty()) {
			while (f_idx < n) {
				f_s.insert(make_pair(f[f_idx].h, f[f_idx].id));
				f_idx++;
				if (f[f_idx].p != f[f_idx - 1].p) {
					break;
				}
			}
		}
		
		if (b_s.size() < f_s.size()) {
			int curbh = b_s.begin()->first;
			int curbid = b_s.begin()->second;
			f_it = f_s.lower_bound(make_pair(curbh, -1));
			if (f_it == f_s.begin()) {
				printf("impossible\n");
				return 0;
			}
			f_it = prev(f_it);
			b_ans[i] = curbid;
			b_s.erase(b_s.begin());
			f_ans[i] = f_it->second;
			f_s.erase(f_it);
		}
		else {
			int curfh = f_s.begin()->first;
			int curfid = f_s.begin()->second;
			b_it = b_s.upper_bound(make_pair(curfh, n + 1));
			if (b_it == b_s.end()) {
				printf("impossible\n");
				return 0;
			}
			f_ans[i] = curfid;
			f_s.erase(f_s.begin());
			b_ans[i] = b_it->second;
			b_s.erase(b_it);
		}
	}

	int sz = b_ans.size();
	for (int i = 0; i < sz; i++) {
		printf("%d%c", b_ans[i], i == (sz - 1) ? '\n' : ' ');
	}
	for (int i = 0; i < sz; i++) {
		printf("%d%c", f_ans[i], i == (sz - 1) ? '\n' : ' ');
	}

	
}

