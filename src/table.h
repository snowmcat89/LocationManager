#ifndef TABLE_H_
#define TABLE_H_

typedef struct TableRow {
    char **columns;
    struct TableRow *next;
} TableRow;
typedef struct Table {
    char **headers;
    int *columnWidths;
    int columnCount;
    TableRow *rows;
    int rowCount;
} Table;

extern void PrintTableBorder(int *columnWidths, int columnCount);
extern void PrintTableHeader(Table *table);
extern void AddRow(Table *table, char **rowData);
extern void PrintTable(Table *table);
extern Table NewTable(char **headers, int columnCount);
#endif