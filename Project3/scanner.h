#pragma once
/* scanner .h*/
#ifndef __SCANNER__H
#define __SCANNER__H
#define WHITE_SAPCE_CHAR ' '
#define TAB_CHAR '\t'
#define NEW_LINE_CHAR '\n'
#define MAX_TOEKN_SIZE 50
#include "fd.h"
#include "token.h"



class SCANNER {
private:
	FileDescriptor *Fd;
	// define your functions ..
	//I would define the following functions..
	// void skip_comments();
	bool isNumber(char c);
	int convertToInteger(char c);
	bool isChar(char c);
	bool isAKeyword(char * word);
	TOKEN *get_id();
	TOKEN *get_string();
	TOKEN *get_int(); // gets integers and floats
	int lineNumber ;
public:
	SCANNER();
	SCANNER(FileDescriptor *fd) { Fd = fd; };
	TOKEN* Scan();
	// You may define it as TOKEN *Scan(FileDescriptor *fd);

};

// It is helpful to define the following arrays in your .cpp file
// not in this header file

/* The keyword list is and must be kept in alphabetical order. To
add a keyword, insert it at the appropriate place in keyword[],
insert its type in the appropriate place in key type[], and
increment the var keys. Order is needed for binary search
*/
int keys = 32; /* number of keywords */
char *keyword[] = {
	"and", "begin", "boolean", "by", "constant",
	"do", "else", "end", "false", "fi", "float", "for", "from",
	"function", "if", "integer", "not", "od", "or", "procedure",
	"program", "read", "return", "string", "then", "to", "true",
	"var", "while", "write"
};

LEXEME_TYPE key_type[] = {
	kw_and, kw_begin, kw_boolean, kw_by, kw_constant,
	kw_do, kw_else, kw_end, kw_false, kw_fi,kw_float,
	kw_for, kw_from, kw_function, kw_if, kw_integer, kw_not,
	kw_od, kw_or, kw_procedure, kw_program,kw_read, kw_return,
	kw_string, kw_then, kw_to, kw_true, kw_var, kw_while, kw_write
};

#endif




