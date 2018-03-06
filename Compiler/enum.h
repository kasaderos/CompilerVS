#ifndef __ENUM_H___
#define __ENUM_H___

enum type_lex {
	LEX_NULL,
	LEX_ASSIGN,
	LEX_INT,
	LEX_FLOAT,
	LEX_STR,
	LEX_CHAR,
	LEX_FNUM,
	LEX_INUM,
	LEX_ID,
	LEX_INPUT,
	LEX_PRINT,
	LEX_PLUS,
	LEX_MINUS,
	LEX_MUL,
	LEX_DIV,
	LEX_LPAREN, // )
	LEX_RPAREN, // )
	LEX_LSQR, // [
	LEX_RSQR, // ]
	LEX_IF,
	LEX_ELSE,
	LEX_WHILE,
	LEX_COLON,
	LEX_NLINE,
	LEX_AND,
	LEX_OR,
	LEX_NOT,
	LEX_SEQ, // ==
	LEX_SNQ, // !=
	LEX_SG, // >
	LEX_SL, // <
	LEX_SGE, // >=
	LEX_SLE, // <=
	LEX_FIN,
	POLIZ_GO,
	POLIZ_FGO,
	POLIZ_LABEL,
	POLIZ_ADDRESS,
};

#endif // !__ENUM_H___