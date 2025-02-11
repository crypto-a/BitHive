//
// Created by Ali Rahbar on 2025-02-10.
//

#ifndef BITHIVE_BUFFER_H
#define BITHIVE_BUFFER_H

/* InputBuffer struct */
typedef struct
{
    char *buffer;
    int bufferLength;
    int inputLength;

} InputBuffer;

// Functions to work with InputBuffer
InputBuffer* newInputBuffer();
void printPrompt();
void readInput(InputBuffer* input_buffer);
void closeInputBuffer(InputBuffer* input_buffer);

#endif //BITHIVE_BUFFER_H
