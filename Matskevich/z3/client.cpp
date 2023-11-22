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
        // Читаем из очереди
        msgrcv(msgQueueID, &msg, sizeof(msg.mtext), 0, 0);

        // Определяем от какого сервера пришло сообщение
        if (msg.mtype == 1) {
            printf("Received from Server 1: %s\n", msg.mtext);
        } else if (msg.mtype == 2) {
            printf("Received from Server 2: %s\n", msg.mtext);
        }
    }

    return 0;
}

