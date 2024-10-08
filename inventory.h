#ifndef INVENTORY_H
#define INVENTORY_H
#pragma once
#include "item.h"
#include <vector>

class Inventory{
	private:
		std::vector<Item> items;
	public:
		void addItem();
		void displayInventory(bool includeSearch);
		void saveToFile() const;
		void loadFromFile();
		void deleteItem();
		void updateItem();
		void sortInventory();
		void searchItems() const;
		void dataAnalysis();
};

#endif // INVENTORY_H
