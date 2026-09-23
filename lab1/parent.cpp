#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include "io_utils.h"

int main() {
    int pipe1[2];
    int pipeMiddle[2];
    int pipe2[2];

    if (pipe(pipe1) < 0 ||
        pipe(pipeMiddle) < 0 ||
        pipe(pipe2) < 0) {
        return 1;
    }


    // child1
    pid_t pid1 = fork();

    if (pid1 < 0) {
        return 1;
    }

    if (pid1 == 0) {
        if (dup2(pipe1[0], STDIN_FILENO) < 0 ||
            dup2(pipeMiddle[1], STDOUT_FILENO) < 0) {
            return 1;
        }

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipeMiddle[0]);
        close(pipeMiddle[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execl("./child1", "child1", (char*)nullptr);

        return 1;
    }


    // child2
    pid_t pid2 = fork();

    if (pid2 < 0) {
        return 1;
    }

    if (pid2 == 0) {
        if (dup2(pipeMiddle[0], STDIN_FILENO) < 0 ||
            dup2(pipe2[1], STDOUT_FILENO) < 0) {
            return 1;
        }

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipeMiddle[0]);
        close(pipeMiddle[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execl("./child2", "child2", (char*)nullptr);

        return 1;
    }


    // parent оставляет только:
    // pipe1[1] — писать child1
    // pipe2[0] — читать child2

    close(pipe1[0]);

    close(pipeMiddle[0]);
    close(pipeMiddle[1]);

    close(pipe2[1]);


    std::string line;
    std::string result;

    int status;

    while ((status = readLine(STDIN_FILENO, line)) > 0) {

        if (line[line.size() - 1] != '\n') {
            line += '\n';
        }

        if (writeAll(pipe1[1], line.c_str(), line.size()) < 0) {
            return 1;
        }

        int r = readLine(pipe2[0], result);

        if (r <= 0) {
            break;
        }

        if (writeAll(
                STDOUT_FILENO,
                result.c_str(),
                result.size()
            ) < 0) {
            return 1;
        }
    }


    close(pipe1[1]);
    close(pipe2[0]);


    int status1;
    int status2;

    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    return 0;
}