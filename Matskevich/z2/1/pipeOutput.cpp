#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char** argv) {
    int fd;
    char ch;

    if (argc < 2) {
        std::cerr << "dst: Too few arguments\n";
        return 1;
    }

    fd = atoi(argv[1]);

    while (read(fd, &ch, 1) > 0)
        write(1, &ch, 1);

    close(fd);
    return 0;
}

