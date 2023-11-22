#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

void sendAndReceiveUNIX() {
    // Создание сокета
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Ошибка при создании сокета");
        return;
    }

    // Настройка адреса сервера
    struct sockaddr_un serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sun_family = AF_UNIX;
    strncpy(serverAddr.sun_path, "server_socket", sizeof(serverAddr.sun_path) - 1);

    // Отправка данных серверу
    const char* message = "Привет от клиента UNIX!";
    ssize_t bytesSent = sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bytesSent == -1) {
        perror("Ошибка при отправке данных серверу");
        close(sockfd);
        return;
    }

    // Получение данных от сервера
    char buffer[1024];
    ssize_t bytesRead = recvfrom(sockfd, buffer, sizeof(buffer), 0, nullptr, nullptr);
    if (bytesRead == -1) {
        perror("Ошибка при чтении данных от сервера");
        close(sockfd);
        return;
    }

    // Вывод данных от сервера
    buffer[bytesRead] = '\0';
    std::cout << "Получены данные от сервера IPv4: " << buffer << std::endl;

    // Закрытие сокета
    close(sockfd);
}
