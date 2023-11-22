// Сервер

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {
    // Создание сокета
    int serverSocket = socket(AF_INET6, SOCK_DGRAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        return -1;
    }

    // Настройка серверного адреса
    sockaddr_in6 serverAddr{};
    serverAddr.sin6_family = AF_INET6;
    serverAddr.sin6_addr = in6addr_any; // Принимаем соединения с любого адреса
    serverAddr.sin6_port = htons(PORT);

    // Привязка адреса к сокету
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Ошибка при привязке адреса" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Сервер запущен. Ожидание данных..." << std::endl;

    while (true) {
        // Получение данных от клиента
        sockaddr_in6 clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));

        ssize_t bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0,
                                     reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);

        if (bytesRead == -1) {
            std::cerr << "Ошибка при получении данных" << std::endl;
        } else {
            // Вывод данных от клиента
            char addrStr[INET6_ADDRSTRLEN];
            std::cout << "Получено от клиента (" << inet_ntop(AF_INET6, &(clientAddr.sin6_addr), addrStr, sizeof(addrStr)) << "): " << buffer << std::endl;
        }
    }

    // Закрытие сокета
    close(serverSocket);

    return 0;
}

