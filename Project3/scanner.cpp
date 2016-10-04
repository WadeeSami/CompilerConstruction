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
LEXEME_TYPE operator_type[] =
{
	lx_colon,lx_plus , lx_minus , lx_not ,
	lx_star ,lx_slash,lx_eq,lx_lt,
	lx_gt , lx_dot , lx_semicolon,
	lx_comma, lx_lparen,lx_rparen,
	lx_lcbracket ,lx_rcbracket ,lx_lbracket,lx_rbracket
};

int operatorsCount = 18; /* number of operators */
char  operators[] = {
	 ':'  ,  '+' , '-' ,'!',
	'*' , '/' ,  '='  , '<' ,
	'>'  ,'.' , ';' ,
	 ',' , '(' , ')',
	 '{' ,'}' , '[' , ']' 
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

bool SCANNER::isIdentefier(char * word)
{
	bool legallId = false;
	if (!isChar(word[0]))
	{
		return legallId;
	}
	legallId = true;
	int index = 1;
	while (index < MAX_TOEKN_SIZE && (isChar(word[index]) || isNumber(word[index]) || word[index] == '_'))
	{
		if (!isNumber(word[index]) && !isChar(word[index]) && word[index] != '_')
		{
			legallId = false;
			break;
		}
		else
			legallId = true;
		index++;
	}
	return legallId;
}

bool SCANNER::isInteger(char * word)
{
	if(!isNumber(word[0]))
		return false;
	int index = 1;
	bool isInteger = true;
	while (index < MAX_TOEKN_SIZE)
	{
		if (!isNumber(word[index]) && word[index]!='\0')
		{
			isInteger = false;
			break;
		}
		index++;
	}
	return isInteger;
}

bool SCANNER::isFloat(char * word)
{
	if (atof(word) == 0.0)
		return false;
	else
		return true;
}

TOKEN * SCANNER::isOpertor(char * word)
{
	OPERATOR_TOKEN * operatorToken = NULL;
	int index = 0;
	int state = 0;
	while (this->isOperator(word[index]) && word[index] != '\0') {
		switch (state)
		{
		case 0:
			//check the character
			if (word[index] == '>')state = 1;
			else if (word[index] == '<')state = 2;
			else if (word[index] == ':')state = 3;
			else if (word[index] == '!')state = 4;
			else if (this->isOperator(word[index]))state = 5;
			else return NULL;
			break;
		case 1:
			index++;
			if (word[index] == '=')
			{
				//this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_ge, ">=");
			}
			break;
		case 2:
			index++;
			if (word[index] == '=')
			{
				//this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_le, "<=");
			}
			break;
		case 3:
			//this->peekChar = Fd->GetChar();
			index++;
			if (word[index] == '=')
			{
				//this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_colon_eq, ":=");
			}
			break;
		case 4:
			//this->peekChar = Fd->GetChar();
			index++;
			if (word[index] == '=')
			{
				//this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_neq, "!=");
			}
			break;
		case 5:
			return operatorToken = new OPERATOR_TOKEN(this->getOperatorLexemeName(word[index]), &word[index]);
			break;
		default:
			index++;
			break;
		}
	}
	return false;
}

bool SCANNER::isOperator(char  c)
{
	for (int i = 0; i < operatorsCount; i++) {
		if (c == operators[i])
			return true;
	}
	return false;
}

void SCANNER::skipWhiteSpaces()
{
	while (this->peekChar = Fd->GetChar()) {
		if (this->peekChar == WHITE_SAPCE_CHAR || this->peekChar == TAB_CHAR) {
			continue;
		}
		else if (this->peekChar == NEW_LINE_CHAR) {
			//next 
			this->lineNumber++;
		}
		else {
			break;
		}
	}
	return;
}

char * SCANNER::readingToken()
{
	this->peekChar = ' ';
	//skip white spaces
	this->skipWhiteSpaces();
	char * tempBuffer = new char[MAX_TOEKN_SIZE];
	for (int i = 0; i < MAX_TOEKN_SIZE; i++)
	{
		tempBuffer[i] = NULL;
	}
	int index = 0;
	do
	{
		tempBuffer[index++] = this->peekChar;
		this->peekChar = Fd->GetChar();
	} while (!isspace(this->peekChar) && index <MAX_TOEKN_SIZE && this->peekChar!='\0');
	return tempBuffer;
}

TOKEN * SCANNER::handleNumbers()
{
	int v = 0;
	if (isNumber(this->peekChar)) 
	{
		do 
		{
			v = v * 10 + convertToInteger(this->peekChar);
			this->peekChar = Fd->GetChar();
		} while (isNumber(this->peekChar));
		//return a number token
		return new INTGER_TOKEN(lx_integer, v);
	}
		return NULL;
}

TOKEN * SCANNER::handleKeyWords()
{
		//collect latters into a phrase
	if (isChar(this->peekChar))
	{
		char * tempBuffer = new char[MAX_TOEKN_SIZE];
		for (int i = 0; i < MAX_TOEKN_SIZE; i++)
		{
			tempBuffer[i] = NULL;
		}
		int index = 0;
		do
		{
			tempBuffer[index++] = this->peekChar;
			this->peekChar = Fd->GetChar();
		} while (isChar(this->peekChar) || isNumber(this->peekChar));
		if (isAKeyword(tempBuffer))
		{
			//this is a reserved word, return its token
			return new KEYWORD_TOKEN(getKeyWordLexemeName(tempBuffer), tempBuffer);
		}
		//this is a new id
		//create a new token for it
		//you must check the syntax of the id
		if (this->isIdentefier(tempBuffer))
			return new STRING_TOKEN(lx_identifier, tempBuffer);
		else
		{
			this->Fd->ReportError("Illegal Identfier");
			return nullptr;
		}
	}
}

TOKEN * SCANNER::handleOperators()
{
	OPERATOR_TOKEN * operatorToken = NULL;
	int state = 0;
	while (this->isOperator(this->peekChar) && this->peekChar!='\0') {
		switch (state) 
		{
		case 0:
			//check the character
			if (this->peekChar == '>')state = 1;
			else if (this->peekChar == '<')state = 2;
			else if (this->peekChar == ':')state = 3;
			else if (this->peekChar == '!')state = 4;
			else if (this->isOperator(this->peekChar))state = 5;
			else return NULL;
			break;
		case 1:
			this->peekChar = Fd->GetChar();
			if (this->peekChar == '=')
			{
				this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_ge, ">=");
			}
			break;
		case 2:
			this->peekChar = Fd->GetChar();
			if (this->peekChar == '=')
			{
				this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_le, "<=");
			}
			break;
		case 3:
			this->peekChar = Fd->GetChar();
			if (this->peekChar == '=')
			{
				this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_colon_eq, ":=");
			}
			break;
		case 4:
			this->peekChar = Fd->GetChar();
			if (this->peekChar == '=')
			{
				this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_neq, "!=");
			}
			break;
		case 5:
			
			return operatorToken = new OPERATOR_TOKEN(this->getOperatorLexemeName(this->peekChar), &this->peekChar);
			break;
		default:
			break;
		}
	}
	return nullptr;
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
LEXEME_TYPE SCANNER::getOperatorLexemeName(char operatorCHar)
{
	int index;
	for (index = 0; index < operatorsCount; index++)
	{
		if (operatorCHar == operators[index])
			return operator_type[index];
	}
}


