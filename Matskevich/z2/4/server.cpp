#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

#define FIFO_NAME "myfifo"
#define BUF_SIZE 512

int main(void) {
    ifstream fifo;
    char *buf;

    if (mkfifo("myfifo", 0640) == -1) {
        cerr << "Can't create fifo\n";
        return 1;
    }

    fifo.open(FIFO_NAME);
    if (!fifo.is_open()) {
        cerr << "Cannot open fifo\n";
        return 1;
    }

    buf = new char[BUF_SIZE];
    if (buf == nullptr) {
        cerr << "new char[] error\n";
        return 1;
    }
    
    while(fifo.getline(buf, BUF_SIZE)){
        cout << buf << endl;
    }
    

    fifo.close();
    delete[] buf;
    unlink(FIFO_NAME);

    return 0;
}

