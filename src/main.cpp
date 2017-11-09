#include "asClassification.h"
#include "asTopology.h"
#include "asClassification.h"
#include "AS.h"
#include "asNode.h"
#include "asTopology_V2.h"

int main(int argc, char *argv[]) {
	/*
    if (argc != 3) {
        cout << "Usage : autosys inFile outFile" << endl;
        return EXIT_FAILURE;
    }
    
    vector<AS *> nodes;
    */
	/*
	 * BEGIN PART ONE
	 * AS Classification
	 */

	// Transit/Access ASes, Content ASes, Enterprise ASes, Total #ASes in file
	// Expected: t = 21722, c = 2341, e = 27447
	// int tCounter = -1, cCounter = -1, eCounter = -1, totalCounter = -1;
    /*
	if(!parseTop(argv[1], nodes)) {
        
    }
	*/
    /*
	parseFile(&tCounter, &cCounter, &eCounter, &totalCounter);
	writeFile(tCounter, cCounter, eCounter, totalCounter);
     */
    
	/*
	 * END PART ONE
	 * BEGIN PART TWO
	 * Topology Interference Through AS Links
	 */
	std::vector<Node> nodes;
	nodes = parseFile2();



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
