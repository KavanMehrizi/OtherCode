#ifndef MYSORTABLEARRAY_H
#define MYSORTABLEARRAY_H

// declare template class
template <typename T>
class DynamicArray
{
public:
	// default constructor that sets the dynamic array and sets size to 0
	DynamicArray()
	{
		dynamicArray = nullptr;
		size = 0;
	}
	// dynamically creates new array and copies over values
	DynamicArray(const DynamicArray<T>& input)
	{
		size = input.size;
		dynamicArray = new T[size];
		copy(input.dynamicArray, input.dynamicArray + size,
			dynamicArray);
	}
	// this function returns size of array
	int getSize()
	{
		return size;
	}
	// this function allows user to add name by dynamically creating larger array
	void addEntry(T name)
	{
		// creates larger array and adds all values so user can add new name
		T* addArray = new T[size + 1];
		for (int i = 0; i < size; i++) {
			addArray[i] = dynamicArray[i];
		}
		// adds new name to end of array
		addArray[size] = name;
		// deletes old array
		delete[] dynamicArray;
		// since we added new entry, size is + 1
		size = size + 1;
		dynamicArray = new T[size];
		for (int i = 0; i < size; ++i) {
			dynamicArray[i] = addArray[i];
		}
	}
	// define assignment operator
	DynamicArray<T>& operator=(const DynamicArray<T>& src)
	{
		size = src.size;
		dynamicArray = new T[size];
		for (int i = 0; i < size; i++)
		{
			dynamicArray[i] = src.dynamicArray[i];
		}
		// returns input
		return *this;
	}
	// This function gets the name at the specified index
	T getEntry(int index)
	{
		// if found returns entry, else returns nothing
		if (index < size)
		{
			return dynamicArray[index];
		}
		else
		{
			return NULL;
		}
	}
	// define destructor to de-initialize array
	~DynamicArray()
	{
		delete[] dynamicArray;
	}
	// this function sorts the index-value pairs in the dynamic array by using Quick Sort
	void sort(int i, int k)
	{
		int j = 0;

		/** Base case: If there are 1 or zero elements to sort,
		 partition is already sorted */
		if (i >= k)
		{
			return;
		}

		/** Partition the data within the array. Value j returned
		 from partitioning is location of last element in low partition. */
		j = Partition(i, k);

		/** Recursively sort low partition (i to j) and
		 high partition (j + 1 to k) */
		sort(i, j);
		sort(j + 1, k);

		return;
	}

private:
	// declare variables only for inside class
	T* dynamicArray;
	int size;
	
	// this function is only used by sort() to partition dynamic array
	int Partition(int i, int k) {
		int l = 0;
		int h = 0;
		int midpoint = 0;
		int pivot = 0;
		int temp = 0;
		bool done = false;

		/** Pick middle element as pivot */
		midpoint = i + (k - i) / 2;
		pivot = dynamicArray[midpoint];

		l = i;
		h = k;

		while (!done) {

			/** Increment l while numbers[l] < pivot */
			while (dynamicArray[l] < pivot) {
				++l;
			}

			/** Decrement h while pivot < numbers[h] */
			while (pivot < dynamicArray[h]) {
				--h;
			}

			/** If there are zero or one elements remaining,
			 all numbers are partitioned. Return h */
			if (l >= h) {
				done = true;
			}
			else {
				/** Swap numbers[l] and numbers[h],
				 update l and h */
				temp = dynamicArray[l];
				dynamicArray[l] = dynamicArray[h];
				dynamicArray[h] = temp;

				++l;
				--h;
			}
		}

		return h;
	}
}; 
#endif