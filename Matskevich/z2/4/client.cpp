#include <iostream>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

#define FIFO_NAME "myfifo"
string executeCommand(const char* cmd);
string getInfo();


int main() {
    int fifo;

    fifo = open(FIFO_NAME, O_WRONLY);
    if (fifo == -1) {
        cerr << "Cannot open fifo\n";
        return 1;
    }
    string text = getInfo();
    if (write(fifo, text.c_str(), text.length()) == -1) {
        cerr << "write() error\n";
        return 1;
    }

    close(fifo);

    return 0;
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

