#pragma once
typedef enum {
	type_integer,
	type_string,
	type_boolean,
	type_float,
	type_none
} j_type;

static char *type_names[] = { "integer", "string", "boolean", "float", "none" };

typedef enum {
	ste_var, // a variable
	ste_const, //A constant
	ste_routine, //A routine
	ste_undefined, // ste_entry
} ste_entry_type;

struct SymbolTableEntry {
	char *name;
	SymbolTableEntry *next;
	ste_entry_type entry_type;
	// User-modifiable fields go here:
	union {
		// l .for a variable record its type
		struct {
			j_type type;
		} var;
		// for a constant record its value
		struct {
			int value;
		} constant;
		/* for a routine, record formal parameters and result type */
		struct {
			// SteListCelll *formals;// will be defined later
			j_type result_type;
		} routine;
	} f;
};