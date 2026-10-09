#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define MAX_ARGS 64
#define IGNORE " \n\t\r"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

int main(void)
{
    char input[BUFF_SIZE];
    char *argv[MAX_ARGS];

    while (1)
    {
        printf(GREEN "minish $ " RESET);
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        int argc = 0;
        char *token = strtok(input, IGNORE);

        while (token != NULL && argc < MAX_ARGS - 1)
        {
            argv[argc++] = token;
            token = strtok(NULL, IGNORE);
        }
        argv[argc] = NULL;

        if (argv[0] == NULL)
        {
            continue;
        }

        if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], ":q") == 0)
        {
            break;
        }

        int pid = fork();

        if (pid == -1)
        {
            fprintf(stderr, "minish: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            for (int i = 0; i < argc; i++)
            {
                int target_fd;
                int flags;

                // output redirection (stdout)
                if (strcmp(argv[i], ">") == 0)
                {
                    flags = O_WRONLY | O_CREAT | O_TRUNC;
                    target_fd = STDOUT_FILENO;
                }
                else if (strcmp(argv[i], ">>") == 0)
                {
                    flags = O_WRONLY | O_CREAT | O_APPEND;
                    target_fd = STDOUT_FILENO;
                }
                // error redirection (stderr)
                else if (strcmp(argv[i], "2>") == 0)
                {
                    flags = O_WRONLY | O_CREAT | O_TRUNC;
                    target_fd = STDERR_FILENO;
                }
                else if (strcmp(argv[i], "2>>") == 0)
                {
                    flags = O_WRONLY | O_CREAT | O_APPEND;
                    target_fd = STDERR_FILENO;
                }
                // input redirection (stdin)
                else if (strcmp(argv[i], "<") == 0)
                {
                    flags = O_RDONLY;
                    target_fd = STDIN_FILENO;
                }
                else
                {
                    continue;
                }

                if ((i + 1) >= argc)
                {
                    fprintf(stderr, "minish: expected filename after '%s'\n", argv[i]);
                    exit(EXIT_FAILURE);
                }

                int fd = open(argv[i + 1], flags, 0644);
                if (fd == -1)
                {
                    perror("minish: open");
                    exit(EXIT_FAILURE);
                }

                if (dup2(fd, target_fd) == -1)
                {
                    perror("minish: dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                argv[i] = NULL;
                break;
            }

            int err = execvp(argv[0], argv);
            if (err == -1)
            {
                fprintf(stderr, "minish: %s: command not found\n", argv[0]);
                exit(EXIT_FAILURE);
            }
        }

        waitpid(pid, NULL, 0);
    }

    return EXIT_SUCCESS;
}
