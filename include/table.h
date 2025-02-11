#ifndef BITHIVE_TABLE_H
#define BITHIVE_TABLE_H

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

#include <stdint.h>

// Define Row first, as it is used in these definitions.
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

// Mark these constants as static to limit their linkage to the translation unit
static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
static const uint32_t PAGE_SIZE = 4096;

#define TABLE_MAX_PAGES 100

static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
    uint32_t numRows;
    void* pages[TABLE_MAX_PAGES];
} Table;

// Function prototypes
Table* newTable();
void freeTable(Table* table);
void* rowSlot(Table* table, uint32_t rowNum);
void printRow(Row* row);

void serializeRow(Row* source, void* destination);
void deserializeRow(void* source, Row* destination);

#endif //BITHIVE_TABLE_H
