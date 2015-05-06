#include "search.h"

bool naiveStringMatch(string &t, string &p) {
	int n = t.size(); // text size
	int m = p.size(); // pattern size

	for (int s = 0; s <= n-m; s++) {
		if (p == t.substr(s,s+m))
			return true;
	}
	return false;
}