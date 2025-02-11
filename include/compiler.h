//
// Created by Ali Rahbar on 2025-02-10.
//

#ifndef BITHIVE_COMPILER_H
#define BITHIVE_COMPILER_H

#include "buffer.h"
#include "table.h"



// Enum for meta command results
typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

// Enum for preparation results
typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

// Enum for statement types
typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

// Struct for a statement
typedef struct
{
    StatementType type;
    Row row_to_insert;
} Statement;

typedef enum { EXECUTE_SUCCESS, EXECUTE_TABLE_FULL } ExecuteResult;

// Function prototypes
MetaCommandResult doMetaCommand(InputBuffer* input_buffer);
PrepareResult prepareStatement(InputBuffer* input_buffer, Statement* statement);
ExecuteResult executeInsert(Statement* statement, Table* table);
ExecuteResult executeSelect(Statement* statement, Table* table);
ExecuteResult executeStatement(Statement *statement, Table *table);

#endif //BITHIVE_COMPILER_H
