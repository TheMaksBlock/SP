#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

// Структура для сообщения
struct message {
    long mtype; // Тип сообщения
    char mtext[100]; // Текст сообщения
};

// Идентификатор очереди
int msgQueueID;

// Функция для потока-клиента
void *clientThread(void *arg) {
    struct message msg;
    
    // Присоединяемся к существующей очереди
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    
    // Подготавливаем сообщение
    msg.mtype = 1; // Пример: тип сообщения равен 1
    snprintf(msg.mtext, sizeof(msg.mtext), "Hello from client thread!");
    
    // Отправляем сообщение
    msgsnd(msgQueueID, &msg, sizeof(msg.mtext), 0);

    // Ожидаем ответа
    msgrcv(msgQueueID, &msg, sizeof(msg.mtext), 2, 0);

    // Выводим полученное сообщение
    printf("Client Thread received: %s\n", msg.mtext);

    // Отсоединяемся от очереди
    msgctl(msgid, IPC_RMID, NULL);

    pthread_exit(NULL);
}

int main() {
    // Создаем или подключаемся к существующей очереди
    msgQueueID = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    // Создаем поток для клиента
    pthread_t thread;
    pthread_create(&thread, NULL, clientThread, NULL);

    struct message msg;

    // Ждем сообщение от клиента
    msgrcv(msgQueueID, &msg, sizeof(msg.mtext), 1, 0);

    // Выводим полученное сообщение
    printf("Server received: %s\n", msg.mtext);

    // Подготавливаем ответ
    msg.mtype = 2; // Пример: тип ответного сообщения равен 2
    snprintf(msg.mtext, sizeof(msg.mtext), "Hello from server!");

    // Отправляем ответ клиенту
    msgsnd(msgQueueID, &msg, sizeof(msg.mtext), 0);

    // Ждем завершения потока
    pthread_join(thread, NULL);

    // Отсоединяемся от очереди
    msgctl(msgQueueID, IPC_RMID, NULL);

    return 0;
}

