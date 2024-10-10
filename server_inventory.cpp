#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

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
    std::string displayInventory() {
        if (items.empty()) {
            return "Inventory is empty.\n";
        }
        std::stringstream ss;
        for (const auto& item : items) {
            ss << "ID: " << item.id << ", Name: " << item.name 
               << ", Price: $" << item.price << ", Quantity: " << item.quantity << "\n";
        }
        return ss.str();
    }

    std::string addItem(int id, const std::string& name, double price, int quantity) {
        items.push_back({id, name, price, quantity});
        // Log the addition to the server console
        std::cout << "Server: Item added - ID: " << id << ", Name: " << name 
                  << ", Price: $" << price << ", Quantity: " << quantity << std::endl;
        return "Item added successfully.\n";
    }
};

int main() {
    const char* socket_path = "/tmp/inventory_socket";
    Inventory inventory;

    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    struct sockaddr_un server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);

    unlink(socket_path);
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(server_fd, 5) == -1) {
        std::cerr << "Listen failed\n";
        return 1;
    }

    std::cout << "Server is listening...\n";

    while (true) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            std::cerr << "Accept failed\n";
            continue;
        }

        char buffer[1024] = {0};
        read(client_fd, buffer, sizeof(buffer));

        std::string response;
        std::string request(buffer);

        // Log the received command
        std::cout << "Server: Received command: " << request << std::endl;

        if (request == "DISPLAY") {
            response = inventory.displayInventory();
        }
        else if (request.substr(0, 3) == "ADD") {
            std::istringstream iss(request.substr(4));
            int id, quantity;
            std::string name;
            double price;

            if (iss >> id >> name >> price >> quantity) {
                response = inventory.addItem(id, name, price, quantity);
            }
            else {
                response = "Invalid ADD command format.\n";
                std::cout << "Server: Invalid ADD command received" << std::endl;
            }
        }
        else {
            response = "Invalid command.\n";
            std::cout << "Server: Invalid command received" << std::endl;
        }

        write(client_fd, response.c_str(), response.length());
        close(client_fd);
    }

    close(server_fd);
    unlink(socket_path);
    return 0;
}
