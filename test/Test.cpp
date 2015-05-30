#include <string>
#include <iostream>
#include "../src/search.h"
#include "../src/table.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
using std::cout;
using std::endl;

void naiveAlpha() {
	string text = "The quick brown fox jumps over the lazy dog";
	string p1 = "The q";
	string p2 = "g";
	string p3 = "he";
	string p4 = "o";
	string p5 = "";
	string p6 = "zero";
	vector<int> result;

	// Single match beginning & end
	result = naive(text, p1);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	result = naive(text, p2);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 1);

	// Multiple matches
	result = naive(text, p3);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], 1);
	ASSERT_EQUAL(result[1], 32);

	result = naive(text, p4);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 12);
	ASSERT_EQUAL(result[1], 17);
	ASSERT_EQUAL(result[2], 26);
	ASSERT_EQUAL(result[3], 41);

	result = naive(text, p5);
	ASSERT_EQUAL(result.size(), text.size());

	// No matches
	result = naive(text, p6);
	ASSERT_EQUAL(result.size(), 0);
}

void naiveNumeric() {
	string text = "01234567890 1337 3141592653589793";
	string p1 = "0123456789";
	string p2 = "93";
	string p3 = "89";
	string p4 = "5";
	vector<int> result;

	// Single match beginning & end
	result = naive(text, p1);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	result = naive(text, p2);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 2);

	// Multiple matches
	result = naive(text, p3);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], 8);
	ASSERT_EQUAL(result[1], 28);

	result = naive(text, p4);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 5);
	ASSERT_EQUAL(result[1], 21);
	ASSERT_EQUAL(result[2], 25);
	ASSERT_EQUAL(result[3], 27);
}

void naiveSymbol() {
	string text = "çãáà\? [] /()=!#&|$#!#  '-<>>|";
	string p1 = "çã";
	string p2 = ">|";
	string p3 = ">";
	string p4 = " ";
	vector<int> result;

	// Single match beginning & end
	result = naive(text, p1);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	result = naive(text, p2);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 2);

	// Multiple matches
	result = naive(text, p3);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], text.size() - 3);
	ASSERT_EQUAL(result[1], text.size() - 2);

	result = naive(text, p4);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 9);
	ASSERT_EQUAL(result[1], 12);
	ASSERT_EQUAL(result[2], 25);
	ASSERT_EQUAL(result[3], 26);
}

void naiveTime() {
	const int textSizeIncrements = 7;
	const int repetitionsPerSize = 5;
	string text =
			"Murphy's Original Law "
					"If there are two or more ways to do something, and one of those ways can result in a catastrophe, then someone will do it."
					"Murphy's Law"
					"If anything can go wrong -- it will."
					"Murphy's First Corollary"
					"Left to themselves, things tend to go from bad to worse."
					"Murphy's Second Corollary"
					"It is impossible to make anything foolproof because fools are so ingenious."
					"Quantised Revision of Murphy's Law"
					"Everything goes wrong all at once."
					"Murphy's Constant"
					"Matter will be damaged in direct proportion to its value."
					"The Murphy Philosophy"
					"Smile... tomorrow will be worse. ";
	string pattern = "a";

	cout << "\n\n*** NAIVE string matching ***\n\n";

	clock_t startTime = clock();
	for (int n = 0; n < textSizeIncrements;
			n++, text += text + text + text + text) {
		for (int i = 0; i < repetitionsPerSize; i++)
			naive(text, pattern);

		clock_t endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
		cout << "String matching for text size = " << text.size() << "     \t"
				<< "Total time in seconds = " << timeInSeconds << "     \t"
				<< "Average time per search in seconds = "
				<< timeInSeconds / repetitionsPerSize << endl;
	}
}

void finiteAutomatonAlpha() {
	string text = "The quick brown fox jumps over the lazy dog";
	string p1 = "The q";
	string p2 = "g";
	string p3 = "he";
	string p4 = "o";
	string p5 = "";
	string p6 = "zero";
	vector<int> result;
	Table table;

	// Single match beginning & end
	table = computeStateTransitionTable(p1);
	result = finiteAutomaton(text, p1, table);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	table = computeStateTransitionTable(p2);
	result = finiteAutomaton(text, p2, table);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 1);

	// Multiple matches
	table = computeStateTransitionTable(p3);
	result = finiteAutomaton(text, p3, table);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], 1);
	ASSERT_EQUAL(result[1], 32);

	table = computeStateTransitionTable(p4);
	result = finiteAutomaton(text, p4, table);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 12);
	ASSERT_EQUAL(result[1], 17);
	ASSERT_EQUAL(result[2], 26);
	ASSERT_EQUAL(result[3], 41);

	table = computeStateTransitionTable(p5);
	result = finiteAutomaton(text, p5, table);
	ASSERT_EQUAL(result.size(), text.size());

	// No matches
	table = computeStateTransitionTable(p6);
	result = finiteAutomaton(text, p6, table);
	ASSERT_EQUAL(result.size(), 0);
}

