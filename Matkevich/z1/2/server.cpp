#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error binding");
        return -1;
    }

    if (listen(serverSocket, 5) == -1) {
        perror("Error listening");
        return -1;
    }

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;
        }

        int clientNumber;
        if (read(clientSocket, &clientNumber, sizeof(clientNumber)) == -1) {
            perror("Error reading client number");
            close(clientSocket);
            continue;
        }

        int start, end;
        if (clientNumber == 1) {
            start = 1;
            end = 10;
        } else if (clientNumber == 2) {
            start = 100;
            end = 110;
        } else {
            cerr << "Invalid client number: " << clientNumber << endl;
            close(clientSocket);
            continue;
        }

        for (int i = start; i <= end; ++i) {
            if (write(clientSocket, &i, sizeof(i)) == -1) {
                perror("Error writing to client");
                break;
            }
        }

        close(clientSocket);
    }

    close(serverSocket);

    return 0;
}

