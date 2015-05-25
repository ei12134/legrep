#include "legrep.h"

void setColor(const int fgColor, bool fgIntensity) {
#if defined(_WIN32) || defined(_WIN64)
	SetConsoleTextAttribute(hConsoleOutput, fgColor | (fgIntensity << 3));
#else
	cout << "\033[" << fgIntensity << ";" << 30 + fgColor << "m";
#endif
}

void resetColor() {
#if defined(_WIN32) || defined(_WIN64)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
#else
	cout << "\033[0m";
#endif
}

void result(string& filePath, string& pattern) {
	fstream file;
	string line;
	int lineNumber = 1;
	
	file.open(filePath.c_str());

	for (auto itr = lines.begin(); itr != lines.end() && !file.eof( ); itr++) {
		int targetLine = (*itr).first;

		for (int i = lineNumber; i <= targetLine && file.good(); i++, lineNumber++){
			line.clear();
			getline(file, line);	
		}

		if ((*itr).second.size() == 0)
			cout << line;
		else if ((*itr).second.size() == 1 && (*itr).second[0] == -1){
			setColor(BLUE,true);
			cout << "--";
			resetColor();
		}

		else {
			vector<int> indexes = (*itr).second;
			int startPos = 0;

			for (int i = 0; i < (int)indexes.size(); i++){
				cout << line.substr(startPos,indexes[i]-startPos);
				setColor(RED,true);
				cout << line.substr(indexes[i], pattern.size());
				resetColor();
				if (i < (int)indexes.size() - 1)
					startPos = indexes[i] + pattern.size();
				else 
					cout << line.substr(indexes[i] + pattern.size());	
			}	
		}
		if (itr != lines.end())
			cout << "\n";
	}
	file.close();
}

void readFile(string& filePath, string& pattern) {
	fstream file;
	string line, text;
	int lineNumber = 1;
	vector<int> empty;
	vector<int> pi;
	hashTable table;

	if (matchMode == FINITE_AUTOMATA) {
		table = computeStateTransitionTable(pattern);
	}
	else if (matchMode == KNUTH_MORRIS_PRATT) {
		pi = computePrefixFunction(pattern);
	}

	file.open(filePath.c_str());
	if (file.is_open()) {
		while (file.good()) {
			// read a line
			line.clear();
			text.clear();
			getline(file, line);

			vector<int> indexes;
			text = line;

			// grep the line
			if (ignoreCase)
				transform(text.begin(), text.end(), text.begin(), ::tolower);

			// search call
			switch (matchMode) {
			case FINITE_AUTOMATA:
				indexes = finiteAutomaton(text, pattern, table);
				break;

			case NAIVE:
				indexes = naive(text, pattern);
				break;

			case KNUTH_MORRIS_PRATT:
				indexes = knuthMorrisPratt(text, pattern, pi);
				break;
			default:
				break;
			}

			// print the line
			if (indexes.size() > 0 && !invertMatch) {	
				auto it = lines.find(pair<int, vector<int> >(lineNumber, empty));
				if (it != lines.end())
					lines.erase(it);
				lines.insert(pair<int,vector<int> >(lineNumber,indexes));

				// add lines before context
				int lbc = lineNumber - 1;
				for (int i = 0; i < beforeContext && lbc > 0; i++, lbc--)
					lines.insert(pair<int,vector<int> >(lbc,empty));
				
				if (matches != 0 && (beforeContext != 0) && lbc > 1)
					lines.insert(pair<int,vector<int> >(lbc,vector<int>(1,-1)));

				// add lines after context
				int lac = lineNumber + 1;
				for (int i = 0; i < afterContext; i++, lac++)
					lines.insert(pair<int,vector<int> >(lac, empty));
			}
			else if (invertMatch && (indexes.size() == 0))
				lines.insert(pair<int,vector<int> >(lineNumber,empty));

			// independently increment matches
			if (indexes.size() > 0)
				matches++;
			lineNumber++;
		}
	}

	file.close();
	result(filePath, pattern);
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

		// Search for options
		if (cmdOptionExists(argv, argv + argc, "-h") || cmdOptionExists(argv, argv + argc, "--help")) {
			usage(true);
			return 0;
		}

		if (cmdOptionExists(argv, argv + argc, "-n") || cmdOptionExists(argv, argv + argc, "--naive-match")) {
			matchMode = NAIVE;
		}

		else if (cmdOptionExists(argv, argv + argc, "-m") || cmdOptionExists(argv, argv + argc, "--finite-automata")) {
			matchMode = FINITE_AUTOMATA;
		}

		else if (cmdOptionExists(argv, argv + argc, "-k") || cmdOptionExists(argv, argv + argc, "--knuth-morris-pratt")) {
			matchMode = KNUTH_MORRIS_PRATT;
		}

		if (cmdOptionExists(argv, argv + argc, "-i") || cmdOptionExists(argv, argv + argc, "--ignore-case")) {
			ignoreCase = true;
			transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
		}

		if (cmdOptionExists(argv, argv + argc, "-v") || cmdOptionExists(argv, argv + argc, "--invert-match")) {
			invertMatch = true;
		}

		char * beforePtr = getCmdOption(argv, argv + argc, "-B");
		if (beforePtr != nullptr)
		{
			// read before match lines count
			beforeContext = atoi(beforePtr);
		}

		char * afterPtr = getCmdOption(argv, argv + argc, "-A");
		if (afterPtr != nullptr)
		{
			// read after match lines
			afterContext = atoi(afterPtr);
		}
		char * contextPtr = getCmdOption(argv, argv + argc, "-C");
		if (contextPtr != nullptr)
		{
			// read before and after match lines
			beforeContext = atoi(contextPtr);
			afterContext = beforeContext;
		}

		readFile(file, pattern);
	} else if (cmdOptionExists(argv, argv + argc, "-h") || cmdOptionExists(argv, argv + argc, "--help")) {
		usage(true);
		return 0;
	} else
		usage(false);

	return 0;
}
