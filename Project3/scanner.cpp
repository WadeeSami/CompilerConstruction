#include "scanner.h"
#include <iostream>
using namespace std;
//neccessary arrays
int keys = 30; /* number of keywords */
char *keyword[] = {
	"and", "begin", "boolean", "by", "constant",
	"do", "else", "end", "false", "fi",
	"float", "for", "from", "function", "if",
	"integer", "not", "od", "or", "procedure",
	"program", "read", "return", "string", "then",
	"to", "true","var", "while", "write"
};

LEXEME_TYPE key_type[] = {
	kw_and, kw_begin, kw_boolean, kw_by, kw_constant,
	kw_do, kw_else, kw_end, kw_false, kw_fi,kw_float,
	kw_for, kw_from, kw_function, kw_if, kw_integer, kw_not,
	kw_od, kw_or, kw_procedure, kw_program,kw_read, kw_return,
	kw_string, kw_then, kw_to, kw_true, kw_var, kw_while, kw_write
};

int operatorsCount = 25; /* number of keywords */
char * operators[] = {
	"()", ":" , ":=" ,  "+" , "-" ,
	"*" , "/" ,  "=" ,  "!=" , "<" ,
	"<=" , ">" ,  ">=" ,"." , ";" ,
	"[]"  , "," ,"{}" , "(" , ")",
	":" , "{" ,"}" , "[" , "]" 
};



bool SCANNER::isNumber(char c)
{
	return ((c - '0') >= 0 && (c - '0') <= 9);
}

int SCANNER::convertToInteger(char c)
{
	return c - '0';
}

bool SCANNER::isChar(char c)
{
	return ( (c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z') );
}

bool SCANNER::isAKeyword(char * word)
{
	//cout << word;
	//loop through the array and check
	//cout<<strcat(word, "\0");
	for (int i = 0; i < keys; i++) {
		
		if (strcmp(word , keyword[i]) == 0) {
			return true;
		}
	}
	return false;
}

bool SCANNER::isOperator(char * c)
{
	for (int i = 0; i < operatorsCount; i++) {
		if (strcmp(c , operators[i]) == 0)
			return true;
	}
	return false;
}

TOKEN * SCANNER::get_id()
{
	return nullptr;
}

TOKEN * SCANNER::get_string()
{
	return nullptr;
}

TOKEN * SCANNER::get_int()
{
	return nullptr;
}

LEXEME_TYPE SCANNER::getKeyWordLexemeName(char * reserevedWord)
{
	int index ;
	for (index = 0; index < keys; index++) {
		if (strcmp(reserevedWord, keyword[index]) == 0) {
			return key_type[index];
		}
	}
}



SCANNER::SCANNER()
{
	lineNumber = 1;
}

TOKEN * SCANNER::Scan()
{
	//skip white spaces
	char peekChar = ' ';
	
	while (peekChar = Fd->GetChar()) {
		if (peekChar == WHITE_SAPCE_CHAR || peekChar == TAB_CHAR) {
			
			continue;
		}
		else if (peekChar == NEW_LINE_CHAR) {
			//next 
			
			lineNumber++;
			return NULL;
		}
		else {
			break;
		}
	}

	//handle numbers
	if (isNumber(peekChar)) {
		int v = 0;
		
		do {
			v = v * 10 + convertToInteger(peekChar);
			peekChar = Fd->GetChar();
			//cout << peekChar << endl;
		} while (isNumber(peekChar));
		//return a number token
		return new INTGER_TOKEN(lx_integer, v);
	}

	//handle keywords
	if (isChar(peekChar)) {
		//collect latters into a phrase
		char * tempBuffer = new char[MAX_TOEKN_SIZE];
		for (int i = 0; i < MAX_TOEKN_SIZE; i++) {
			tempBuffer[i] = NULL;
		}
		int index = 0;
		do {
			tempBuffer[index++] = peekChar;
			peekChar = Fd->GetChar();
		} while (isChar(peekChar) || isNumber(peekChar));
		if (isAKeyword(tempBuffer)) {
			//this is a reserved word, return its token
			return new KEYWORD_TOKEN( getKeyWordLexemeName(tempBuffer), tempBuffer);
		}
		//this is a new id
		//create a new token for it
		return new STRING_TOKEN(lx_identifier, tempBuffer);
	}

	char * opArray = new char[2];
	opArray[0] = peekChar;
	if (isOperator(opArray)) {
		peekChar = Fd->GetChar();
		opArray[1] = peekChar;
		
	}
}



