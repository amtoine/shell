#include "log.h"
#include "ANSI-color-codes.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

void __log(char message[], char color[], char marker[], int level,
           int threshold) {
  if (level <= threshold) {
    printf("[%s%s%s] %s\n", color, marker, reset, message);
  }
}

// clang-format off
void error(char message[], int level) { __log(message, RED,  "#", level, ERROR); }
void info (char message[], int level) { __log(message, BBLU, "?", level, INFO); }
void debug(char message[], int level) { __log(message, GRN,  ".", level, DEBUG); }
// clang-format on

int get_log_level() {
  char *log_level = getenv("LOG_LEVEL");
  int level;
  if (log_level == NULL) {
    level = DEFAULT;
  } else if (strcmp(log_level, "FATAL") == 0) {
    level = FATAL;
  } else if (strcmp(log_level, "ERROR") == 0) {
    level = ERROR;
  } else if (strcmp(log_level, "WARNING") == 0) {
    level = WARNING;
  } else if (strcmp(log_level, "INFO") == 0) {
    level = INFO;
  } else if (strcmp(log_level, "DEBUG") == 0) {
    level = DEBUG;
  } else if (strcmp(log_level, "TRACE") == 0) {
    level = TRACE;
  } else {
    level = DEFAULT;
  }
  return level;
}
