#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <адрес сервера> <имя файла>" << std::endl;
        return 1;
    }

    const char* host = argv[1];
    const char* port = "80";
    const char* filename = argv[2];

    // Структура для хранения адреса сервера
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Получение информации об адресе сервера
    int status = getaddrinfo(host, port, &hints, &res);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return 1;
    }

    // Создание сокета
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        perror("Ошибка при создании сокета");
        freeaddrinfo(res);
        return 1;
    }

    // Подключение к серверу
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("Ошибка при подключении");
        close(sockfd);
        freeaddrinfo(res);
        return 1;
    }

    // Формирование HTTP-запроса
    const char* httpRequest = "GET / HTTP/1.1\r\nHost: ";
    char fullRequest[256];
    snprintf(fullRequest, sizeof(fullRequest), "%s%s\r\nConnection: close\r\n\r\n", httpRequest, host);

    // Отправка HTTP-запроса
    if (send(sockfd, fullRequest, strlen(fullRequest), 0) == -1) {
        perror("Ошибка при отправке запроса");
        close(sockfd);
        freeaddrinfo(res);
        return 1;
    }

    // Чтение и запись ответа в файл
    std::ofstream outputFile(filename, std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        perror("Ошибка при открытии файла для записи");
        close(sockfd);
        freeaddrinfo(res);
        return 1;
    }

    char buffer[4096];
    int bytesRead;
    bool headersFinished = false;

    while ((bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';

        if (!headersFinished) {
            // Поиск пустой строки, разделяющей заголовки и тело ответа
            char* bodyStart = strstr(buffer, "\r\n\r\n");
            if (bodyStart != nullptr) {
                bodyStart += 4; // Перейти к началу тела ответа после пустой строки
                headersFinished = true;
                outputFile << bodyStart; // Записать первый фрагмент тела ответа
            }
        } else {
            outputFile << buffer; // Записать оставшуюся часть тела ответа
        }
    }

    // Закрытие сокета, файла и освобождение ресурсов
    close(sockfd);
    freeaddrinfo(res);
    outputFile.close();

    std::cout << "Данные успешно записаны в файл: " << filename << std::endl;

    return 0;
}

