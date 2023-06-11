# ADT-SortedBag
Implementation in C++ of a Sorted Bag ADT.

The Sorted Bag is represented on a dynammic array and a frequency array. Values and frequencies are associated by the same indices.

The Sorted Bag includes in its interface the following:
  - Add a new element
  - Remove an element 
  - Search if an element is in the bag
  - Get the size and the number of occurrences of an element
  - Iterator

The dynammic array is resized when it gets full and it is shrinked when only a quarter of the memory allocated is used.
