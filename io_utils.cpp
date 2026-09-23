#include "io_utils.h"
#include <unistd.h>

int writeAll(int fd, const char* data, size_t size) {
    size_t pos = 0;

    while (pos < size) {
        ssize_t n = write(fd, data + pos, size - pos);

        if (n <= 0) {
            return -1;
        }

        pos += n;
    }

    return 0;
}

int readLine(int fd, std::string& line) {
    line.clear();

    char c;

    while (true) {
        ssize_t n = read(fd, &c, 1);

        if (n < 0) {
            return -1;
        }

        if (n == 0) {
            return line.empty() ? 0 : 1;
        }

        line += c;

        if (c == '\n') {
            return 1;
        }
    }
}