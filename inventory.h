#pragma once
#include "item.h"
#include <vector>

class Inventory{
	private:
		std::vector<Item> items;
	public:
		void addItem();
		void displayInventory() const;
		void saveToFile() const;
		void loadFromFile();
		void deleteItem();
		void updateItem();
};
