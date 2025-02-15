//
// Created by Ali Rahbar on 2025-02-10.
//

#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "../include/table.h"

// Function to initialize a table
Table* newTable()
{
    Table* table = (Table*)malloc(sizeof(Table));
    table->numRows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        table->pages[i] = NULL;
    }
    return table;
}

// Function to free a table
void freeTable(Table* table)
{
    for (int i = 0; table->pages[i]; i++)
    {
        free(table->pages[i]);
    }
    free(table);
}

void serializeRow(Row* source, void* destination)
{
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserializeRow(void* source, Row* destination)
{
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

void* rowSlot(Table* table, uint32_t rowNum)
{
    uint32_t pageNum = rowNum / ROWS_PER_PAGE;
    void* page = table->pages[pageNum];
    if (!page)
    {
        page = table->pages[pageNum] = malloc(PAGE_SIZE);
    }
    uint32_t rowOffset = rowNum % ROWS_PER_PAGE;
    uint32_t byteOffset = rowOffset * ROW_SIZE;
    return page + byteOffset;
}

void printRow(Row* row)
{
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}


