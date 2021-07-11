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
#include <vector>
#include <stdexcept>
#include "astnode.h"
#include "../lexer/lexer.h"

#ifndef EMERALD_PARSER_ASTLEAF_H
#define EMERALD_PARSER_ASTLEAF_H

namespace ParserMsp
{
	using namespace std;
	using namespace LexerMsp;
	
	class AstLeaf: public AstNode
	{
	public:
		AstLeaf(Token t) : token(t) { }
		virtual ~AstLeaf() { }
		int getChildrenNumber()
		 { return 0; }
		AstNode operator[] (int index) 
		{
			throw range_error("in ParserMsp::AstLeaf::operator[](int)");
		}
		string getLocation()
		{
			char buf[32];
			sprintf(buf, "at line %d", token.line);
			return string(buf);
		}
		Token getToken()
		{
			return token;
		}
	protected:
		Token token;
	private:
		static vector<AstNode> empty;
	}
	
	// AstLeaf::empty的义务性定义 
	vector<AstNode> AstLeaf::empty = vector();
}

#endif
