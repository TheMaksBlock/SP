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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Неверное количество параметров \n");
        return 1;
    }    
    
    int msgQueueID1 = atoi(argv[1]);
    int msgQueueID2 = atoi(argv[2]);

    struct message msg;

    while (1) {
        // Подготавливаем сообщение
        msg.mtype = 1; // Тип сообщения для первой очереди
        printf("Enter message for Process 1: ");
        fgets(msg.mtext, sizeof(msg.mtext), stdin);

        // Пишем в первую очередь
        msgsnd(msgQueueID1, &msg, sizeof(msg.mtext), 0);

        // Читаем из второй очереди
        msgrcv(msgQueueID2, &msg, sizeof(msg.mtext), 2, 0);

        // Выводим сообщение от другого процесса
        printf("Received from Process 1: %s\n", msg.mtext);
    }

    return 0;
}

