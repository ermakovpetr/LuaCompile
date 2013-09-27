

#if !defined(Lua_COCO_PARSER_H__)
#define Lua_COCO_PARSER_H__



#include "Scanner.h"

namespace Lua {


class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_Name=1,
		_Int=2,
		_Float=3,
		_Expnum=4,
		_Hex=5,
		_Normalstring=6,
		_Longstring=7,
		_Eql=8,
		_Comma=9,
		_Point=10,
		_Colon=11,
		_Semicolon=12,
		_Slb=13,
		_Srb=14,
		_Rlb=15,
		_Rrb=16,
		_Flb=17,
		_Frb=18
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

bool IsNameAndEql()
{
    scanner->ResetPeek();
    Token* next = scanner->Peek();
    return la->kind == _Name && next->kind == _Eql;
}

/* return true, if lookahead token is _Comma and next token is _Name */
bool IsCommaAndName()
{
    scanner->ResetPeek();
    Token* next = scanner->Peek();
    return la->kind == _Comma && next->kind == _Name;
}

/* resolve LL(1) conflict in "stat" production */
bool IsCommaOrEql()
{
    scanner->ResetPeek();
    Token* next = scanner->Peek();
    if (next->kind == _Slb)
    {
        int i = 0;
        while (next->kind != _EOF)
        {
            if (next->kind == _Slb) i++;
            else if (next->kind == _Srb) i--;
            if (i == 0) break;
            next = scanner->Peek();
        }
        next = scanner->Peek();
        return next->kind == _Comma || next->kind == _Eql || next->kind == _Slb;
    }
    if (next->kind == _Point)
    {
        next = scanner->Peek();
        if (next->kind == _Name)
        {
            next = scanner->Peek();
            return next->kind == _Comma || next->kind == _Eql;
        }
        return false;
    }
    return next->kind == _Comma || next->kind == _Eql;
}



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void Lua(int i);
	void Chunk(int i);
	void Stat(int i);
	void Laststat(int i);
	void Block(int i);
	void Varlist(int i);
	void Explist(int i);
	void Functioncall(int i);
	void Exp(int i);
	void Funcname(int i);
	void Funcbody(int i);
	void Namelist(int i);
	void Var(int i);
	void Exp1(int i);
	void Binop(int i);
	void Exp2(int i);
	void Unop(int i);
	void Number(int i);
	void String(int i);
	void Function(int i);
	void Prefixexp(int i);
	void Tableconstructor(int i);
	void Prefixexp2(int i);
	void Args(int i);
	void Prefixexp1(int i);
	void Parlist(int i);
	void Parlist1(int i);
	void Fieldlist(int i);
	void Field(int i);
	void Fieldsep(int i);

	void Parse();

}; // end Parser

} // namespace


#endif

