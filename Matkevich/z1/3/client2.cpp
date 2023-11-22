#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void sendAndReceiveIPv4() {
    // Создание сокета
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Ошибка при создании сокета");
        return;
    }

    // Настройка адреса сервера
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;

    // Преобразование текстового IP-адреса в структуру in_addr
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("Ошибка при преобразовании IP-адреса");
        close(sockfd);
        return;
    }

    serverAddr.sin_port = htons(8080);

    // Отправка данных серверу
    const char* message = "Привет от клиента IPv4!";
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

int main() {
    sendAndReceiveIPv4();

    return 0;
}

