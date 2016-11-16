#pragma once
#include<iostream>
#include "symbol.h"
#include <map>
#include<vector>
using namespace std;


class SymbolTable {
private:
	//SymbolTableEntr  a hashtable of symbol table entries
	int foldCase;
	//a hash
	map<char*, SymbolTableEntry*> scopeVars;
	//a vector of pointers to scopes
	vector <SymbolTable*>childrenScopes;
	SymbolTable* parent;

public:
	SymbolTable(int foldCaseFlag);
	SymbolTableEntry* getSymbol(char * str);
	SymbolTableEntry* putSymbol(char * str, SymbolTableEntry* ste);
	void clearSymbolTable();
	void printSymbolTable();
	SymbolTable* addNewScope();
	void assignParentScope(SymbolTable* scope);
};