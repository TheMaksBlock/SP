// server.cpp
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

int main() {
    // Создаем сокет
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        return -1;
    }

    // Задаем параметры сервера
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // Привязываем сокет к адресу и порту
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error binding");
        return -1;
    }

    // Слушаем подключения
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening");
        return -1;
    }

    // Принимаем клиентский запрос
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1) {
        perror("Error accepting connection");
        return -1;
    }

    // Читаем число от клиента
    int number;
    if (read(clientSocket, &number, sizeof(number)) == -1) {
        perror("Error reading from client");
        return -1;
    }

    // Возводим число в квадрат
    int square = number * number;

    // Отправляем результат клиенту
    if (write(clientSocket, &square, sizeof(square)) == -1) {
        perror("Error writing to client");
        return -1;
    }

    // Закрываем сокеты
    close(clientSocket);
    close(serverSocket);

    return 0;
}

