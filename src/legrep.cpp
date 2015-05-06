#include "legrep.h"

void readFile(const char* filePath, string pattern)
{
	fstream file;
	string line, text;
	bool print;
	
	file.open(filePath);
	if (file.is_open()) {
		while (file.good()) {
			// read a line
			line.clear();
			text.clear();
			getline(file, line);

			// line = "hoje amanha";
			print = false;
			text = line;

			// grep the line
			if (ignore_case)
				transform(text.begin(), text.end(), text.begin(), ::tolower);
			
			// search call
			print = naiveStringMatch(text, pattern);	

			// print the line
			if (invert_match != print)
			 	cout << line << "\n";
		}
	}
	file.close();
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
		cout << "Try \'legrep --help\' for more information.\n\n";
	}
	else {
		cout << "Usage: grep [OPTION]... PATTERN [FILE]...\n";
		cout << "Search for PATTERN in each FILE or standard input.\n";
		cout << "PATTERN is, by default, a basic regular expression (BRE).\n";
		cout << "Example: grep -i 'hello world' menu.h main.c\n\n";

		cout << "Regexp selection and interpretation:\n";
		cout << "  -i, --ignore-case         ignore case distinctions\n\n";

		cout << "Miscellaneous:\n";
		cout << "  -v, --invert-match        select non-matching lines\n";
		cout << "    --help                display this help text and exit\n\n";

		cout << "Context control:\n";
		cout << "  -B, --before-context=NUM  print NUM lines of leading context\n";
		cout << "  -A, --after-context=NUM   print NUM lines of trailing context\n";
		cout << "  -C, --context=NUM         print NUM lines of output context\n\n";
	}
}

int main(int argc, char** argv)
{
	if (argc >= 3) {
		ignore_case = false;
		invert_match = false;
		string pattern = argv[argc-2];
		char* filePath = argv[argc-1];
		cout << "Searching for " << pattern << " in " << filePath << "...\n";

		// Search for options
		if(cmdOptionExists(argv, argv+argc, "-i") || cmdOptionExists(argv, argv+argc, "--ignore-case"))
		{
			ignore_case = true;
			transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
		}

		if(cmdOptionExists(argv, argv+argc, "-v") || cmdOptionExists(argv, argv+argc, "--invert-match"))
		{
			invert_match = true;
		}

		// char * beforePtr = getCmdOption(argv, argv + argc, "-B");
		// if (beforePtr != nullptr)
		// {
		// 	// read before line count
		// 	before_context = ...;
		// }
		
		readFile(filePath,pattern);
	}
	else {
		usage(false);
	}

	return 0;
}