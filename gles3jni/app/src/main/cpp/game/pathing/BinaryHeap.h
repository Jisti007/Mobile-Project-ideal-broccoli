#ifndef GLES3JNI_BINARYHEAP_H
#define GLES3JNI_BINARYHEAP_H

#include <vector>
#include "Comparable.h"
#include <cstdint>

class BinaryHeap {
public:
	BinaryHeap();
	~BinaryHeap();

	void add(Comparable* item);
	void reposition(Comparable* item);
	Comparable* removeAt(int position);
	//bool remove(Comparable* item);
	//void sort();
	//bool contains(Comparable* item);

	inline void reserve(size_t size) { items.reserve(size); }
	inline Comparable* remove() { return removeAt(0); }
	inline Comparable* peek() { return items[0]; }
	inline void clear() { items.clear(); }
	inline size_t count() { return items.size(); }

private:
	std::vector<Comparable*> items;
	//bool sorted = false;

	void heapifyUp(int position);
	void heapifyDown(int position);
	void swap(int positionA, int positionB);
	int getSmallerChild(int position);

	inline int getParent(int position) { return (position - 1) / 2; }
	inline int getLeftChild(int position) { return position * 2 + 1; }
	inline int getRightChild(int position) { return position * 2 + 2; }
};

#endif //GLES3JNI_BINARYHEAP_H
