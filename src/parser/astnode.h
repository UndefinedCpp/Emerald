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

#ifndef EMERALD_PARSER_ASTNODE_H
#define EMERALD_PARSER_ASTNODE_H

namespace ParserMsp
{
	using namespace std;
	/*
	 * AstNode: 抽象语法树(AST)的节点，是一个抽象类 
	*/
	class AstNode
	{
	public:
		AstNode() { }
		virtual ~AstNode() { }
	public:
		// 获取子节点个数，纯虚函数 
		virtual int getChildrenNumber() = 0;
		// 获取这个节点的源码位置 
		virtual string getLocation() = 0;
		// 查询第index个节点，和数组一样用[] 
		virtual AstNode operator[] (int index) = 0;
	}

}

#endif 
