#ifndef SEARCH_H_
#define SEARCH_H_

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "table.h"
using namespace std;

/** @file */

/**
 * Finds if a pattern is present on a given text using the naive string-match algorithm
 * @param text input where to find the pattern
 * @param pattern string to match in the text
 * @return true if finds a match or false otherwise
 */
bool naiveMatch(string& text, string& pattern);

/**
 * Determines the alphabet from a given string
 * @param string from which to determine the alphabet
 * @return alphabet containing non-repeated characters from the input string
 */
string getAlphabet(string& s);

/**
 * Computes the transition table for a given pattern
 * @param pattern string input from which the transition table is created
 * @return Table type object containing all accepted transitions
 */
Table computeTransition(string& pattern);

/**
 * Finds if a pattern is present on a given text using the finite automata string-match algorithm
 * @param table previously processed state machine table
 * @param text input where to find the pattern
 * @param pattern string to match in the text
 * @return true if finds a match or false otherwise
 */
bool finiteAutomatonMatch(Table table, string& text, string& pattern);

#endif // SEARCH_H_
