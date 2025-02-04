enum {
  TRACE,
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  FATAL,
  DEFAULT = INFO,
};

void error(char message[], int level);
void info(char message[], int level);
void debug(char message[], int level);

int get_log_level();
