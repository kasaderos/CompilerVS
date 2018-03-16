#ifndef __SYNTAX_H__
#define __SYNTAX_H__
#include "lexical.h"
#include <vector>

template <class T, int max_size > class Stack
{
	T *s;
	int size;
	int top;
public:
	Stack();
	~Stack();
	void reset();
	void push(T i);
	T pop();
	T get_top();
	bool is_empty();
	bool is_full();
	void print();
};


class Poliz {
	Lex *p;
	int pos;
	int size;
public:
	Poliz(int max_size);
	~Poliz();
	void put_lex(Lex l);
	void put_lex(Lex l, int place);
	void blank();
	int get_pos();
	Lex & operator[] (int index);
	void print();
};

class Parser {
	Lex curr_l;
	Lex tmp;
	type_lex curr_t;
	type_lex type;
	double curr_v;
	Scanner scan;
	Stack < int, 100 > st_int;
	Stack < Lex, 100 > st_lex;
	void Prog();
	void Dcls();
	void Del();
	void Block();
	void Stmts();
	void Stmt();
	void Expr();
	void Expr1();
	void T();
	void F();

	void dec();
	void check_id();
	void check_op();
	void eq_type();
public:
	Poliz prog;
	Parser(const char * program);
	void analyze();
	void gl();
	void gln();
};

class Executer {
	Lex curr_l;
public:
	void execute(Poliz & prog);
};

class Interpretator {
	Parser pars;
	Executer E;
public:
	Interpretator(const char * program) : pars(program) {};
	void interpretation();
};
#endif

