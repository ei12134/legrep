#include "legrep.h"

inline void setColor(const int fgColor, bool fgIntensity) {
#if defined(_WIN32) || defined(_WIN64)
	SetConsoleTextAttribute(hConsoleOutput, fgColor | (fgIntensity << 3));
#else
	cout << "\033[" << fgIntensity << ";" << 30 + fgColor << "m";
#endif
}

inline void resetColor() {
#if defined(_WIN32) || defined(_WIN64)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
#else
	cout << "\033[0m";
#endif
}

void readFile(const string& filePath, const string& pattern) {
	string line, text;
	queue<string> linesBefore;
	int separator = -1;
	size_t lac = 0;

	ifstream file(filePath.c_str(), ios::binary);
	if (file.is_open()) {
		while (file.good()) {
			// read a line
			line.clear();
			text.clear();
			getline(file, line);

			vector<int> indexes;
			text = line;

			// ignore case flag
			if (ignoreCase)
				transform(text.begin(), text.end(), text.begin(), ::tolower);

			// search call
			switch (matchMode) {
			case KNUTH_MORRIS_PRATT:
				indexes = knuthMorrisPratt(text, pattern, pi);
				break;

			case FINITE_AUTOMATA:
				indexes = finiteAutomaton(text, pattern, table);
				break;

			case NAIVE:
				indexes = naive(text, pattern);
				break;

			default:
				break;
			}

			if (invertMatch) {
				if (indexes.size() == 0) {
					cout << line << "\n";
				}
			} else {
				if (indexes.size() > 0) {
					if ((beforeContext > 0 || afterContext > 0)
							&& separator >= (int) linesBefore.size()) {
						setColor(CYAN, false);
						cout << "--\n";
						resetColor();
						separator = -1;
					}

					lac = afterContext;

					// prints lines before
					while (!linesBefore.empty()) {
						string lbc = linesBefore.front();
						linesBefore.pop();
						cout << lbc << "\n";
					}

					// print matching line
					int startPos = 0;

					for (int i = 0; i < (int) indexes.size(); i++) {
						cout << line.substr(startPos, indexes[i] - startPos);
						setColor(RED, true);
						cout << line.substr(indexes[i], pattern.size());
						resetColor();
						if (i < (int) indexes.size() - 1)
							startPos = indexes[i] + pattern.size();
						else {
							cout << line.substr(indexes[i] + pattern.size())
									<< "\n";
						}
					}
				} else {
					if (beforeContext > 0) {
						if (!linesBefore.empty()
								&& linesBefore.size() >= beforeContext)
							linesBefore.pop();
						if (lac <= 0)
							linesBefore.push(line);
					}
					if (lac > 0) {
						cout << line << "\n";
						lac--;
					} else if (lac <= 0) {
						separator++;
					}
				}
			}
			// independently increment matches
			if (indexes.size() > 0)
				matches++;
		}
	}
	file.close();
}

void readFileRaw(const string& filePath, const string& pattern) {
	string text;

	ifstream file(filePath.c_str(), ios::binary);
	if (file.is_open()) {
		while (file.good()) {
			// read a line
			text.clear();
			getline(file, text);
			vector<int> indexes;
			indexes = knuthMorrisPratt(text, pattern, pi);

			// print matching line
			int startPos = 0;
			for (int i = 0; i < (int) indexes.size(); i++) {
				cout << text.substr(startPos, indexes[i] - startPos);
				setColor(RED, true);
				cout << text.substr(indexes[i], pattern.size());
				resetColor();
				if (i < (int) indexes.size() - 1)
					startPos = indexes[i] + pattern.size();
				else {
					cout << text.substr(indexes[i] + pattern.size())
					<< "\n";
				}
			}
		}
	}
	file.close();
}

char* getCmdOption(char** begin, char** end, const string& option) {
	char ** itr = find(begin, end, option);
	if (itr != end && ++itr != end) {
		return *itr;
	}
	return nullptr;
}

bool cmdOptionExists(char** begin, char** end, const string& option) {
	return find(begin, end, option) != end;
}

