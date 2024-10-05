#include <iostream>
#include "item.h"

void Item::inputItem(){
    std::cout << "Enter item ID: " << std::endl;
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter item name (dont seperate words with space): " << std::endl;
    std::getline(std::cin, name);

    std::cout << "Enter item price: " << std::endl;
    std::cin >> price;
    std::cin.ignore();

    std::cout << "Enter item quantity: " << std::endl;
    std::cin >> quantity;

}

void Item::displayItem() const {
    std::cout << std::endl;
    std::cout << id << ": " << name << " - " << price << "$" << " | Stock: " << quantity << std::endl;
}