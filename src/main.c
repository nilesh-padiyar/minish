#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
        printf(GREEN "minish >>> " RESET);
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

        int pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "minish: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (strcasecmp(argv[0], "exit") == 0)
        {
            break;
        }

        if (pid == 0)
        {
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
