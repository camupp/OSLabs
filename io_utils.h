#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>

int writeAll(int fd, const char* data, size_t size);
int readLine(int fd, std::string& line);

#endif