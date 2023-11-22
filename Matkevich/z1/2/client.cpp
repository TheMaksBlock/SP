#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <client_number>" << endl;
        return 1;
    }

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to server");
        return -1;
    }

    int clientNumber = atoi(argv[1]);
    if (write(clientSocket, &clientNumber, sizeof(clientNumber)) == -1) {
        perror("Error writing to server");
        return -1;
    }

    int number;
    while (read(clientSocket, &number, sizeof(number)) > 0) {
        cout << "Received: " << number << endl;
    }

    close(clientSocket);

    return 0;
}

