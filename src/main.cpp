#include "asClassification.h"
#include "asTopology.h"
#include "asInference.h"
#include <map>
#include <chrono>
#include <ctime>

int main(int argc, char *argv[]) {
	
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	/*
	 * BEGIN PART ONE
	 * AS Classification
	 */

	std::cout << "Begin Part One:\n";
	// Transit/Access ASes, Content ASes, Enterprise ASes, Total #ASes in file
	int tCounter = -1, cCounter = -1, eCounter = -1, totalCounter = -1;

	// Expected: t = 21722, c = 2341, e = 27447, total = sum
	start = std::chrono::system_clock::now();
	parsePartOne(&tCounter, &cCounter, &eCounter, &totalCounter);
	writePartOne(tCounter, cCounter, eCounter, totalCounter);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "Part One Completed in " << elapsed_seconds.count() << " seconds\n\n";
    
	/*
	 * END PART ONE
	 * BEGIN PART TWO
	 * Topology Interference Through AS Links
	 */

	std::cout << "Begin Part Two and Three:\n";
	std::multimap<int, int>* p2p = new std::multimap<int, int>();
	std::multimap<int, int>* p2c = new std::multimap<int, int>();
    std::multimap<std::string, double>* ipList = new std::multimap<std::string, double>();
    std::multimap<int, int>* sorted = new std::multimap<int, int>();

	std::cout << "\nGetting all node entries from file.\n";
	start = std::chrono::system_clock::now();
    parseIPPrefix(ipList);
	parsePartTwo(p2p, p2c);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "Done with file parsing in " << elapsed_seconds.count() << " seconds.\n";
	
	std::cout << "\nStart processing data and get degrees\n";
	start = std::chrono::system_clock::now();
	processPartTwo(p2p, p2c, ipList);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "Done with processing in " << elapsed_seconds.count() << " seconds\n";
	
	std::cout << "Part Two and Three Completed\n";
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
