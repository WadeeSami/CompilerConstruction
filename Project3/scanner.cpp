#include "scanner.h"

//neccesarry arrays
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






bool SCANNER::isNumber(char c)
{
	return ((c - '0') >= 0 && (c - '0') <= 0);
}

int SCANNER::convertToInteger(char c)
{
	return c - '0';
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

TOKEN * SCANNER::Scan()
{
	//skip white spaces
	char peekChar;
	for (; ; peekChar = Fd->GetChar()) {
		if (peekChar == WHITE_SAPCE_CHAR || peekChar == TAB_CHAR) {

		}
		else if (peekChar == NEW_LINE_CHAR) {
			//next line
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
		} while (isNumber(peekChar));
		//return a number token
	}
}
