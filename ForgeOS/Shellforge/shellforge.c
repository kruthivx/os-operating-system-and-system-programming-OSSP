
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

int main(void)
{
    char input[MAX_INPUT];

    while (1)
    {
        printf("shellforge> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
        {
            continue;
        }

        if (strcmp(input, "exit") == 0)
        {
            break;
        }

       char *args[MAX_ARGS];
int argc = 0;

char *token = strtok(input, " \t");

while (token != NULL && argc < MAX_ARGS - 1)
{
    args[argc++] = token;
    token = strtok(NULL, " ");
}

args[argc] = NULL;

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            execvp(args[0], args);

            perror("shellforge");
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
