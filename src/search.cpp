#include "search.h"

bool naiveStringMatch(string &t, string &p) {
	int ts = t.size(); // text size
	int ps = p.size(); // pattern size

	for (int i = 0; i <= (ts-ps); i++) {
		if (t.substr(i,ps) == p)
			return true;
	}
	return false;
}