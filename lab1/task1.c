#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

ssize_t processBuffer(char *buff, ssize_t size)
{
    ssize_t changedBytes = 0;
    for (ssize_t i = 0; i <= size; i++)
    {
        if (buff[i] >= 'a' && buff[i] <= 'z')
        {
            buff[i] -= 32;
            changedBytes++;
        }
    }
    return changedBytes;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Need input file\n");
        exit(1);
    }
    if (argc < 3)
    {
        printf("Need output file\n");
        exit(1);
    }
    char *input = argv[1];
    char *output = argv[2];
    int fIn = open(input, O_RDONLY);
    if (fIn == -1)
    {
        printf("Problem with input file %s.\n Error: %s\n", input, strerror(errno));
        exit(1);
    }
    int fOut = open(output, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fOut == -1)
    {
        printf("Problem with output file %s.\n Error: %s\n", output, strerror(errno));
        exit(1);
    }
    char buffer[512];
    int changed = 0;
    while (1)
    {
        int bytes = read(fIn, buffer, sizeof(buffer));
        for (int i = 0; i < sizeof(buffer); i++)
        {
            if (buffer[i] >= 'a' && buffer[i] <= 'z')
            {
                buffer[i] -= 32;
                changed++;
            }
        }
        write(fOut, buffer, sizeof(buffer));
        if (bytes < sizeof(buffer))
            break;
    }
    printf("Changed %d bytes\n", changed);
    close(fIn);
    close(fOut);
    return 0;
}