#include "asClassification.h"

int main(int argc, char *argv[]) {
	
	/*
	 * BEGIN PART ONE
	 * AS Classification
	 */

	// Transit/Access ASes, Content ASes, Enterprise ASes, Total #ASes in file
	// Expected: t = 21722, c = 2341, e = 27447
	int tCounter = -1, cCounter = -1, eCounter = -1, totalCounter = -1;

	parseFile(&tCounter, &cCounter, &eCounter, &totalCounter);
	writeFile(tCounter, cCounter, eCounter, totalCounter);

	/*
	 * END PART ONE
	 * BEGIN PART TWO
	 * Topology Interference Through AS Links
	 */




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