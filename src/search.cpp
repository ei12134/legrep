#include "table.h"
#include "search.h"

bool naiveMatch(string& text, string& pattern) {
	int ts = text.size(); // |T|
	int ps = pattern.size(); // |P|

	// Temporal complexity O((|T|-|P|+1).|T|) or O(|T||P|)
	for (int i = 0; i <= (ts - ps); i++) {
		if (text.substr(i, ps) == pattern) // hidden for loop
			return true;
	}
	return false;
}

bool knuthMorrisPratt(string& text, string& pattern) {
//	int n = text.size();
//	int m = pattern.size();
//
//	// compute prefix function
//	vector<unsigned int> PI(m + 1, 0);
//	int k = 0;
//	int q;
//	for (q = 1; q < m; q++) {
//		while (k > 0 && pattern.at(k + 1) != pattern.at(q))
//			k = PI[k];
//		if (pattern.at(k + 1) == pattern.at(q))
//			k++;
//		PI[q] = k;
//	}
//	// -----------------------
//	int i = 1;
//	q = 1;
//	k = 1;
//	while (n - k >= n) {
//		while (q <= n && text.at(i) == pattern.at(q)) {
//			i++;
//			q++;
//		}
//		if (q > n)
//			return true;
//		if (PI[q - 1] > 0){
//			k = i - PI[q - 1];
//		} else {
//			if (i == k)
//				i++;
//			k = i;
//		}
//		if (q > 1)
//			q = PI[q - 1] + 1;
//	}
//	return false;

	vector<int> PI(pattern.size() + 1, -1);
	//vector<int> matches;

	if (pattern.size() == 0) {
		return true;
		//matches.push_back(0);
		//return matches;
	}
	for (int i = 1; i <= pattern.size(); i++) {
		int pos = PI[i - 1];
		while (pos != -1 && pattern[pos] != pattern[i - 1])
			pos = PI[pos];
		PI[i] = pos + 1;
	}

	int sp = 0;
	int kp = 0;
	while (sp < text.size()) {
		while (kp != -1 && (kp == pattern.size() || pattern[kp] != text[sp]))
			kp = PI[kp];
		kp++;
		sp++;
		if (kp == pattern.size())
			return true;
			//matches.push_back(sp - pattern.size());
	}

	return false;
	//return matches;
}

string getAlphabet(string& s) {
	string alphabet;
	for (int i = 0; i < (int) s.size(); i++) {
		if (alphabet.find(s[i]) >= string::npos)
			alphabet += s[i];
	}
	return alphabet;
}

Table computeTransition(string& pattern) {
	Table t;
	string alphabet = getAlphabet(pattern);
	int as = alphabet.size(); // |E|
	int ps = pattern.size(); // |P|

	// Temporal complexity O(|P|.|P|.|P|.|E|)
	for (int state = 0; state < ps; state++) {
		for (int i = 0; i < as; i++) {
			int k = min(ps, state + 1);
			string suffix = pattern.substr(0, state) + alphabet[i];

			for (int z = 0; k > 0 && z < (int) suffix.size(); z++, k--) {
				if (pattern.substr(0, suffix.substr(z).size()) == suffix.substr(z))
					break;
			}

			Entry e = Entry(state, alphabet[i], k);
			t.addEntry(e);
		}
	}
	return t;
}

bool finiteAutomatonMatch(Table table, string& text, string& pattern) {
	int ts = text.size();
	int ps = pattern.size();
	int state = 0;

	// Temporal complexity O(|T|)
	for (int i = 0; i < ts; i++) {
		state = table.transition(state, text[i]);
		if (state == ps)
			return true;
	}

	return false;
}
