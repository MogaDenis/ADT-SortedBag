#include "../Header files/SortedBag.h"
#include "../Header files/SortedBagIterator.h"
#include <iostream>
#include "../Header files/ShortTest.h"
#include "../Header files/ExtendedTest.h"

#include <chrono>
using namespace std::chrono;


using namespace std;

int main() {

	// // Use auto keyword to avoid typing long
	// // type definitions to get the timepoint
	// // at this instant use function now()
	// auto start = high_resolution_clock::now();

	testAll();
	testAllExtended();

	// auto stop = high_resolution_clock::now();
	// auto duration = duration_cast<microseconds>(stop - start);

	// // To get the value of duration use the count()
	// // member function on the duration object
	// cout << duration.count() << endl;
	
	cout << "Test over" << endl;
	//system("pause");
}
