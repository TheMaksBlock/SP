#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int pf[2];
    pid_t pid1, pid2;

    if (argc < 3) {
        std::cerr << "Too few arguments\n";
        return 1;
    }

    if (pipe(pf) == -1) {
        std::cerr << "pipe() error\n";
        return 1;
    }

    if ((pid1 = fork()) == 0) {
        // Child process 1
        dup2(pf[1], 1);
        close(pf[0]);
        execlp("ls", "ls", argv[1], nullptr);
        std::cerr << "exec() [1] error\n";
        return 1;
    }

    if ((pid2 = fork()) == 0) {
        // Child process 2
        dup2(pf[0], 0);
        close(pf[1]);
        execlp("grep", "grep", "-i", argv[2], nullptr);
        std::cerr << "exec() [2] error\n";
        return 1;
    }

    // Parent process
    close(pf[0]);
    close(pf[1]);

    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);

    return 0;
}

