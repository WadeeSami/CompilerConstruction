#include "SymbolTable.h"

SymbolTable::SymbolTable(int foldCaseFlag)
{
	cout << "Hello from the other side\n";
	this->foldCase = foldCaseFlag;
	//initialize with datastructure with the global scope
}

SymbolTableEntry * SymbolTable::getSymbol(char * str)
{
	map<char *, SymbolTableEntry *>::iterator searchMap = this->scopeVars.find(str);
	if (searchMap != this->scopeVars.end()) {
		//element exists
		cout << "This variable  exists" << endl;
		return this->scopeVars[str];
	}
	else {
		cout << "will search for parent\n";
		while (this->parent != nullptr) {
			return this->parent->getSymbol(str);
		}
		cout << "variable does not exist\n";
	}
	return nullptr;
}

SymbolTableEntry * SymbolTable::putSymbol(char * str, SymbolTableEntry* ste)
{
	map<char *, SymbolTableEntry *>::iterator searchMap = this->scopeVars.find(str);
	if (searchMap != this->scopeVars.end()) {
		//element exists
		cout << "This variable already exists" << endl;
		return this->scopeVars[str];
	}
	else {
		//add a new elements
		this->scopeVars[str] = ste;
		return this->scopeVars[str];

	}
	
	
}

void SymbolTable::clearSymbolTable()
{
	this->scopeVars.clear();
}

void SymbolTable::printSymbolTable()
{
}

SymbolTable* SymbolTable::addNewScope()
{
	SymbolTable* childScope = new SymbolTable(this->foldCase);
	//assign parent
	childScope->assignParentScope(this);
	this->childrenScopes.push_back(childScope);
	return childScope;
}

void SymbolTable::assignParentScope(SymbolTable * scope)
{
	this->parent = scope;
}
