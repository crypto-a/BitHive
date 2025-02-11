//
// Created by Ali Rahbar on 2025-02-10.
//

#ifndef BITHIVE_COMPILER_H
#define BITHIVE_COMPILER_H

#include "buffer.h"

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
} Statement;

// Function prototypes
MetaCommandResult doMetaCommand(InputBuffer* input_buffer);
PrepareResult prepareStatement(InputBuffer* input_buffer, Statement* statement);
void executeStatement(Statement* statement);

#endif //BITHIVE_COMPILER_H
