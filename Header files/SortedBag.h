#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	TComp *elements; 				  // The array of elements.
	TComp *frequencies;				  // The array of frequencies. 
	int length; 					  // The number of unique elements in the bag. 
	int capacity;					  // The maximum number of unique elements in the bag. 
	int bagSize;					  // The total number of elements in the bag (the sum of the frequencies). 
	int elementsNotDeleted;			  // The number of unique elements in the bag having a frequency greater than 0.
	Relation relationBetweenElements; // The relation based on which the elements are sorted.

	void expand();					  // Function for doubling the capacity of the bag.
	void shrink();					  // Function for halving the capacity of the bag. 

public:
	//constructor
	SortedBag(Relation r);

	// Copy constructor.
	SortedBag(const SortedBag& sortedBag);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appears is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();
};