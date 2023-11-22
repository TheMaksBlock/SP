#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const char* channel_path = "my_channel";
string received_message;


    

int main() {
    // Создание именованного канала для чтения
    ifstream input_channel(channel_path, ios::in);
    if (!input_channel) {
        cerr << "Ошибка при открытии именованного канала для чтения." << endl;
        exit(EXIT_FAILURE);
    }
    
    // Вывод полученного сообщения
    cout << "Получено сообщение: " <<endl;
    while(getline(input_channel, received_message)){
        cout << received_message <<endl;
    }
    

    // Закрытие потока ввода
    input_channel.close();

    
    // Удаление именованного канала
    if (remove(channel_path) != 0) {
        cerr << "Ошибка при удалении именованного канала." << endl;
        exit(EXIT_FAILURE);
    }
}

