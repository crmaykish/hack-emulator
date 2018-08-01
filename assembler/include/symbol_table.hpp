#ifndef SYMBOl_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>

class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable();
    void Add(std::string key, int value);
    int Get(std::string key);
    bool Contains(std::string key);
private:
};

#endif