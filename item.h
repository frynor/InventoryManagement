#pragma once
#include <string>

class Item{
	public:
		std::string name;
		int price;
		int quantity;
		int id;
		
		void inputItem();
		void displayItem() const;
};
