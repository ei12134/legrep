#include "table.h"
#include "search.h"

bool naiveMatch(string& text, string& pattern)
{
	int ts = text.size(); // |T|
	int ps = pattern.size(); // |P|

	// Temporal complexity O((|T|-|P|+1).|T|) or O(|T||P|)
	for (int i = 0; i <= (ts-ps); i++) {
		if (text.substr(i,ps) == pattern) // hidden for loop
			return true;
	}
	return false;
}

string getAlphabet(string& s)
{
	string alphabet;
	for (int i = 0 ; i < (int)s.size(); i++) {
		if (alphabet.find(s[i]) >= string::npos)
			alphabet += s[i];
	}
	return alphabet;
}

Table computeTransition(string& pattern)
{
	Table t;
	string alphabet = getAlphabet(pattern);
	int as = alphabet.size(); // |E|
	int ps = pattern.size(); // |P|

	// Temporal complexity O(|P|.|P|.|P|.|E|)
	for (int state = 0 ; state < ps; state++){
		for (int i = 0; i < as; i++){
			int k = min(ps,state+1);
			string suffix = pattern.substr(0,state) + alphabet[i];

			for (int z = 0; k > 0 && z < (int)suffix.size(); z++, k--){
				if (pattern.substr(0,suffix.substr(z).size()) == suffix.substr(z))
					break;
			}
			
			Entry e = Entry(state,alphabet[i],k);
			t.addEntry(e);
		}		
	}
	return t;
}

bool finiteAutomatonMatch(Table table, string& text, string& pattern)
{
	int ts = text.size();
	int ps = pattern.size();
	int state = 0;

	// Temporal complexity O(|T|)
	for (int i = 0; i < ts ; i++){
		state = table.transition(state,text[i]);
		if (state == ps)
			return true;
	}

	return false;
}