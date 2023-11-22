#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Структура для сообщения
struct message {
    long mtype; // Тип сообщения
    char mtext[100]; // Текст сообщения
};

int main() {
    // Создаем или присоединяемся к очереди сообщений
    key_t key = ftok("server_client_communication", 1);
    int msgQueueID = msgget(key, IPC_CREAT | 0666);

    struct message msg;

    while (1) {
        // Подготавливаем сообщение от сервера 2
        msg.mtype = 2; // Тип сообщения для сервера 2
        snprintf(msg.mtext, sizeof(msg.mtext), "Message from Server 2");

        // Пишем в очередь
        msgsnd(msgQueueID, &msg, sizeof(msg.mtext), 0);

        sleep(3); // Имитируем работу сервера
    }

    return 0;
}

