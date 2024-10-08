/* Project file for reading file as argument, and forking the process line by line */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char* filename = "input.txt";

char forking(char forking);

int main(int argc, char *argv[])
{
    FILE *in_file = fopen(filename, "r");

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        printf("> %s\n", file_contents);
    }

    forking(file_contents);
    fclose(in_file);
    exit(EXIT_SUCCESS);
}

char forking(char forking)
{
pid_t forkStatus;

forkStatus = fork();

/* Child... */
if        (forkStatus == 0) {
printf("Child is running, processing.\n");

sleep(30);
printf("Child is done, exiting.\n");

/* Parent... */
} else if (forkStatus != -1) {
printf("Parent is waiting...\n");

wait(NULL);
printf("Parent is exiting...\n");

} else {
perror("Error while calling the fork function");

}

return 0;

}