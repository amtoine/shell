#include "log.h"

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define BUF_SIZE 256
#define ARGV_SIZE 10

#define LOG_MESSAGE_BUF_SIZE 1024

#define PROMPT "# "
#define PROMPT_SIZE 2

int main(int argc, char *argv[]) {
  int log_level = get_log_level();
  info("starting shell", log_level);

  char buf[BUF_SIZE];

  for (;;) {
    write(STDOUT_FILENO, PROMPT, PROMPT_SIZE);
    ssize_t count = read(STDIN_FILENO, buf, BUF_SIZE);
    buf[count - 1] = '\0';

    char *child_argv[] = {[0 ... ARGV_SIZE + 1] = NULL};

    char *token, *cmd;
    int argv_idx = 1;
    token = strtok(buf, " ");
    cmd = token;
    child_argv[0] = token;
    while (token != NULL) {
      token = strtok(NULL, " ");
      child_argv[argv_idx] = token;
      argv_idx++;
    }

    char *child_envp[] = {NULL};

    debug("forking", log_level);
    pid_t pid = fork();
    if (pid == 0) {
      char msg[LOG_MESSAGE_BUF_SIZE];
      sprintf(msg, "cmd: %s", cmd);
      debug(msg, log_level);

      strcpy(msg, "args: { ");
      int i;
      for (i = 0; i < ARGV_SIZE && child_argv[i + 1] != NULL; i++) {
        strcat(msg, child_argv[i]);
        strcat(msg, ", ");
      }
      strcat(msg, child_argv[i]);
      strcat(msg, " }");
      debug(msg, log_level);

      execve(cmd, child_argv, child_envp);
      break;
    } else {
      debug("waiting", log_level);
      siginfo_t info;
      waitid(P_ALL, 0, &info, WEXITED);
    }
  }

  error("woopsies", log_level);
  return EXIT_FAILURE;
}
