#include <unistd.h>
#include <string>
#include "io_utils.h"

int main() {
    std::string line;

    int status;

    while ((status = readLine(STDIN_FILENO, line)) > 0) {

        std::string result;

        bool previousWasSpace = false;

        for (size_t i = 0; i < line.size(); ++i) {

            if (line[i] == ' ') {
                if (previousWasSpace) {
                    continue;
                }

                previousWasSpace = true;
            }
            else {
                previousWasSpace = false;
            }

            result += line[i];
        }

        if (writeAll(
                STDOUT_FILENO,
                result.c_str(),
                result.size()
            ) < 0) {
            return 1;
        }
    }

    if (status < 0) {
        return 1;
    }

    return 0;
}