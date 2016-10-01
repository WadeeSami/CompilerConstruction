#include "token.h"

INTGER_TOKEN::INTGER_TOKEN(LEXEME_TYPE type, int value)
{
	this->value = value;
	this->type = type;
}

FLOAT_TOKEN::FLOAT_TOKEN(LEXEME_TYPE, float value)
{
	this->float_value = value;
	this->type = type;
}

STRING_TOKEN::STRING_TOKEN(LEXEME_TYPE, char * value)
{
	this->str_ptr = value;
	this->type = type;
}
