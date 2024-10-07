#include "inventory.h"
#include "item.h"
#include "quickSort.cpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>

void Inventory::sortInventory() {
  if (items.empty()) {
    std::cout << "Inventory is empty" << std::endl;
    return;
  }

  quickSort(items, 0, items.size() - 1);
  std::cout << "Inventory has been sorted by ID" << std::endl;
}

void Inventory::searchItems() const {
	if (items.empty()) {
		std::cout << std::endl;
		std::cout << "Inventory is empty, cant search!" << std::endl;
		std::cout << std::endl;
		
		return;
	}

	std::cout << "\nSearch options: " << std::endl;
	std::cout << "1. Search by ID: " << std::endl;
	std::cout << "2. Search by name: " << std::endl;
	std::cout << "3. Enter your choice: " << std::endl;

	int choice;
	std::cin >> choice;

	switch(choice){
		case 1:
			int searchID;
			std::cout << "Enter ID to search: " << std::endl;
			std::cin >> searchID;
			auto it = std::find_if(items.begin(), items.end(),
			  [searchID](const Item& item) { return item.id == searchID; });
			if(it != items.end()){
				std::cout << "Item found:" << std::endl;
				it->displayItem();
			} else {
				std::cout << "No item was found with " << searchID << std::endl;
			}
			break;
	}

}

void Inventory::addItem() {
  Item newItem;
  newItem.inputItem();
  bool exists = false;

  for (const auto &item : items) {
    if (item.id == newItem.id) {
      exists = true;
      break;
    }
  }
  if (exists) {
    std::cout << "ID already exists!" << std::endl;
  } else {
    items.push_back(newItem);
    std::cout << "Item has been added successfully!" << std::endl;
  }

  std::cout << std::endl;
}

void Inventory::displayInventory() {

sortInventory();

  
  if (items.empty()) {
    std::cout << std::endl;
    std::cout << "Inventory is empty" << std::endl;
    std::cout << std::endl;
    return;
  }
  for (const auto &item : items) {
    item.displayItem();
  }
	
  searchItems();
}

void Inventory::saveToFile() const {
  std::ofstream file("inventory.txt");
  if (!file) {
    std::cerr << "Error saving" << std::endl;
    return;
  }
  for (const auto &item : items) {
    file << item.id << "," << item.name << "," << item.price << ","
         << item.quantity << std::endl;
  }
  file.close();
  std::cout << "Inventory saved to the file!" << std::endl;
}

void Inventory::loadFromFile() {
  std::ifstream file("inventory.txt");
  if (!file) {
    std::cerr << "Error loading file" << std::endl;
    return;
  }
  items.clear();
  Item item;
  while (file >> item.id) {
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

void Inventory::deleteItem() {
  displayInventory();

  if (items.empty()) {
    std::cout << std::endl;
    return;
  }

  std::cout << "Enter item's ID to delete: " << std::endl;
  int id;
  while (true) {
    std::cin >> id;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter valid integer for item's ID: "
                << std::endl;
    } else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    }
  }

  bool found = false;

  for (int i = 0; i < items.size(); i++) {
    if (items[i].id == id && !found) {
      std::cout << "Found item to delete, deleting..." << std::endl;
      items.erase(items.begin() + i);
      found = true;
      break;
    }
  }
  if (!found) {
    std::cout << "Invalid ID, item was not found!" << std::endl;
    return;
  } else {
    std::cout << std::endl;
    std::cout << "Item was deleted successfully!" << std::endl;
    std::cout << std::endl;
  }
}

void Inventory::updateItem() {
  displayInventory();

  if (items.empty()) {
    std::cout << std::endl;
    return;
  }

  std::cout << "Enter item's ID to update: " << std::endl;
  int id;
  std::cin >> id;
  bool found = false;
  size_t index = 0;

  for (size_t i = 0; i < items.size(); i++) {
    if (items[i].id == id && !found) {
      std::cout << "Item was found!" << std::endl;
      found = true;
      index = i;
      break;
    }
  }

  if (found) {
    std::cout << "Your current item details: " << std::endl;
    displayInventory();

    std::cout << "What would you like to update?" << std::endl;
    std::cout << "1. Name" << std::endl;
    std::cout << "2. Price" << std::endl;
    std::cout << "3. Quantity" << std::endl;
    std::cout << "Enter your choice (1-3): ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1:
      std::cout << "Enter a new name: " << std::endl;
      while (true) {
        std::getline(std::cin, items[index].name);
        bool onlyDigits = true;

        for (char c : items[index].name) {
          if (!(std::isdigit(c) && c != ' ' && items[index].name.size() > 1)) {
            onlyDigits = false;
            break;
          }
        }
        if (!onlyDigits) {
          std::cout << "Invalid input. please enter the valid string for "
                       "updating item's name: "
                    << std::endl;
        } else {
          break;
        }
      }

      break;
    case 2:
      std::cout << "Enter a new price: " << std::endl;
      while (true) {
        std::cin >> items[index].price;

        if (std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input. Please enter valid integer for updating "
                       "the price: "
                    << std::endl;
        } else {
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
      }

      break;
    case 3:
      std::cout << "Enter a new quantity: " << std::endl;
      while (true) {
        std::cin >> items[index].quantity;

        if (std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input. Please enter a valid integer for "
                       "updating the price: "
                    << std::endl;
        } else {
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
      }

      break;
    default:
      std::cout << "Invalid choice, please try again!" << std::endl;
    }

  } else {
    std::cout << "Item not found." << std::endl;
  }
}
