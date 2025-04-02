#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintTableBorder(int *columnWidths, int columnCount)
{
    for (int i = 0; i < columnCount; i++) {
        printf("+");
        for (int j = 0; j < columnWidths[i] + 2; j++) {
            printf("-");
        }
    }
    printf("+\n");
}
void PrintTableHeader(Table *table)
{
    PrintTableBorder(table->columnWidths, table->columnCount);
    printf("|");
    for (int i = 0; i < table->columnCount; i++) {
        printf(" %-*s |", table->columnWidths[i], table->headers[i]);
    }
    printf("\n");
    PrintTableBorder(table->columnWidths, table->columnCount);
}
void AddRow(Table *table, char **rowData)
{
    TableRow *newRow = (TableRow *)malloc(sizeof(TableRow));
    newRow->columns = (char **)malloc(table->columnCount * sizeof(char *));
    newRow->next = NULL;

    for (int i = 0; i < table->columnCount; i++) {
        newRow->columns[i] = strdup(rowData[i]);
        int len = strlen(rowData[i]);
        if (len > table->columnWidths[i]) {
            table->columnWidths[i] = len;
        }
    }

    if (table->rows == NULL) {
        table->rows = newRow;
    } else {
        TableRow *temp = table->rows;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newRow;
    }

    table->rowCount++;
}
void PrintTable(Table *table)
{
    PrintTableHeader(table);

    TableRow *currentRow = table->rows;
    while (currentRow != NULL) {
        printf("|");
        for (int i = 0; i < table->columnCount; i++) {
            printf(" %-*s |", table->columnWidths[i], currentRow->columns[i]);
        }
        printf("\n");
        currentRow = currentRow->next;
    }

    PrintTableBorder(table->columnWidths, table->columnCount);
}
Table NewTable(char **headers, int columnCount)
{
    Table table;
    table.headers = headers;
    table.columnWidths = (int *)malloc(columnCount * sizeof(int));
    table.columnCount = columnCount;
    table.rows = NULL;
    table.rowCount = 0;

    for (int i = 0; i < columnCount; i++) {
        table.columnWidths[i] = strlen(headers[i]);
    }

    return table;
}
