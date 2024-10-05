#include <iostream>
#include "item.h"

void Item::inputItem(){
    std::cout << "Enter item ID: " << std::endl;
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter item name" << std::endl;
    std::cin >> name;
    std::cin.ignore();

    std::cout << "Enter item price: " << std::endl;
    std::cin >> price;
    std::cin.ignore();

    std::cout << "Enter item quantity: " << std::endl;
    std::cin >> quantity;
    std::cin.ignore();

}

void Item::displayItem() const {
    std::cout << std::endl;
    std::cout << id << ": " << name << " - " << price << "$" << std::endl;
    std::cout << std::endl;
}