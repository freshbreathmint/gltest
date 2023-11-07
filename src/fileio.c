#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *filename)
{
    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return NULL;
    }

    // Find out how big the file is
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Allocate memory for the file
    char *buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file: %s\n", filename);
        fclose(file);
        return NULL;
    }

    // Read file into the buffer
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        printf("Failed to read file: %s\n", filename);
        fclose(file);
        return NULL;
    }

    // Close file and return buffer.
    buffer[fileSize] = '\0'; // Add null-terminator to end of file.

    fclose(file);
    return buffer;
}

void freeFile(char *fileContent)
{
    free(fileContent);
}