void usage(bool status) {
	if (!status) {
		cout << "Usage: lerep [OPTION]... PATTERN [FILE]...\n";
		cout << "Try \'legrep --help\' for more information.\n";
	} else {
		cout << "Usage: legrep [OPTION]... PATTERN [FILE]...\n";
		cout << "Search for PATTERN in each FILE or standard input.\n";
		cout << "Example: legrep -i 'hello world' file.txt\n\n";

		cout << "PATTERN selection and interpretation:\n";
		cout << "  -n, --naive-match         naive matching algorithm\n";
		cout
				<< "  -m, --finite-automata     finite automata state machine algorithm\n";
		cout
				<< "  -k, --knuth-morris-pratt  Knuth-Morris-Pratt algorithm (default)\n";
		cout << "  -i, --ignore-case         ignore case distinctions\n\n";

		cout << "Miscellaneous:\n";
		cout << "  -v, --invert-match        select non-matching lines\n";
		cout
				<< "  -h, --help                display this help text and exit\n\n";

		cout << "Context control:\n";
		cout
				<< "  -B, --before-context=NUM  print NUM lines of leading context\n";
		cout
				<< "  -A, --after-context=NUM   print NUM lines of trailing context\n";
		cout
				<< "  -C, --context=NUM         print NUM lines of output context\n";
	}
}

int main(int argc, char** argv) {
	if (argc >= 3) {
#if defined(_WIN32) || defined (_WIN64)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO Info;
		GetConsoleScreenBufferInfo(hConsoleOutput, &Info);
		Attributes = Info.wAttributes;
#endif
		ignoreCase = false;
		invertMatch = false;
		string pattern = argv[argc - 2];
		string file = argv[argc - 1];

		// no extra arguments mode
		if (argc == 3){
			matchMode = KNUTH_MORRIS_PRATT;
			pi = computePrefixFunction(pattern);
			// start reading from file
			readFileRaw(file,pattern);
		}
		else {
			// Search for options
			if (cmdOptionExists(argv, argv + argc, "-h")
					|| cmdOptionExists(argv, argv + argc, "--help")) {
				usage(true);
				return 0;
			}

			if (cmdOptionExists(argv, argv + argc, "-i")
					|| cmdOptionExists(argv, argv + argc, "--ignore-case")) {
				ignoreCase = true;
				transform(pattern.begin(), pattern.end(), pattern.begin(),
						::tolower);
			}

			if (cmdOptionExists(argv, argv + argc, "-v")
					|| cmdOptionExists(argv, argv + argc, "--invert-match")) {
				invertMatch = true;
			}

			char * beforePtr = getCmdOption(argv, argv + argc, "-B");
			if (beforePtr != nullptr) {
				// read before match lines count
				beforeContext = atoi(beforePtr);
			}

			char * afterPtr = getCmdOption(argv, argv + argc, "-A");
			if (afterPtr != nullptr) {
				// read after match lines
				afterContext = atoi(afterPtr);
			}

			char * contextPtr = getCmdOption(argv, argv + argc, "-C");
			if (contextPtr != nullptr) {
				// read before and after match lines
				beforeContext = atoi(contextPtr);
				afterContext = beforeContext;
			}

			// Set string matching mode algorithm
			if (cmdOptionExists(argv, argv + argc, "-n")
					|| cmdOptionExists(argv, argv + argc, "--naive-match")) {
				matchMode = NAIVE;
			} else if (cmdOptionExists(argv, argv + argc, "-m")
					|| cmdOptionExists(argv, argv + argc, "--finite-automata")) {
				matchMode = FINITE_AUTOMATA;
				table = computeStateTransitionTable(pattern);
			} else {
				matchMode = KNUTH_MORRIS_PRATT;
				pi = computePrefixFunction(pattern);
			}

			// start reading from file
			readFile(file, pattern);
		}
	} else if (cmdOptionExists(argv, argv + argc, "-h")
			|| cmdOptionExists(argv, argv + argc, "--help")) {
		usage(true);
		return 0;
	} else
		usage(false);

	return 0;
}
