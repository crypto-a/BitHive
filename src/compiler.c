//
// Created by Ali Rahbar on 2025-02-10.
//

#include <string.h>
#include <stdlib.h>
#include <printf.h>
#include "../include/buffer.h"
#include "../include/compiler.h"



MetaCommandResult doMetaCommand(InputBuffer* input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        closeInputBuffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}


PrepareResult prepareStatement(InputBuffer* input_buffer, Statement* statement)
{
    // Check if the first word is "insert"
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }

    // Check if the first word is "select"
    if (strcmp(input_buffer->buffer, "select") == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    // Return unrecognized statement
    return PREPARE_UNRECOGNIZED_STATEMENT;
}


void executeStatement(Statement* statement)
{
    switch (statement->type)
    {
        case (STATEMENT_INSERT):
            printf("This is where we would do an insert.\n");
            break;
        case (STATEMENT_SELECT):
            printf("This is where we would do a select.\n");
            break;
    }
}
