#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../include/buffer.h"
#include "../include/compiler.h"





int main(int argc, char* argv[])
{
    InputBuffer* input_buffer = newInputBuffer();
    while (true)
    {
        printPrompt();
        readInput(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            switch (doMetaCommand(input_buffer))
            {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepareStatement(input_buffer, &statement))
        {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

        executeStatement(&statement);
        printf("Executed.\n");

    }
}