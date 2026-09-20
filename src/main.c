#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

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

        if (strcasecmp(argv[0], "exit") == 0)
        {
            break;
        }

        if (argv[0] == NULL)
        {
            continue;
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
                if (strcasecmp(argv[i], ">") == 0)
                {
                    if ((i + 1) >= argc)
                    {
                        fprintf(stderr, "minish: expected filename after '>'\n");
                    }

                    int fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd == -1)
                    {
                        perror("minish: open");
                        exit(EXIT_FAILURE);
                    }
                    
                    if (dup2(fd, STDOUT_FILENO) == -1)
                    {
                        perror("minish: open");
                        close(fd);
                        exit(EXIT_FAILURE);
                    }
                    close(fd);

                    argv[i] = NULL;
                    break;
                }
            }

            int err = execvp(argv[0], argv);

            if (err == -1)
            {
                fprintf(stderr, "minish: can't access '%s': %s\n", argv[0], strerror(errno));
                exit(EXIT_FAILURE);
            }
        }

        waitpid(pid, NULL, 0);
    }

    return EXIT_SUCCESS;
}
