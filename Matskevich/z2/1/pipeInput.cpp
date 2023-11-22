#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/utsname.h>
#include <ctime>

using namespace std;  // Глобальная директива using

#define WAIT_SECS 2

string executeCommand(const char* cmd);
string getInfo();

int main(int argc, char** argv) {
    int i, fd;

    if (argc < 2) {
        cerr << "src: Too few arguments\n";
        return 1;
    }

    fd = atoi(argv[1]);
    cerr << "Wait please";

    for (i = 0; i < WAIT_SECS; i++, sleep(1))
        cerr << ".";

    cerr << "\n";

    string info = getInfo();
    if (write(fd, info.c_str(), info.length()) == -1) {
        cerr << "src: write() error\n";
        return 1;
    }

    close(fd);
    return 0;
}

string executeCommand(const char* cmd) {
    string result = "";
    FILE* pipe = popen(cmd, "r");

    if (!pipe) {
        cerr << "popen() failed\n";
        return result;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

string getInfo() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    string date = buffer;

    strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
    string time = buffer;

    utsname unameData;
    uname(&unameData);
    string osname = unameData.sysname;
    string osVersion = unameData.release;
    string calendar = executeCommand("cal");

    return "OS Name: " + osname + "OS Version: " + osVersion +
           "Current Date and Time: " + date + " " + time + "\n" +
           "Calendar:\n" + calendar;
}

