#include "inventory.cpp"
#include "inventory.h"
#include "item.cpp"
#include "item.h"
#include <iostream>


int main() {
  Inventory inventory;
  inventory.loadFromFile();
  while (true) {
    std::cout << "1. Add a new item" << std::endl;
    std::cout << "2. Display items" << std::endl;
    std::cout << "3. Delete an item" << std::endl;
    std::cout << "4. Update an item" << std::endl;
    std::cout << "5. Data analysis" << std::endl;
    std::cout << "6. Save and exit" << std::endl;
    std::cout << "Enter your choice: " << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
      inventory.addItem();
      break;
    case 2:
      inventory.displayInventory();
      break;
    case 3:
      inventory.deleteItem();
      break;
    case 4:
      inventory.updateItem();
      break;
    case 5:
      inventory.dataAnalysis();
      break;
    case 6:
      inventory.saveToFile();
      std::cout << "Exiting..." << std::endl;
      return 0;
    }
  }
}
