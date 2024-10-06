#include "item.h"
#include <algorithm>
#include <vector>

int partition(std::vector<Item>& items, int low, int high);
void quickSort(std::vector<Item>& items, int low, int high);

int partition(std::vector<Item>& items, int low, int high){
	Item& pivot = items[high];
	int i = low - 1;

	for(int j = 0; j < high; j++) {
		if(items[j].id <= pivot.id){
			i++;
			std::swap(items[i], items[j]);
		}
	}
	std::swap(items[i + 1], items[high]);
	return i + 1;
}

void quickSort(std::vector<Item>& items, int low, int high){
	if(low < high){
		int pi = partition(items, low, high);

		quickSort(items, low, pi - 1);
		quickSort(items, pi + 1, high);
	}
}

void sortInventory(std::vector<Item>& items){
	quickSort(items, 0, items.size() - 1);
}
