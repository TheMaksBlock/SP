#include <iostream>
#include <fstream>

using namespace std;

int main() {
    char ch;
    ifstream file("myfile");

    if (!file.is_open()) {
        cerr << "Unable to open file\n";
        return 1;
    }

    // Redirect stdin to the file
    streambuf *original_stdin = cin.rdbuf(file.rdbuf());

    // Read from stdin and write to stdout
    while (cin.get(ch)) {
        cout.put(ch);
    }

    // Restore stdin
    cin.rdbuf(original_stdin);
    file.close();

    return 0;
}

