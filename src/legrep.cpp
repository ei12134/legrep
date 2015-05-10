#include "legrep.h"

void result()
{
	switch(matchMode){
		case FINITE_AUTOMATA:
		cout << "[Finite automata string-matching algorithm";
		break;

		case NAIVE:
		cout << "[Naive string-matching algorithm";
		break;

		case KNUTH_MORRIS_PRATT:
		cout << "[Knuth Morris Pratt algorithm";
		break;

		default:
		break;
	}
	if (matches == 0)
		cout << " didn't find any matches.]\n";
	else
		cout << " found " << matches << (matches == 1? " match.]" : " matches.]") << "\n";
}

void readFile(const char* filePath, string pattern)
{
	fstream file;
	string line, text;
	bool print;
	
	if (matchMode == FINITE_AUTOMATA){
		// Create transition table
		table = computeTransition(pattern);
		// table.print();
	}

	file.open(filePath);
	if (file.is_open()) {
		while (file.good()) {
			// read a line
			line.clear();
			text.clear();
			getline(file, line);

			print = false;
			text = line;

			// grep the line
			if (ignoreCase)
				transform(text.begin(), text.end(), text.begin(), ::tolower);
			
			// search call
			switch(matchMode){
				case FINITE_AUTOMATA:
				print = finiteAutomaton(table, text, pattern);
				break;

				case NAIVE:
				print = naive(text, pattern);
				break;

				case KNUTH_MORRIS_PRATT:
				print = knuthMorrisPratt(text, pattern);
				break;

				default:
				break;
			}

			// print the line
			if (invertMatch != print){
				cout << line << "\n";
			}

			// independently increment matches
			if (print)
				matches++;
		}
	}
	file.close();
	result();
}

char* getCmdOption(char** begin, char** end, const string& option)
{
	char ** itr = find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return nullptr;
}

bool cmdOptionExists(char** begin, char** end, const string& option)
{
	return find(begin, end, option) != end;
}

void usage(bool status)
{
	if (!status){
		cout << "Usage: lerep [OPTION]... PATTERN [FILE]...\n";
		cout << "Try \'legrep --help\' for more information.\n";
	}
	else {
		cout << "Usage: legrep [OPTION]... PATTERN [FILE]...\n";
		cout << "Search for PATTERN in each FILE or standard input.\n";
		cout << "PATTERN is, by default, a basic regular expression (BRE).\n";
		cout << "Example: legrep -i 'hello world' menu.h main.c\n\n";

		cout << "Regexp selection and interpretation:\n";
		cout << "  -n, --naive-match         naive matching algorithm\n";
		cout << "  -m, --finite-automata     finite automata state machine algorithm (default)\n";
		cout << "  -k, --knuth-morris-pratt  Knuth Morris Pratt algorithm\n";
		cout << "  -i, --ignore-case         ignore case distinctions\n\n";

		cout << "Miscellaneous:\n";
		cout << "  -v, --invert-match        select non-matching lines\n";
		cout << "  -h, --help                display this help text and exit\n\n";

		cout << "Context control:\n";
		cout << "  -B, --before-context=NUM  print NUM lines of leading context\n";
		cout << "  -A, --after-context=NUM   print NUM lines of trailing context\n";
		cout << "  -C, --context=NUM         print NUM lines of output context\n\n";
	}
}

int main(int argc, char** argv)
{
	if (argc >= 3) {
		ignoreCase = false;
		invertMatch = false;
		string pattern = argv[argc-2];
		char* filePath = argv[argc-1];

		// Search for options
		if(cmdOptionExists(argv, argv+argc, "-h") || cmdOptionExists(argv, argv+argc, "--help")) {
			usage(true);
			return 0;
		}

		if(cmdOptionExists(argv, argv+argc, "-n") || cmdOptionExists(argv, argv+argc, "--naive-match")) {
			matchMode = NAIVE;
		}

		else if(cmdOptionExists(argv, argv+argc, "-m") || cmdOptionExists(argv, argv+argc, "--finite-automata")) {
			matchMode = FINITE_AUTOMATA;
		}

		else if(cmdOptionExists(argv, argv+argc, "-k") || cmdOptionExists(argv, argv+argc, "--knuth-morris-pratt")) {
			matchMode = KNUTH_MORRIS_PRATT;
		}

		if(cmdOptionExists(argv, argv+argc, "-i") || cmdOptionExists(argv, argv+argc, "--ignore-case")) {
			ignoreCase = true;
			transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
		}

		if(cmdOptionExists(argv, argv+argc, "-v") || cmdOptionExists(argv, argv+argc, "--invert-match")) {
			invertMatch = true;
		}

		// char * beforePtr = getCmdOption(argv, argv + argc, "-B");
		// if (beforePtr != nullptr)
		// {
		// 	// read before line count
		// 	before_context = ...;
		// }
		
		readFile(filePath,pattern);
	}
	else if(cmdOptionExists(argv, argv+argc, "-h") || cmdOptionExists(argv, argv+argc, "--help")) {
		usage(true);
		return 0;
	}
	else
		usage(false);

	return 0;
}