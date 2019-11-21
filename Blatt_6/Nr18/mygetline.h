#pragma once

#include "mystddef.h"

ssize_t mygetline(char **buf, size_t *buflen, int fd);
size_t increaseBuffer(void **buf, size_t *buflen, size_t size);