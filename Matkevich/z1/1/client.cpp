// client.cpp
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

int main() {
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
    

    cout<<"Enter a number: ";
    int number;
    cin>>number;
    
    if (write(clientSocket, &number, sizeof(number)) == -1) {
        perror("Error writing to server");
        return -1;
    }

    // Читаем результат от сервера
    int square;
    if (read(clientSocket, &square, sizeof(square)) == -1) {
        perror("Error reading from server");
        return -1;
    }

    // Выводим результат
    cout << "Square of " << number << " is: " << square << endl;

    // Закрываем сокет
    close(clientSocket);

    return 0;
}

