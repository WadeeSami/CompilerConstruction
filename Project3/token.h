#pragma once

//Token types enumeration
typedef enum
{
	/* Literals */
	lx_identifier, lx_integer, lx_string, lx_float,
	/* Keywords */
	kw_program,
	kw_var, kw_constant, kw_integer, kw_boolean, kw_string, kw_float,
	kw_true, kw_false, kw_if, kw_fi, kw_then, kw_else,
	kw_while, kw_do, kw_od,
	kw_and, kw_or,
	kw_read, kw_write,
	kw_for, kw_from, kw_to, kw_by,
	kw_function, kw_procedure, kw_return, kw_not, kw_begin, kw_end,
	/* Operators */
	lx_Iparen, lx_rparen, lx_lbracket, lx_rbracket,
	Ix_colon, lx_dot, lx_semicolon, lx_comma, Ix_colon_eq,
	lx_plus, lx_minus, lx_star, lx_slash,
	lx_eq, lx_neq, lx_lt, lx_le, lx_gt, lx_ge, lx_eof
}
LEXEME_TYPE;


class TOKEN {
	public:
	LEXEME_TYPE type;
	int value;  // can be used instead of the str_ptr for IDs and strings
	float float_value;

	char *str_ptr;
};

class INTGER_TOKEN : public	TOKEN {
public:
	INTGER_TOKEN(LEXEME_TYPE, int value);
};

class FLOAT_TOKEN : public	TOKEN {
	FLOAT_TOKEN(LEXEME_TYPE, float value);
};


class STRING_TOKEN : public	TOKEN {
	STRING_TOKEN(LEXEME_TYPE, char * value);
};
