#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Item {
    int id;
    std::string name;
    double price;
    int quantity;
};

class Inventory {
private:
    std::vector<Item> items;

public:
    void displayInventory() {
        if (items.empty()) {
            std::cout << "Inventory is empty.\n";
            return;
        }
        for (const auto& item : items) {
            std::cout << "ID: " << item.id << ", Name: " << item.name 
                      << ", Price: $" << item.price << ", Quantity: " << item.quantity << "\n";
        }
    }

    void addItem(int id, const std::string& name, double price, int quantity) {
        items.push_back({id, name, price, quantity});
        std::cout << "Item added successfully.\n";
    }
};

int main() {
    Inventory inventory;

    while (true) {
        std::cout << "Enter command (DISPLAY, ADD id name price quantity, or QUIT): ";
        std::string request;
        std::getline(std::cin, request);

        if (request == "QUIT") break;

        if (request == "DISPLAY") {
            inventory.displayInventory();
        }
        else if (request.substr(0, 3) == "ADD") {
            std::istringstream iss(request.substr(4));
            int id, quantity;
            std::string name;
            double price;

            if (iss >> id >> name >> price >> quantity) {
                inventory.addItem(id, name, price, quantity);
            }
            else {
                std::cout << "Invalid ADD command format.\n";
            }
        }
        else {
            std::cout << "Invalid command.\n";
        }
    }

    return 0;
}
