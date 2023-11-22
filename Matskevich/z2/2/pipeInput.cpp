#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <ctime>

using namespace std;

#define FILENAME "myfile"

string executeCommand(const char* cmd);
string getInfo();

int main()
{
    char ch;
    ofstream file(FILENAME);

    if (!file.is_open())
    {
        cerr << "Unable to open file\n";
        return 1;
    }

    // Redirect stdout to the file
    streambuf *original_stdout = cout.rdbuf(file.rdbuf());

    cout<<getInfo();

    // Restore stdout
    cout.rdbuf(original_stdout);
    file.close();

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

    utsname unameData;
    string osname = executeCommand("uname -a");
    string osVersion = executeCommand("date");
    string calendar = executeCommand("cal");

    return "OS Name: " + osname+ "OS Version: " + osVersion
                        + "Current Date and Time: " + date+" "+time + "\n"
                        + "Calendar:\n" + calendar;

}



