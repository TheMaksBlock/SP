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
    // Создаем очереди сообщений
    int msgQueueID1 = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    int msgQueueID2 = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    // Опционально: можно вывести идентификаторы очередей для использования в других процессах
    printf("Process 1: msgQueueID1 = %d, msgQueueID2 = %d\n", msgQueueID1, msgQueueID2);

    struct message msg;

    while (1) {
        // Читаем из первой очереди
        msgrcv(msgQueueID1, &msg, sizeof(msg.mtext), 1, 0);

        // Выводим сообщение от другого процесса
        printf("Received from Process 2: %s\n", msg.mtext);

        // Подготавливаем сообщение
        msg.mtype = 2; // Тип сообщения для второй очереди
        printf("Enter message for Process 2: ");
        fgets(msg.mtext, sizeof(msg.mtext), stdin);

        // Пишем во вторую очередь
        msgsnd(msgQueueID2, &msg, sizeof(msg.mtext), 0);
    }

    return 0;
}

