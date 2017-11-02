#include "BinaryHeap.h"

BinaryHeap::BinaryHeap() {

}

BinaryHeap::~BinaryHeap() {

}

void BinaryHeap::add(Comparable* item) {
	items.push_back(item);
	heapifyUp((int)items.size());
}

void BinaryHeap::reposition(Comparable* item) {
	// TODO: Implement a proper search function.
	for (int i = 0; i < items.size(); i++) {
		if (items[i] == item) {
			heapifyUp(i);
			heapifyDown(i);
			break;
		}
	}
}

Comparable* BinaryHeap::removeAt(int position) {
	if (position >= items.size()) {
		return nullptr;
	}

	Comparable* item = items[position];
	items[position] = items.back();
	items.pop_back();

	heapifyDown(position);

	return item;
}

void BinaryHeap::heapifyUp(int position) {
	int parent = getParent(position);
	while (position > 0 && items[position]->compareTo(items[parent]) >= 0) {
		swap(position, parent);
		position = parent;
		parent = getParent(position);
	}
}

void BinaryHeap::heapifyDown(int position) {
	while (true) {
		int child = getSmallerChild(position);
		if (child == position) {
			break;
		}

		if (items[position]->compareTo(items[child]) > 0) {
			swap(position, child);
			position = child;
		} else {
			break;
		}
	}
}

void BinaryHeap::swap(int positionA, int positionB) {
	Comparable* dataB = items[positionB];
	items[positionB] = items[positionA];
	items[positionA] = dataB;
}

int BinaryHeap::getSmallerChild(int position) {
	int leftChild = getLeftChild(position);
	if (leftChild >= items.size()) {
		return position;
	}
	int rightChild = getRightChild(position);
	if (rightChild >= items.size() || items[leftChild]->compareTo(items[rightChild]) < 0) {
		return leftChild;
	}
	return rightChild;
}