void finiteAutomatonNumeric() {
	string text = "01234567890 1337 3141592653589793";
	string p1 = "0123456789";
	string p2 = "93";
	string p3 = "89";
	string p4 = "5";
	vector<int> result;
	Table table;

	// Single match beginning & end
	table = computeStateTransitionTable(p1);
	result = finiteAutomaton(text, p1, table);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	table = computeStateTransitionTable(p2);
	result = finiteAutomaton(text, p2, table);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 2);

	// Multiple matches
	table = computeStateTransitionTable(p3);
	result = finiteAutomaton(text, p3, table);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], 8);
	ASSERT_EQUAL(result[1], 28);

	table = computeStateTransitionTable(p4);
	result = finiteAutomaton(text, p4, table);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 5);
	ASSERT_EQUAL(result[1], 21);
	ASSERT_EQUAL(result[2], 25);
	ASSERT_EQUAL(result[3], 27);
}

void finiteAutomatonSymbol() {
	string text = "çãáà\? [] /()=!#&|$#!#  '-<>>|";
	string p1 = "çã";
	string p2 = ">|";
	string p3 = ">";
	string p4 = " ";
	vector<int> result;
	Table table;

	// Single match beginning & end
	table = computeStateTransitionTable(p1);
	result = finiteAutomaton(text, p1, table);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	table = computeStateTransitionTable(p2);
	result = finiteAutomaton(text, p2, table);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 2);

	// Multiple matches
	table = computeStateTransitionTable(p3);
	result = finiteAutomaton(text, p3, table);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], text.size() - 3);
	ASSERT_EQUAL(result[1], text.size() - 2);

	table = computeStateTransitionTable(p4);
	result = finiteAutomaton(text, p4, table);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 9);
	ASSERT_EQUAL(result[1], 12);
	ASSERT_EQUAL(result[2], 25);
	ASSERT_EQUAL(result[3], 26);
}

void finiteAutomatonTime() {
	const int textSizeIncrements = 7;
	const int repetitionsPerSize = 5;
	string text =
			"Murphy's Original Law "
					"If there are two or more ways to do something, and one of those ways can result in a catastrophe, then someone will do it."
					"Murphy's Law"
					"If anything can go wrong -- it will."
					"Murphy's First Corollary"
					"Left to themselves, things tend to go from bad to worse."
					"Murphy's Second Corollary"
					"It is impossible to make anything foolproof because fools are so ingenious."
					"Quantised Revision of Murphy's Law"
					"Everything goes wrong all at once."
					"Murphy's Constant"
					"Matter will be damaged in direct proportion to its value."
					"The Murphy Philosophy"
					"Smile... tomorrow will be worse. ";
	string pattern = "a";

	cout << "\n\n*** FINITE AUTOMATON string matching ***\n\n";

	clock_t startTime = clock();
	Table table = computeStateTransitionTable(pattern);
	for (int n = 0; n < textSizeIncrements;
			n++, text += text + text + text + text) {
		for (int i = 0; i < repetitionsPerSize; i++)
			finiteAutomaton(text, pattern, table);

		clock_t endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
		cout << "String matching for text size = " << text.size() << "     \t"
				<< "Total time in seconds = " << timeInSeconds << "     \t"
				<< "Average time per search in seconds = "
				<< timeInSeconds / repetitionsPerSize << endl;
	}
}

void knuthMorrisPrattAlpha() {
	string text = "The quick brown fox jumps over the lazy dog";
	string p1 = "The q";
	string p2 = "g";
	string p3 = "he";
	string p4 = "o";
	string p5 = "";
	string p6 = "zero";
	vector<int> result;
	vector<int> pi;

	// Single match beginning & end
	pi = computePrefixFunction(p1);
	result = knuthMorrisPratt(text, p1, pi);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	pi = computePrefixFunction(p2);
	result = knuthMorrisPratt(text, p2, pi);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 1);

	// Multiple matches
	pi = computePrefixFunction(p3);
	result = knuthMorrisPratt(text, p3, pi);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], 1);
	ASSERT_EQUAL(result[1], 32);

	pi = computePrefixFunction(p4);
	result = knuthMorrisPratt(text, p4, pi);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 12);
	ASSERT_EQUAL(result[1], 17);
	ASSERT_EQUAL(result[2], 26);
	ASSERT_EQUAL(result[3], 41);

	pi = computePrefixFunction(p5);
	result = knuthMorrisPratt(text, p5, pi);
	ASSERT_EQUAL(result.size(), text.size());

	// No matches
	pi = computePrefixFunction(p6);
	result = knuthMorrisPratt(text, p6, pi);
	ASSERT_EQUAL(result.size(), 0);
}

