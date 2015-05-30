#ifndef SEARCH_H_
#define SEARCH_H_

#include <string>
#include <vector>

#include "table.h"

using std::string;
using std::vector;

/** @file */

/**
 * Finds if a pattern is present on a given text using the naive string-matching algorithm
 * @param text input where to find the pattern
 * @param pattern string to match in the text
 * @return indexes for each of the first character in the text matching the pattern
 */
vector<int> naive(const string& text, const string& pattern);

/**
 * Determines the alphabet from the pattern
 * @param pattern is the input string from which the alphabet is determined
 * @return alphabet containing non-repeated characters from the input string
 */
string getAlphabet(const string& pattern);

/**
 * Computes the transition table for a given pattern
 * @param pattern string input from which the transition table is created
 * @return Table type object containing all accepted transitions
 */
Table computeStateTransitionTable(const string& pattern);

/**
 * Finds if a pattern is present on a given text using the finite automata string-matching algorithm
 * @param text input where to find the pattern
 * @param pattern string to match in the text
 * @param table previously processed state machine transitions table
 * @return indexes for each of the first character in the text matching the pattern
 */
vector<int> finiteAutomaton(const string& text, const string& pattern, const Table& table);

/**
 * generates prefix function used in the Knuth-Morris-Pratt string-match algorithm
 * @param pattern string
 * @return vector of indexes
 */
vector<int> computePrefixFunction(const string& pattern);

/**
 * Finds if a pattern is present on a given text using the Knuth-Morris-Pratt string-matching algorithm
 * @param text input where to find the pattern
 * @param pattern string to match in the text
 * @param pi pre-computed prefix indexes
 * @return indexes for each of the first character in the text matching the pattern
 */
vector<int>  knuthMorrisPratt(const string& text, const string& pattern, const vector<int>& pi);

#endif // SEARCH_H_
