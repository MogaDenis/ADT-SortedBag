#pragma once
#include "../Header files/SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	int currentElementIndex;
	int currentElementFrequency;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

