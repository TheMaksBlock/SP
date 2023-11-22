// Клиент 2 (IPv6)

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {
    // Создание сокета
    int clientSocket = socket(AF_INET6, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        return -1;
    }

    // Настройка серверного адреса
    sockaddr_in6 serverAddr{};
    serverAddr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &(serverAddr.sin6_addr)); // IPv6 адрес сервера
    serverAddr.sin6_port = htons(PORT);

    // Отправка данных серверу
    const char* message = "Привет, сервер! - Клиент 2 (IPv6)";
    ssize_t bytesSent = sendto(clientSocket, message, strlen(message), 0,
                               reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));

    if (bytesSent == -1) {
        std::cerr << "Ошибка при отправке данных" << std::endl;
    } else {
        std::cout << "Данные успешно отправлены на сервер" << std::endl;
    }

    // Закрытие сокета
    close(clientSocket);

    return 0;
}

