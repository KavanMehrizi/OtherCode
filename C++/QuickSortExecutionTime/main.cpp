#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
#include "MySortableArray.h"
using namespace std;


int main()
{
	// declare variables
	DynamicArray<int> nums;
	int number = 0, sortNum, lookupNum = 0, choice = 0;
	

	for (int N = 1000; N < 10000000; N *= 2)
  {
    nums.addEntry(N);
  }

      auto start = chrono::high_resolution_clock::now();
			nums.sort(0, nums.getSize());
      auto stop = chrono::high_resolution_clock::now();

       chrono::duration<double, milli> fp_ms = stop - start;
       auto int_ms = chrono::duration_cast<chrono::milliseconds>(stop - start);

       std::chrono::duration<long, std::micro> int_usec = int_ms;

			cout << "Sorted:\n";
			for (int i = 0; i < nums.getSize(); i++)
				cout << i << "=>" << nums.getEntry(i) << " ";
			cout << endl;
      cout << "Execution Time: " << fp_ms.count() << " ms, "
              << "or " << int_ms.count() << " whole milliseconds "
              << "(which is " << int_usec.count() << " whole microseconds)" << endl;

	return 0;
}