//  Emerald Language, UndefinedCpp
//    Copyright (C) 2021-2026  UndefinedCpp
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <string>

#ifndef EMERALD_PARSER_PTYPES_H
#define EMERALD_PARSER_PTYPES_H

namespace ParserMsp
{
	using namespace std
	
	/*
	 * ParseCell就是分析单元，记录语法分析状态
	*/
	struct ParseCell
	{
		char op;		// 表示操作类型
		char oprand;	// 表示操作数
	};
	
	/*
	 * Collection是FIRST和FOLLOW用的
	*/
	struct Collection
	{
		int *vts;
		int top;
		
		Collection()
		{
			top = 0;
			vts = new int[128];
		}
		~Collection()
		{
			delete[] vts;
		}
	};
	
	struct Item
	{
		int pid;	// 产生式下标
		int idx;	// 上一个的下标		
	};
	
	struct Production
	{
		string leftPart;
		string rightPart;
		int rightLength;
	};
	
	struct MState
	{
		Item *its;
		int top;
		MState()
		{
			its = new Item[128];
			top = 0;
		}
		~MState()
		{
			delete[] its;
		}
	}
}

#endif
