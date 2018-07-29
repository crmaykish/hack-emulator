#ifndef SYMBOl_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SYMBOLS 64

static const int NO_SYMBOL = -1;

typedef struct SymbolTable SymbolTable;

SymbolTable* SymbolTable_Create();
void SymbolTable_Destroy(SymbolTable *symbol_table);

void SymbolTable_Add(SymbolTable *symbol_table, char *key, int value);
int SymbolTable_Get(SymbolTable *symbol_table, char *key);

#endif