#include <iostream>
#include <regex>
#include "scanner.h"
#include "SymbolTable.h"
using namespace std;


int main() {
	char * Lexemes[] =
	{
		"lx_identifier", "lx_integer", "lx_string", "lx_float","lx_float",
		/* Keywords */
		"kw_program",
		"kw_var", "kw_constant", "kw_integer", "kw_boolean", "kw_string", "kw_float",
		"kw_true", "kw_false", "kw_if", "kw_fi", "kw_then", "kw_else",
		"kw_while", "kw_do","kw_od",
		"kw_and","kw_or",
		"kw_read", "kw_write",
		"kw_for", "kw_from", "kw_to", "kw_by",
		"kw_function", "kw_procedure", "kw_return", "kw_return", "kw_begin", "kw_end",
		/* Operators */
		"lx_lparen", "lx_rparen", "lx_lbracket", "lx_rbracket", "lx_lcbracket", "lx_rcbracket","lx_not",
		"lx_colon", "lx_dot", "lx_semicolon", "lx_comma", "lx_colon_eq",
		"lx_plus", "lx_minus", "lx_star", "lx_slash",
		"lx_eq", "lx_neq", "lx_lt", "lx_le", "lx_ge", "lx_ge", "lx_eof"
	};
	//FileDescriptor *fd = new FileDescriptor("example.txt");

	//SCANNER scanner(fd);
	//TOKEN * t = NULL;
	//int i = 0;
	//while (fd->GetCurrLine() != NULL) {
	//	while ((t = scanner.Scan()) != NULL) {
	//		//cout << t->str_ptr ;
	//		cout << ++i << "\t" << t->type << "\t" << Lexemes[t->type] << endl;
	//	}
	//}

	SymbolTable * globalScope = new SymbolTable(0);
	/*SymbolTableEntry * ate = globalScope->getSymbol("ss");
	cout << "The result is" << ate<<endl;*/
	SymbolTableEntry* steIn = new SymbolTableEntry();
	steIn->entry_type = ste_var;
	steIn->f.var.type = type_integer;
	steIn->name = "X";

	/////
	SymbolTableEntry* steIn2 = new SymbolTableEntry();
	steIn2->entry_type = ste_const;
	steIn2->f.constant.value = 22;
	steIn2->name = "Const";

	///
	globalScope->putSymbol(steIn->name, steIn);
	globalScope->putSymbol(steIn2->name, steIn2);
	//SymbolTableEntry * ate = globalScope->getSymbol(steIn->name);
	//cout << "The result is" << ate->name;
	//cout << "The result is" << ate->f.var.type;
	/////
	SymbolTableEntry * ate2 = new SymbolTableEntry();// = globalScope->getSymbol(steIn2->name);
	//cout << "The result is" << ate2->name;
	//cout << "The result is" << ate2->f.constant.value;
	/////
	SymbolTable* childScope = globalScope->addNewScope();
	ate2->entry_type = ste_const;
	ate2->f.constant.value = 768;
	ate2->name = "Const2";
	childScope->putSymbol(ate2->name, ate2);
	SymbolTableEntry * ate3 = childScope->getSymbol(ate2->name);
	cout << "The result is" << ate3->f.constant.value;
	///
	ate3 = childScope->getSymbol("Const");
	cout << "searching for const \n";
	cout << "The result is" << ate3->f.constant.value;
	///////3
	SymbolTable* childScope2 = childScope->addNewScope();
	ate2->entry_type = ste_const;
	ate2->f.constant.value = 333;
	ate2->name = "Const3";
	childScope2->putSymbol(ate2->name, ate2);
	ate3 = childScope2->getSymbol(ate2->name);
	cout << "The result is" << ate3->f.constant.value;
	///
	ate3 = childScope2->getSymbol("Const");
	cout << "searching for const \n";
	cout << "The result is" << ate3->f.constant.value;
	int x = 0;
	cin >> x;
	return 0;
}