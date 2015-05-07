#include <string>
#include "../src/search.h"
#include "../src/table.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

void naive() {
	std::string alpha = "The quick brown fox jumps over the lazy dog";
	std::string p1 = "The";
	std::string p2 = " The apsdghidamkbrowpago";
	std::string p3 = " fox j";
	std::string p4 = "ovr t";
	std::string p5 = "y dog";
	std::string p6 = "z dog";
	std::string p7 = "quick brown ";
	ASSERT_EQUAL(naiveMatch(alpha, p1), true);
	ASSERT_EQUAL(naiveMatch(alpha, p2), false);
	ASSERT_EQUAL(naiveMatch(alpha, p3), true);
	ASSERT_EQUAL(naiveMatch(alpha, p4), false);
	ASSERT_EQUAL(naiveMatch(alpha, p5), true);
	ASSERT_EQUAL(naiveMatch(alpha, p6), false);
	ASSERT_EQUAL(naiveMatch(alpha, p7), true);

	std::string numbers = "01234567890 1337 3141592653589793";
	std::string p8 = "01234567890";
	std::string p9 = "012345678901";
	std::string p10 = " 1337";
	std::string p11 = "3144";
	std::string p12 = "3";
	std::string p13 = "999";
	std::string p14 = "793";
	ASSERT_EQUAL(naiveMatch(numbers, p8), true);
	ASSERT_EQUAL(naiveMatch(numbers, p9), false);
	ASSERT_EQUAL(naiveMatch(numbers, p10), true);
	ASSERT_EQUAL(naiveMatch(numbers, p11), false);
	ASSERT_EQUAL(naiveMatch(numbers, p12), true);
	ASSERT_EQUAL(naiveMatch(numbers, p13), false);
	ASSERT_EQUAL(naiveMatch(numbers, p14), true);

	std::string symbols = "\? [] /()=!#&|$#!#  '-<>>|";
	std::string p15 = "\? [] /()=!#&|$#!#  '-<>>|";
	std::string p16 = "\? [] /()=!#&|$#!#  '-<>>| ";
	std::string p17 = "|";
	std::string p18 = "||";
	std::string p19 = "\? ";
	std::string p20 = "\\";
	std::string p21 = ")=!#&";
	ASSERT_EQUAL(naiveMatch(symbols, p15), true);
	ASSERT_EQUAL(naiveMatch(symbols, p16), false);
	ASSERT_EQUAL(naiveMatch(symbols, p17), true);
	ASSERT_EQUAL(naiveMatch(symbols, p18), false);
	ASSERT_EQUAL(naiveMatch(symbols, p19), true);
	ASSERT_EQUAL(naiveMatch(symbols, p20), false);
	ASSERT_EQUAL(naiveMatch(symbols, p21), true);

	std::string nonAscii = "prcação água, não sôr3";
	std::string p22 = "não";
	std::string p23 = "noãasçºdlfkçfkºasdkfokrot";
	std::string p24 = "sôr";
	std::string p25 = "prcação água, não sô";
	std::string p26 = "prcação água, não sôr3";
	std::string p27 = "prcação água, não sôt";
	std::string p28 = " água, ";
	ASSERT_EQUAL(naiveMatch(nonAscii, p22), true);
	ASSERT_EQUAL(naiveMatch(nonAscii, p23), false);
	ASSERT_EQUAL(naiveMatch(nonAscii, p24), true);
	ASSERT_EQUAL(naiveMatch(nonAscii, p25), true);
	ASSERT_EQUAL(naiveMatch(nonAscii, p26), true);
	ASSERT_EQUAL(naiveMatch(nonAscii, p27), false);
	ASSERT_EQUAL(naiveMatch(nonAscii, p28), true);
}

void automata() {
	std::string alpha = "The quick brown fox jumps over the lazy dog";
	std::string p1 = "The";
	std::string p2 = " The apsdghidamkbrowpago";
	std::string p3 = " fox j";
	std::string p4 = "ovr t";
	std::string p5 = "y dog";
	std::string p6 = "z dog";
	std::string p7 = "quick brown ";
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p1), alpha, p1), true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p2), alpha, p2), false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p3), alpha, p3), true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p4), alpha, p4), false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p5), alpha, p5), true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p6), alpha, p6), false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p7), alpha, p7), true);

	std::string numbers = "01234567890 1337 3141592653589793";
	std::string p8 = "01234567890";
	std::string p9 = "012345678901";
	std::string p10 = " 1337";
	std::string p11 = "3144";
	std::string p12 = "3";
	std::string p13 = "999";
	std::string p14 = "793";
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p8), numbers, p8),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p9), numbers, p9),
			false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p10), numbers, p10),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p11), numbers, p11),
			false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p12), numbers, p12),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p13), numbers, p13),
			false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p14), numbers, p14),
			true);

	std::string symbols = "\? [] /()=!#&|$#!#  '-<>>|";
	std::string p15 = "\? [] /()=!#&|$#!#  '-<>>|";
	std::string p16 = "\? [] /()=!#&|$#!#  '-<>>| ";
	std::string p17 = "|";
	std::string p18 = "||";
	std::string p19 = "\? ";
	std::string p20 = "\\";
	std::string p21 = ")=!#&";
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p15), symbols, p15),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p16), symbols, p16),
			false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p17), symbols, p17),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p18), symbols, p18),
			false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p19), symbols, p19),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p20), symbols, p20),
			false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p21), symbols, p21),
			true);

	std::string nonAscii = "prcação água, não sôr3";
	std::string p22 = "não";
	std::string p23 = "noãasçºdlfkçfkºasdkfokrot";
	std::string p24 = "sôr";
	std::string p25 = "prcação água, não sô";
	std::string p26 = "prcação água, não sôr3";
	std::string p27 = "prcação água, não sôt";
	std::string p28 = " água, ";
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p22), nonAscii, p22),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p23), nonAscii, p23),
			false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p24), nonAscii, p24),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p25), nonAscii, p25),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p26), nonAscii, p26),
			true);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p27), nonAscii, p27),
			false);
	ASSERT_EQUAL(finiteAutomatonMatch(computeTransition(p28), nonAscii, p28),
			true);
}

void runSuite() {
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(naive));
	s.push_back(CUTE(automata));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main() {
	runSuite();
	return 0;
}

