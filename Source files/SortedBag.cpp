#include "../Header files/SortedBag.h"
#include "../Header files/SortedBagIterator.h"
#include <iostream>


// Constructor.
SortedBag::SortedBag(Relation r) {
	this->capacity = 1;
	this->bagSize = 0;
	this->length = 0;
	this->elementsNotDeleted = 0;

	this->elements = new TComp[this->capacity];
	this->frequencies = new int[this->capacity];
	
	this->relationBetweenElements = r;
}


// Copy constructor. 
SortedBag::SortedBag(const SortedBag& sortedBag)
{
	capacity = sortedBag.capacity;
	bagSize = sortedBag.bagSize;
	length = sortedBag.length;
	elementsNotDeleted = sortedBag.elementsNotDeleted;

	elements = sortedBag.elements;
	frequencies = sortedBag.frequencies;

	relationBetweenElements = sortedBag.relationBetweenElements;
}


// Best case: 	 Theta(1) - the bag is empty
// Average case: Theta(log n) - the element already exists in the bag, only the frequency is increased.
//				 Theta(n) - the element is not in the bag, so we need to make room for it by shifting other values.
// Worst case:   Theta(n) - the bag is full so we need memory reallocation, then check if the element is in the bag and add it. 

// Total time complexity: O(n)
void SortedBag::add(TComp e) {
	if (this->length == 0)
	{
		// Best case. O(1)
		// If the bag is empty, add the first element. 
		this->elements[0] = e;
		this->frequencies[0] = 1;
		this->length = 1;
		this->bagSize = 1;
		this->elementsNotDeleted = 1;
		return;
	}

	// Worst case. Allocate new memory, copy the data and deallocate the previous data. O(n)
	if (this->length == this->capacity)
		this->expand();

	// Search the element using binary search. O(log n)
	int left = 0, right = this->length - 1, middle;
	bool found = false;

	while (left <= right)
	{
		middle = left + (right - left) / 2;
		if (this->elements[middle] == e)
		{
			found = true;
			break;
		}

		else if (this->relationBetweenElements(this->elements[middle], e))
			left = middle + 1;
		
		else
			right = middle - 1;
	}

	// If the element was found, increase its frequency. O(1)
	if (found)
	{
		if (this->frequencies[middle] == 0)
			// If the element was previously deleted completely, we consider now that it was added back.
			this->elementsNotDeleted++;

		this->frequencies[middle]++;
	}

	// If the element is unique, insert it at the correct position.
	else
	{
		// The 'left' index is the position where we have to insert the new element.
		int index = left;

		// Move all the values from the right one position further. O(n)
		for (int i = this->length; i > index; i--)
		{
			this->elements[i] = this->elements[i - 1];
			this->frequencies[i] = this->frequencies[i - 1];
		}

		// Insert the new element.
		this->elements[index] = e;
		this->frequencies[index] = 1;
		this->length++; // Increase the length (the number of unique elements).
		this->elementsNotDeleted++;  // Increase the number of elements that are not deleted. 
	}

	// Increase the total number of elements.
	this->bagSize++;
}


void SortedBag::expand()
{
	// Resize.
	TComp *newElementsArray = new TComp[2 * this->capacity];
	TComp *newFrequenciesArray = new TComp[2 * this->capacity];
	this->capacity *= 2;

	// Copy the data. 
	for (int i = 0; i < this->length; i++)
	{
		newElementsArray[i] = this->elements[i];
		newFrequenciesArray[i] = this->frequencies[i];
	}

	// Deallocate the previous arrays.
	delete[] this->elements;
	delete[] this->frequencies;

	// Change the refferences to the new arrays.
	this->elements = newElementsArray;
	this->frequencies = newFrequenciesArray;
}


void SortedBag::shrink()
{
	// Resize.
	this->capacity /= 2;
	TComp *newElementsArray = new TComp[this->capacity];
	TComp *newFrequenciesArray = new TComp[this->capacity];

	// Copy the data that is not considered deleted.
	int index = 0;
	for (int i = 0; i < this->length; i++)
	{
		if (this->frequencies[i] > 0)
		{
			newElementsArray[index] = this->elements[i];
			newFrequenciesArray[index] = this->frequencies[i];
			index++;
		}
	}

	// Deallocate the previous arrays.
	delete[] this->elements;
	delete[] this->frequencies;

	// Change the references to the new arrays.
	this->elements = newElementsArray;
	this->frequencies = newFrequenciesArray;
	this->length = index;
}


// Best case: 	 Theta(1) - the element to delete is in the middle of the bag.
// Average case: Theta(log n) - the element is either in the bag or not (binary search). 
// Worst case:   Theta(n) - the number of elements is a quarter of the capacity, so we need to shrink the bag.

// Total time complexity: O(n)
bool SortedBag::remove(TComp e) {
	// Search the element using binary search.
	int left = 0, right = this->length - 1;

	while (left <= right)
	{
		int middle = left + (right - left) / 2;

		if (this->elements[middle] == e)
		{	
			// If we found the element and the frequency is positive(it exists) decrease the frequency.
			if (this->frequencies[middle] > 0)
			{
				this->frequencies[middle]--;
				this->bagSize--;

				// If an element has a frequency of 0, it is considered deleted.
				if (this->frequencies[middle] == 0 && this->elementsNotDeleted > 1)
					this->elementsNotDeleted--;

				// If we have a lot of unused memory, allocate a smaller area of memory and copy the data. O(n)
				// std::cout << " " << this->capacity << " " << this->length << " " << this->elementsNotDeleted << std::endl;
				if (this->elementsNotDeleted == this->capacity / 4 && this->elementsNotDeleted > 1)
					this->shrink();

				return true;
			}

			// If the frequency is 0, it means that the element was already deleted.
			return false;
		}
		else if (this->relationBetweenElements(this->elements[middle], e))
			left = middle + 1;
		else
			right = middle - 1;
	}

	return false;
}


// Theta(log n) - worst/average case, element is not in the bag.
// Theta(1) - best case, element is right in the middle.

// Total time complexity: O(log n)
bool SortedBag::search(TComp elem) const {
	// Search the element using binary search.
	int left = 0, right = this->length - 1;

	while (left <= right)
	{
		int middle = left + (right - left) / 2;

		if (this->elements[middle] == elem)
		{	
			// If we found the element and the frequency is positive(it exists) decrease the frequency.
			if (this->frequencies[middle] > 0)
				return true;

			// If the frequency is 0, it means that the element was already deleted.
			return false;
		}
		else if (this->relationBetweenElements(this->elements[middle], elem))
			left = middle + 1;
		else
			right = middle - 1;
	}

	return false;
}


// Theta(log n) - worst/average case, element is not in the bag.
// Theta(1) - best case, element is right in the middle.

// Total time complexity: O(log n)
int SortedBag::nrOccurrences(TComp elem) const {
	// Search the element using binary search.
	int left = 0, right = this->length - 1;

	while (left <= right)
	{
		int middle = left + (right - left) / 2;

		if (this->elements[middle] == elem)
			return this->frequencies[middle];

		else if (this->relationBetweenElements(this->elements[middle], elem))
			left = middle + 1;

		else
			right = middle - 1;
	}

	return 0;
}


// Theta(1) 
int SortedBag::size() const {
	return this->bagSize;
}


// Theta(1) 
bool SortedBag::isEmpty() const {
	return this->bagSize == 0;
}


// Iterator.
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


// Destructor.
SortedBag::~SortedBag() {
	delete[] this->elements;
	delete[] this->frequencies;
}
