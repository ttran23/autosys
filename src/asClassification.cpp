#include "asClassification.h"

void parsePartOne(int *tC, int *cC, int *eC, int *total) {

	int tCount = 0, cCount = 0, eCount = 0;
	
	// Open file
	std::ifstream inFile;
	inFile.open("dataset_text_files/20150801.as2types.txt");
	// Check that file exists
	if (!inFile) {
		std::cout << "Unable to open file\n";
		exit(1);
	}

	// Get each line
	std::string inLine, asClass;
	while (std::getline(inFile, inLine)) {
		asClass = inLine.substr(inLine.find_last_of("|") + 1);
		//std::cout << asClass << std::endl;
		if (asClass == "Transit/Access") tCount++;
		else if (asClass == "Enterprise") eCount++;
		else if (asClass == "Content") cCount++;
	}
	*tC = tCount;
	*eC = eCount;
	*cC = cCount;
	*total = tCount + eCount + cCount;
	inFile.close();
}

void writePartOne(int tC, int cC, int eC, int total) {

	// Open file
	std::ofstream outFile;
	outFile.open("output_text_files/partOne.txt");
	// Check that file exists
	if (!outFile) {
		std::cout << "Unable to open file\n";
		exit(1);
	}

	double tPercent = (double)tC / (double)total * 100.0;
	double ePercent = (double)eC / (double)total * 100.0;
	double cPercent = (double)cC / (double)total * 100.0;

	outFile << "There were a total of " << total << "entries. Of which, the class distribution are as follows:\n";
	outFile << "Transit/Access = " << tC << "\twith a percentage of " << tPercent << std::endl;
	outFile << "Enterprise = " << eC << "\t\twith a percentage of " << ePercent << std::endl;
	outFile << "Content = " << cC << "\t\t\twith a percentage of " << cPercent << std::endl;
	outFile << "\n\n\n";
	outFile.close();
}