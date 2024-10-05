#include "item.h"
#include "inventory.h"
#include <iostream>
#include <fstream>

void Inventory::addItem(){
    Item newItem;
    newItem.inputItem();
    items.push_back(newItem);
    std::cout << "Item has added successfully!" << std::endl;
    std::cout << std::endl;
}

void Inventory::displayInventory() const {
    if(items.empty()) {
        std::cout << "Inventory is empty" << std::endl;
        return;
    }
    for(const auto& item : items){
        item.displayItem();
    }
}

void Inventory::saveToFile() const {
    std::ofstream file("inventory.txt");
    if (!file) {
        std::cerr << "Error saving" << std::endl;
        return;
    }
    for(const auto& item: items){
        file << item.id << "," << item.name << "," << item.price << "," << item.quantity;
    }
    file.close();
    std::cout << "Inventory saved to the file!" << std::endl;
}

void Inventory::loadFromFile(){
    std::ifstream file("inventory.txt");
    if(!file){
        std::cerr << "Error loading file" << std::endl;
        return;
    }
    items.clear();
    Item item;
    while(file >> item.id){
        file.ignore();
        std::getline(file, item.name, ',');
        file >> item.price;
        file.ignore();
        file >> item.quantity;
        items.push_back(item);
    }
    file.close();
    std::cout << "Loaded items from the file" << std::endl;
    std::cout << std::endl;
}

void Inventory::deleteItem(){
    displayInventory();

    std::cout << "Enter item's ID to delete: " << std::endl;
    int id;
    std::cin >> id;
    bool found = false;

    if(items.empty()){
        std::cerr << "Inventory is empty!" << std::endl;
        return;
    }

    
    for(int i = 0; i < items.size(); i++){
        if(items[i].id == id && !found){
            std::cout << "Found item to delete, deleting..." << std::endl;
            items.erase(items.begin() + i);
            found = true;
            break;
        }
    }
    if(!found){
        std::cout << "Invalid ID, item was not found!" << std::endl;
        return;
    } else { 
        std::cout << "Item was deleted successfully!" << std::endl;
    }
}

void Inventory::updateItem(){
    displayInventory();

    std::cout << "Enter item's ID to update: " << std::endl;
    int id;
    std::cin >> id;
    bool found = false;
    size_t index = 0;

    if(items.empty()){
        std::cout << "Inventory is empty!" << std::endl;
        return;
    }

    for(size_t i = 0; i < items.size(); i++){
        if(items[i].id == id && !found){
            std::cout << "Item was found!" << std::endl;
            found = true;
            index = i;
            break;
        }
    }

    if(found){
        std::cout << "Your current item details: " << std::endl;
        displayInventory();

        std::cout << "What would you like to update?" << std::endl;
        std::cout << "1. Name" << std::endl;
        std::cout << "2. Price" << std::endl;
        std::cout << "3. Quantity" << std::endl;
        std::cout << "Enter your choice (1-3): ";

        int choice;
        std::cin >> choice;

        switch(choice){
            case 1:
                std::cout << "Enter a new name: " << std::endl;
                std::cin >> items[index].name;
                break;
            case 2:
                std::cout << "Enter a new price: " << std::endl;
                std::cin >> items[index].price;
                break;
            case 3:
                std::cout << "Enter a new quantity: " << std::endl;
                std::cin >> items[index].quantity;
                break;
            default:
                std::cout << "Invalid choice, please try again!" << std::endl;
        }

    } else {
        std::cout << "Item not found." << std::endl;
    }
}