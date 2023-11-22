#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

#define STR_SIZE 32

int main() {
    int pf[2];
    int pid1, pid2;
    char spf[2][STR_SIZE];

    if (pipe(pf) == -1) {
        std::cerr << "pipe() error\n";
        return 1;
    }

    snprintf(spf[0], sizeof(spf[0]), "%d", pf[0]);
    snprintf(spf[1], sizeof(spf[1]), "%d", pf[1]);

    if ((pid1 = fork()) == 0) {
        close(pf[0]);
        execl("./pipeInput", "pipeInput", spf[1], nullptr);
        std::cerr << "exec() [src] error\n";
        return 1;
    }

    if ((pid2 = fork()) == 0) {
        close(pf[1]);
        execl("./pipeOutput", "pipeOutput", spf[0], nullptr);
        std::cerr << "exec() [dst] error\n";
        return 1;
    }

    waitpid(pid1, nullptr, 0);
    close(pf[0]);
    close(pf[1]);
    waitpid(pid2, nullptr, 0);

    return 0;
}

