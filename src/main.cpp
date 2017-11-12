#include "asClassification.h"
#include "asTopology.h"
#include "asClassification.h"
#include "AS.h"
#include "asNode.h"
#include "asTopology_V2.h"
#include <map>
#include <chrono>
#include <ctime>

int main(int argc, char *argv[]) {
	/*
    if (argc != 3) {
        cout << "Usage : autosys inFile outFile" << endl;
        return EXIT_FAILURE;
    }
    */

	/*
	 * BEGIN PART ONE
	 * AS Classification
	 */

	// Transit/Access ASes, Content ASes, Enterprise ASes, Total #ASes in file
	// Expected: t = 21722, c = 2341, e = 27447
	// int tCounter = -1, cCounter = -1, eCounter = -1, totalCounter = -1;
	
    /*
	parseFile(&tCounter, &cCounter, &eCounter, &totalCounter);
	writeFile(tCounter, cCounter, eCounter, totalCounter);
     */
    
	/*
	 * END PART ONE
	 * BEGIN PART TWO
	 * Topology Interference Through AS Links
	 */
	std::cout << "Begin Part Two:\n";
	multimap<int, int>* p2p = new multimap<int, int>();
	multimap<int, int>* p2c = new multimap<int, int>();
	std::cout << "Getting all node entries from file.\n";
	auto start = std::chrono::system_clock::now();
	parsePartTwo(p2p, p2c);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "File parsing completed in " << elapsed_seconds.count() << " seconds.\n";
	
	std::cout << "\n Start processing data and get degrees\n";
	start = std::chrono::system_clock::now();	
	processPartTwo(p2p, p2c);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "\nDone with processing in " << elapsed_seconds.count() << " seconds\n";
	
	/*
	 * END PART TWO
	 * BEGIN PART THREE
	 * Interference of T1 ASes
	 */



	/*
	* END PART THREE
	*/

	return 0;
}
