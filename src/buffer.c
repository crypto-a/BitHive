//
// Created by Ali Rahbar on 2025-02-10.
//

#include <stdlib.h>
#include <printf.h>
#include "../include/buffer.h"

InputBuffer* newInputBuffer()
{
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->bufferLength = 0;
    input_buffer->inputLength = 0;

    return input_buffer;
}

void printPrompt()
{
    printf("bithive > ");
}

void readInput(InputBuffer* input_buffer)
{
    ssize_t bytesRead = getline(&(input_buffer->buffer), &(input_buffer->bufferLength), stdin);

    if (bytesRead <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    input_buffer->inputLength = bytesRead - 1;
    input_buffer->buffer[bytesRead - 1] = 0;
}

void closeInputBuffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}