void knuthMorrisPrattNumeric() {
	string text = "01234567890 1337 3141592653589793";
	string p1 = "0123456789";
	string p2 = "93";
	string p3 = "89";
	string p4 = "5";
	vector<int> result;
	vector<int> pi;

	// Single match beginning & end
	pi = computePrefixFunction(p1);
	result = knuthMorrisPratt(text, p1, pi);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	pi = computePrefixFunction(p2);
	result = knuthMorrisPratt(text, p2, pi);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 2);

	// Multiple matches
	pi = computePrefixFunction(p3);
	result = knuthMorrisPratt(text, p3, pi);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], 8);
	ASSERT_EQUAL(result[1], 28);

	pi = computePrefixFunction(p4);
	result = knuthMorrisPratt(text, p4, pi);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 5);
	ASSERT_EQUAL(result[1], 21);
	ASSERT_EQUAL(result[2], 25);
	ASSERT_EQUAL(result[3], 27);
}

void knuthMorrisPrattSymbol() {
	string text = "çãáà\? [] /()=!#&|$#!#  '-<>>|";
	string p1 = "çã";
	string p2 = ">|";
	string p3 = ">";
	string p4 = " ";
	vector<int> result;
	vector<int> pi;

	// Single match beginning & end
	pi = computePrefixFunction(p1);
	result = knuthMorrisPratt(text, p1, pi);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], 0);

	pi = computePrefixFunction(p2);
	result = knuthMorrisPratt(text, p2, pi);
	ASSERT_EQUAL(result.size(), 1);
	ASSERT_EQUAL(result[0], text.size() - 2);

	// Multiple matches
	pi = computePrefixFunction(p3);
	result = knuthMorrisPratt(text, p3, pi);
	ASSERT_EQUAL(result.size(), 2);
	ASSERT_EQUAL(result[0], text.size() - 3);
	ASSERT_EQUAL(result[1], text.size() - 2);

	pi = computePrefixFunction(p4);
	result = knuthMorrisPratt(text, p4, pi);
	ASSERT_EQUAL(result.size(), 4);
	ASSERT_EQUAL(result[0], 9);
	ASSERT_EQUAL(result[1], 12);
	ASSERT_EQUAL(result[2], 25);
	ASSERT_EQUAL(result[3], 26);
}

void knuthMorrisPrattTime() {
	const int textSizeIncrements = 7;
	const int repetitionsPerSize = 5;
	string text =
			"Murphy's Original Law "
					"If there are two or more ways to do something, and one of those ways can result in a catastrophe, then someone will do it."
					"Murphy's Law"
					"If anything can go wrong -- it will."
					"Murphy's First Corollary"
					"Left to themselves, things tend to go from bad to worse."
					"Murphy's Second Corollary"
					"It is impossible to make anything foolproof because fools are so ingenious."
					"Quantised Revision of Murphy's Law"
					"Everything goes wrong all at once."
					"Murphy's Constant"
					"Matter will be damaged in direct proportion to its value."
					"The Murphy Philosophy"
					"Smile... tomorrow will be worse. ";
	string pattern = "a";

	cout << "\n\n*** KNUTH MORRIS PRATT string matching ***\n\n";

	clock_t startTime = clock();
	vector<int> pi = computePrefixFunction(pattern);
	for (int n = 0; n < textSizeIncrements;
			n++, text += text + text + text + text) {
		for (int i = 0; i < repetitionsPerSize; i++)
			knuthMorrisPratt(text, pattern, pi);

		clock_t endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
		cout << "String matching for text size = " << text.size() << "     \t"
				<< "Total time in seconds = " << timeInSeconds << "     \t"
				<< "Average time per search in seconds = "
				<< timeInSeconds / repetitionsPerSize << endl;
	}
}

void runSuite() {
	cute::suite s;
	s.push_back(CUTE(naiveAlpha));
	s.push_back(CUTE(naiveNumeric));
	s.push_back(CUTE(naiveSymbol));
	s.push_back(CUTE(finiteAutomatonAlpha));
	s.push_back(CUTE(finiteAutomatonNumeric));
	s.push_back(CUTE(finiteAutomatonSymbol));
	s.push_back(CUTE(knuthMorrisPrattAlpha));
	s.push_back(CUTE(knuthMorrisPrattNumeric));
	s.push_back(CUTE(knuthMorrisPrattSymbol));

	s.push_back(CUTE(naiveTime));
	s.push_back(CUTE(finiteAutomatonTime));
	s.push_back(CUTE(knuthMorrisPrattTime));

	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "leGrep");
}

int main() {
	runSuite();
	return 0;
}
