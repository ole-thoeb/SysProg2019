#pragma once

#include "mystddef.h"

char **shell_split(char *input);
pid_t run_command(char **argv, int no_fork);
int run_cmdline(char **argv);