#include "legrep.h"

void readFile(const char *filePath, string pattern) {
	fstream file;
	string line;
	stringstream ss;
	
	file.open(filePath);
	if (file.is_open()) {
		while (file.good()) {
			// read a line
			getline(file, line);
			ss << line;

			// grep the line
			if (naiveStringMatch(line, pattern))
				cout << line;
		}
	}
	file.close();
}

void printNoArgs() {
	cout << "Usage: lerep [OPTION]... PATTERN [FILE]...\n";
	cout << "Try \'legrep --help\' for more information.\n";
}

int main(int argc, char **argv){
	if (argc == 1)
		printNoArgs();
	if (argc > 1){
		cout << "Searching for " << argv[1] << "...\n";
		readFile(argv[1],"ola");
	}

	return 0;
}