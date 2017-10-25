#ifndef GLES3JNI_WEIGHTEDLIST_H
#define GLES3JNI_WEIGHTEDLIST_H

#include <list>
#include <cstdlib>

template <typename T>
class WeightedList {
public:
	T getRandom();
	bool add(T item, double weight);
	void remove(T item);
	void clear();
	size_t count();

private:
	std::list<std::pair<double, T>> items;
	double totalWeight = 0.0;
};

template <typename T>
T WeightedList<T>::getRandom() {
	if (totalWeight > 0) {
		double rn = (double)rand() / RAND_MAX * totalWeight;
		for (auto& weightItem : items) {
			if (rn <= weightItem.first) {
				return weightItem.second;
			}
			rn -= weightItem.first;
		}
	}

	return nullptr;
}

template <typename T>
bool WeightedList<T>::add(T item, double weight) {
	if (weight <= 0) {
		return false;
	}

	items.push_back({weight, item});
	totalWeight += weight;
	return true;
}

template <typename T>
void WeightedList<T>::remove(T item) {
	for (auto& weightItem : items) {
		if (item == weightItem.second) {
			totalWeight -= weightItem.first;
			items.remove(weightItem);
			return;
		}
	}
}

template <typename T>
void WeightedList<T>::clear() {
	items.clear();
	totalWeight = 0;
}

template <typename T>
size_t WeightedList<T>::count() {
	return items.size();
}

#endif //GLES3JNI_WEIGHTEDLIST_H
