#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char* socket_path = "/tmp/inventory_socket";

    while (true) {
        int client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (client_fd == -1) {
            std::cerr << "Socket creation failed\n";
            return 1;
        }

        struct sockaddr_un server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);

        if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            std::cerr << "Connection failed\n";
            return 1;
        }

        std::cout << "Enter command (DISPLAY, ADD id name price quantity, or QUIT): ";
        std::string request;
        std::getline(std::cin, request);

        if (request == "QUIT") break;

        send(client_fd, request.c_str(), request.length(), 0);

        char buffer[1024] = {0};
        read(client_fd, buffer, sizeof(buffer));
        std::cout << buffer;

        close(client_fd);
    }

    return 0;
}

