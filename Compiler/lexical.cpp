﻿#include <string>
#include "lexical.h"
using namespace std;

extern Table_ident TID;

Ident::Ident() : val(""), declare(false), assign(false) {}

Ident::Ident(const string str) : name(str), val(""), declare(false), assign(false) {}

Lex::Lex() {
	t_lex = LEX_NULL;
	v_lex = "_";
}
Lex::Lex(type_lex t, string v) {
	t_lex = t;
	v_lex = v;
}

Lex::Lex(int i) {
	t_lex = LEX_INUM;
	v_lex = to_string(i);
}

Lex::Lex(double f) {
	t_lex = LEX_FNUM;
	v_lex = to_string(f);
}

Lex convert(const Lex & a) {
	if (a.t_lex == LEX_ID) {
		int i = atoi(a.v_lex.c_str());
		//cout << "convert : ";
		//cout << Scanner::LEXS[TID.var[i].type] << endl;
		if (TID.var[i].type == LEX_INT)
			return Lex(LEX_INUM, TID.var[i].val);
		if (TID.var[i].type == LEX_FLOAT)
			return Lex(LEX_FNUM, TID.var[i].val);
		else
			throw "error convert lex";
	}
	return a;
}

Lex operator + (const Lex & a, const Lex & b) {
	Lex lex1 = convert(a);
	Lex lex2 = convert(b);
	//cout << Scanner::LEXS[lex1.t_lex] << endl;
	//cout << Scanner::LEXS[lex2.t_lex] << endl;
	if (lex1.t_lex == LEX_FNUM || lex2.t_lex == LEX_FNUM)
		return atof(lex1.v_lex.c_str()) + atof(lex2.v_lex.c_str());
	return atoi(lex1.v_lex.c_str()) + atoi(lex2.v_lex.c_str());
}

Lex operator - (const Lex & a, const Lex & b) {
	Lex lex1 = convert(a);
	Lex lex2 = convert(b);
	if (lex1.t_lex == LEX_FNUM || lex2.t_lex == LEX_FNUM)
		return atof(lex1.v_lex.c_str()) - atof(lex2.v_lex.c_str());
	return atoi(lex1.v_lex.c_str()) - atoi(lex2.v_lex.c_str());
}
/*
Lex Lex::operator * (const Lex & a, const Lex & b){

}
Lex Lex::operator / (const Lex & a, const Lex & b){

}*/
ostream & operator << (ostream & s, Lex lx) {
	s << '(' << Scanner::LEXS[lx.t_lex] << ',' << lx.v_lex << ')';
	return s;
}



Scanner::Scanner(const char *filename)
{
	fp.open(filename);
	ST = H;
	gc();
}

Scanner::~Scanner()
{
	fp.close();
}

void Scanner::gc() {
	fp.get(c);
}

int Scanner::lookTW() {
	int i = 1;
	while (!TW[i].empty()) {
		if (!buf.compare(TW[i]))
			return i;
		++i;
	}
	return 0;
}

int Scanner::lookTD() {
	int i = 1;
	while (!TD[i].empty()) {
		if (!buf.compare(TD[i]))
			return i;
		++i;
	}
	return 0;
}

int Table_ident::put(Ident id) {
	for (size_t i = 0; i < TID.var.size(); i++)
		if (!id.name.compare(TID.var[i].name))
			return i;
	TID.var.push_back(id);
	return TID.var.size() - 1;
}

Lex Scanner::get_lex()
{
	int j, f = 0;
	ST = H;
	buf.clear();
	do {
		switch (ST) {
		case H:
			if (c == ' ' || c == '\t' || c == '\r') {
				gc();
				continue;
			}
			else if (isalpha(c))
				ST = IDENT;
			else if (isdigit(c))
				ST = NUM;
			else
				ST = DELIM;
			break;
		case IDENT:
			if (isalpha(c) || isdigit(c)) {
				buf.push_back(c);
				gc();
			}
			else {
				if ((j = lookTW()) != 0) {
					return Lex(tw[j], to_string(j));
				}
				else {
					Ident id(buf);
					j = TID.put(id);
					return Lex(LEX_ID, to_string(j));
				}
			}
			break;
		case NUM:
			if (isdigit(c)) {
				buf.push_back(c);
				gc();
			}
			else if (c == '.') {
				f = 1;
				buf.push_back(c);
				gc();
			}
			else if (f)
				return Lex(LEX_FNUM, buf);
			else
				return Lex(LEX_INUM, buf);
			break;
		case DELIM:
			buf.push_back(c);
			if ((j = lookTD()) != 0) {
				gc();
				return Lex(td[j], to_string(j));
			}
			else
				throw c;
			break;
		}
	} while (1);
	return Lex(LEX_NULL, "");
}

void Table_ident::print() {
	cout << endl;
	for (int i = 0; i < TID.var.size(); i++)
		cout << TID.var[i].name << " : " << TID.var[i].val << endl;
}

