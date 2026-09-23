#include <unistd.h>
#include <string>
#include "io_utils.h"

int main() {
    std::string line;

    int status;

    while ((status = readLine(STDIN_FILENO, line)) > 0) {

        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] >= 'a' && line[i] <= 'z') {
                line[i] = line[i] - 'a' + 'A';
            }
        }

        if (writeAll(
                STDOUT_FILENO,
                line.c_str(),
                line.size()
            ) < 0) {
            return 1;
        }
    }

    if (status < 0) {
        return 1;
    }

    return 0;
}