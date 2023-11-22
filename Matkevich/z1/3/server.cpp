#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

int main() {
    int serverSocket1 = socket(AF_INET, SOCK_STREAM, 0);
    int serverSocket2 = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket1 == -1 || serverSocket2 == -1) {
        perror("Error creating socket");
        return -1;
    }

    sockaddr_in serverAddress1, serverAddress2;
    serverAddress1.sin_family = AF_INET;
    serverAddress1.sin_addr.s_addr = INADDR_ANY;
    serverAddress1.sin_port = htons(8081); // Порт для первого клиента

    serverAddress2.sin_family = AF_INET;
    serverAddress2.sin_addr.s_addr = INADDR_ANY;
    serverAddress2.sin_port = htons(8082); // Порт для второго клиента

    if (bind(serverSocket1, (struct sockaddr*)&serverAddress1, sizeof(serverAddress1)) == -1 ||
        bind(serverSocket2, (struct sockaddr*)&serverAddress2, sizeof(serverAddress2)) == -1) {
        perror("Error binding");
        return -1;
    }

    if (listen(serverSocket1, 5) == -1 || listen(serverSocket2, 5) == -1) {
        perror("Error listening");
        return -1;
    }

    while (true) {
        sockaddr_in clientAddress;
        socklen_t clientSize = sizeof(clientAddress);

        // Принимаем подключение от первого клиента
        int clientSocket1 = accept(serverSocket1, (struct sockaddr*)&clientAddress, &clientSize);
        if (clientSocket1 == -1) {
            perror("Error accepting connection from client 1");
            continue;
        }

        // Принимаем подключение от второго клиента
        int clientSocket2 = accept(serverSocket2, (struct sockaddr*)&clientAddress, &clientSize);
        if (clientSocket2 == -1) {
            perror("Error accepting connection from client 2");
            close(clientSocket1);
            continue;
        }

        for (int i = 1; i <= 10; ++i) {
            // Пишем данные в сокет для первого клиента
            if (write(clientSocket1, &i, sizeof(i)) == -1) {
                perror("Error writing to client 1");
                break;
            }
        }

        for (int i = 100; i <= 110; ++i) {
            // Пишем данные в сокет для второго клиента
            if (write(clientSocket2, &i, sizeof(i)) == -1) {
                perror("Error writing to client 2");
                break;
            }
        }

        // Закрываем сокеты для клиентов
        close(clientSocket1);
        close(clientSocket2);
    }

    // Закрываем сокеты сервера
    close(serverSocket1);
    close(serverSocket2);

    return 0;
}

