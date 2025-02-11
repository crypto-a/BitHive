//
// Created by Ali Rahbar on 2025-02-10.
//

#include <string.h>
#include <stdlib.h>
#include <printf.h>
#include "../include/buffer.h"
#include "../include/compiler.h"
#include "../include/table.h"



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
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        // Expecting the input to be of the form: insert <id> <username> <email>
        int args_assigned = sscanf(
                input_buffer->buffer,
                "insert %d %s %s",
                &(statement->row_to_insert.id),
                statement->row_to_insert.username,
                statement->row_to_insert.email
        );
        if (args_assigned < 3) {
            // Handle syntax error (you may want to define and return a new error code)
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        return PREPARE_SUCCESS;
    }

    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}


ExecuteResult executeInsert(Statement* statement, Table* table)
{
    if (table->numRows >= TABLE_MAX_ROWS)
    {
        printf("Table is full.\n");
        return EXECUTE_TABLE_FULL;
    }
    Row* row_to_insert = &(statement->row_to_insert);

    serializeRow(row_to_insert, rowSlot(table, table->numRows));
    table->numRows += 1;

    return EXECUTE_SUCCESS;
}

ExecuteResult executeSelect(Statement* statement, Table* table)
{
    Row row;
    for (uint32_t i = 0; i < table->numRows; i++)
    {
        deserializeRow(rowSlot(table, i), &row);
        printRow(&row);
    }
    return EXECUTE_SUCCESS;
}


ExecuteResult executeStatement(Statement *statement, Table *table)
{
    switch (statement->type)
    {
        case (STATEMENT_INSERT):
        {
            return executeInsert(statement, table);
        }
        case (STATEMENT_SELECT):
        {
            return executeSelect(statement, table);
        }
    }
}
