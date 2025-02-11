#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../include/buffer.h"
#include "../include/compiler.h"
#include "../include/table.h"





int main(int argc, char* argv[])
{
    Table* table = newTable();
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

        switch (executeStatement(&statement, table))
        {
            case EXECUTE_SUCCESS:
                printf("Executed.\n");
                break;
            case EXECUTE_TABLE_FULL:
                printf("Error: Table full.\n");
                break;

        }

    }
}