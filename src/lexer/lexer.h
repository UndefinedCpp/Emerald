/*  Emerald Scriptting Language, UndefinedCpp
    Copyright (C) 2021-2026  UndefinedCpp

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <string>

#ifndef EMERALD_LEXER_LEXER_H
#define EMERALD_LEXER_LEXER_H

#define SOURCE_MAX 1024

namespace LexerMsp
{
	using namespace std;
	enum TokenType
	{
		EMPTY = 0,		// like NULL or whatever 
		KEYWORD,
		IDENTIFIER,
		NUMBER,
		STRING,
		OPERATOR,
		TYPE,			// user defined type
		SEPERATOR
	};
	
	typedef struct _TagToken
	{
		TokenType type;
		string value;
		int errcode;
		int line; 
	} Token;
	
	class Lexer
	{
	public:
		Lexer(string buffer);
		~Lexer();
		Token read();
		bool isKeyword(const char * tk); 
		unsigned int lineNumber;
	private:
		char readChar();
		void ungetChar(char c);
		Token processDoubleOperator(char op);
		
		char *buf;	// store the code
		unsigned int index;		// a pointer to buffer
	};
}



#endif
