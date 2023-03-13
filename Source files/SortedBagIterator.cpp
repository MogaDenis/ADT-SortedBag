#include "../Header files/SortedBagIterator.h"
#include "../Header files/SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->currentElementIndex = 0;
	this->currentElementFrequency = 1;
}

TComp SortedBagIterator::getCurrent() {
	if (!this->valid())
		throw std::exception();

	return this->bag.elements[this->currentElementIndex];
}

bool SortedBagIterator::valid() {
	if (this->currentElementIndex < this->bag.length && this->currentElementFrequency <= this->bag.frequencies[this->currentElementIndex])
		return true;

	return false;
}

void SortedBagIterator::next() {
	if (!this->valid())
		throw std::exception();

	this->currentElementFrequency++;

	if (this->currentElementFrequency > this->bag.frequencies[this->currentElementIndex])
	{
		this->currentElementIndex++;
		this->currentElementFrequency = 1;
	}
}

void SortedBagIterator::first() {
	this->currentElementIndex = 0;
	this->currentElementFrequency = 1;
}

