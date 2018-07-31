#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol_table.h"
#include "str_utils.h"

typedef struct Symbol {
    char *key;
    int value;
} Symbol;

struct SymbolTable {
    Symbol symbols[MAX_SYMBOLS];
    int index;
};

SymbolTable* SymbolTable_Create() {
    SymbolTable *symbol_table = calloc(1, sizeof(SymbolTable));

    symbol_table->index = 0;
}

void SymbolTable_Destroy(SymbolTable *symbol_table) {
    // TODO: free all the symbol keys

    free(symbol_table);
}

void SymbolTable_Add(SymbolTable *symbol_table, char *key, int value) {
    // TODO: don't add duplicate symbols
    // TODO: array bounds and null checking

    printf("Add: %s\n", key);
    printf("Len: %d\n", strlen(key));

    Symbol s = {
        key = key,
        value = value
    };
    
    symbol_table->symbols[symbol_table->index] = s;

    symbol_table->index++;
}

int SymbolTable_Get(SymbolTable *symbol_table, char *key) {
    int result = NO_SYMBOL;

    for (int i = 0; i < symbol_table->index; i++) {
        if (strcmp(key, symbol_table->symbols[i].key) == 0) {
            // Found a matching symbol, return it
            result = symbol_table->symbols[i].value;
            break;
        }
    }

    return result;
}