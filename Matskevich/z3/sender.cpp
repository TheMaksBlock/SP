#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;
string executeCommand(const char* cmd);
string getInfo();

const char* channel_path = "my_channel";
string message_to_send = getInfo();

void sender() {
    // Создание именованного канала для записи
    ofstream output_channel(channel_path, ios::out);
    if (!output_channel) {
        cerr << "Ошибка при открытии именованного канала для записи." << endl;
        exit(EXIT_FAILURE);
    }

    // Пример передачи данных
    output_channel << message_to_send << endl;

    // Закрытие потока вывода
    output_channel.close();
}

int main() {
    sender();
    return EXIT_SUCCESS;
}

string executeCommand(const char* cmd)
{
    string result = "";
    FILE* pipe = popen(cmd, "r");

    if (!pipe)
    {
        cerr << "popen() failed\n";
        return result;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

string getInfo()
{
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    string date = buffer;

    strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
    string time = buffer;

    string osname = executeCommand("uname -a");
    string osVersion = executeCommand("date");
    string calendar = executeCommand("cal");

    return "OS Name: " + osname+ "OS Version: " + osVersion
                        + "Current Date and Time: " + date+" "+time + "\n"
                        + "Calendar:\n" + calendar;

}

