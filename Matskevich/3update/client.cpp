#include <iostream>
#include <csignal>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Неверное количество параметров" << std::endl;
        return 1;
    }
    int moves = std::stoi(argv[1]);

    pid_t serverPid = fork();
    
    if (serverPid == -1) {
        perror("Ошибка при создании процесса сервера");
        return 1;
    } else if (serverPid == 0) {
        execl("./server", "server", nullptr);
        perror("Ошибка при запуске сервера");
        return 1;
    } else {
    
        // Код для клиента
        sleep(1);  // Ждем немного, чтобы сервер успел инициализироваться
        while(moves>0)
        {
            // Отправляем сигнал серверу
            kill(serverPid, SIGUSR1);

            sleep(2);  // Ждем немного, чтобы сервер обработал сигнал
            moves--;
        }

        // Завершаем сервер после отправки сигнала
        kill(serverPid, SIGTERM);
    }

    return 0;
}

