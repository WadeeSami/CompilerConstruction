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
#include <map>
#include <iostream>
#include <string>
#endif


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
	bool isOperator(char * c);
	void skipWhiteSpaces();
	TOKEN *handleNumbers();
	TOKEN *handleKeyWords();
	TOKEN *get_id();
	TOKEN *get_string();
	TOKEN *get_int(); // gets integers and floats
	int lineNumber ;
	char peekChar;
	LEXEME_TYPE getKeyWordLexemeName(char * keyword);
public:
	SCANNER();
	SCANNER(FileDescriptor *fd) { 
		Fd = fd; 
		lineNumber = 1;
	};
	TOKEN* Scan();
	// You may define it as TOKEN *Scan(FileDescriptor *fd);

};

// It is helpful to define the following arrays in your .cpp file
// not in this header file