SCANNER::SCANNER()
{
	lineNumber = 1;
}

TOKEN * SCANNER::Scan()
{
	bool error = false;
	char*token=this->readingToken();
	//cout << "token1 " <<token << endl;
	if (isAKeyword(token)) //if is it a keyword
		return new KEYWORD_TOKEN(this->getKeyWordLexemeName(token), token);
	else if (isIdentefier(token)) //if is it an id
		return new STRING_TOKEN(lx_identifier, token);
	else if (isInteger(token)) //if is it an integer
		return new INTGER_TOKEN(lx_integer, atoi(token));
	else if (isFloat(token)) //if is it a float
		return new FLOAT_TOKEN(lx_float, atof(token));
	else if (isOpertor(token) != NULL)
		return isOpertor(token); //if is it an OP

	if (this->peekChar == WHITE_SAPCE_CHAR || this->peekChar == TAB_CHAR)
	{
		//cout << "token2 " << token << endl;
		token = this->readingToken();
	}

	if (this->peekChar == '\n' || error)
		return NULL;
	/*
	this->peekChar = ' ';
	//skip white spaces
	this->skipWhiteSpaces();	
	//handle keywords OR IDs
	/*TOKEN * keyWordToken = this->handleKeyWords();
	if (keyWordToken != NULL) {
		return keyWordToken;
	}

	//handle Numbers
	TOKEN * numberToken = this->handleNumbers();
	if (numberToken != NULL) {
		return numberToken;
	}

	//handle operators
		TOKEN * operatorToken = this->handleOperators();
		if (operatorToken != NULL)
		{
			return operatorToken;
		}
		return NULL;*/
}



