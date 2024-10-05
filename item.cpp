#include <iostream>
#include <limits>
#include <cctype>
#include "item.h"

void Item::inputItem(){
    std::cout << "Enter item ID: " << std::endl;
    while(true){
        std::cin >> id;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer for item ID:  " << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    std::cout << "Enter item name (dont seperate words with space): " << std::endl;
    while(true){
        std::getline(std::cin, name);
        bool onlyDigits = true;

        for(char c : name){
            if(!(std::isdigit(c) && c != ' ')){
                onlyDigits = false;
                break;
            }
        }

        if(onlyDigits){
            std::cout << "Invalid input. Enter valid string for item name: " << std::endl;
        } else {
            break;
        }
    }

    std::cout << "Enter item price: " << std::endl;
    while(true){
        std::cin >> price;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer for item price: " << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    std::cout << "Enter item quantity: " << std::endl;
    while(true){
        std::cin >> quantity;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer for item quantity: " << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

}

void Item::displayItem() const {
    std::cout << std::endl;
    std::cout << id << ": " << name << " - " << price << "$" << " | Stock: " << quantity << std::endl;
    std::cout << std::endl;
}