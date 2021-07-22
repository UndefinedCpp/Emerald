//  Emerald Language, UndefinedCpp
//    Copyright (C) 2021-2026  UndefinedCpp
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <string>
#include <cstring>
#include "lexer.h" 

#ifndef EMERALD_LEXER_LEXER_CPP
#define EMERALD_LEXER_LEXER_CPP

// 这样的话可以轻松拼接string和char 
std::string operator+ (std::string s, char c)
{
	std::string temp = " ";
	temp[0] = c;
	return s + temp;
}

namespace LexerMsp
{
	using namespace std;
	// 初始化词法分析器 
	Lexer::Lexer(string buffer)
	{
		buf = new char[SOURCE_MAX];
		strcpy(buf, buffer.c_str());
		lineNumber = 1;
		index = 0;
	}
	Lexer::~Lexer()
	{
		delete[] buf;
	}
	// 读取token 
	Token Lexer::read()
	{
		Token token;
		char ch;
		
		// 重要，以免误判 
		token.errcode = 0xff; 
		
		while(true)
		{
			ch = readChar();	// 读出一个字符
			if(ch == 0 || ch == EOF)
			{
				token.type = EMPTY;
				token.value = string("<end>");
				token.errcode = 0xff; 
				token.line = lineNumber;
				return token;
			} 
			if(ch == '\n')	// 换行符 
			{
				this->lineNumber++;
			}
			if(!isspace(ch))	// 不是空格，退出循环 
			{
				break;
			}
		}
		
		token.value = token.value + ch;
		
		if(isalpha(ch) || ch == '_')	// 如果是字母 
		{
			// 读取字符，是字母或数字或下划线 
			while(ch = readChar(), isalnum(ch) || ch == '_')
			{
				token.value = token.value + ch;
			}
			ungetChar(ch);
			// 采用逻辑短路来做一个小小的优化 
			if((ch != '_' && ('0' <= ch && ch <= '9')) && isKeyword(token.value.c_str()))
			{
				// 是关键字 
				token.type = KEYWORD;
				token.line = lineNumber;
				return token;
			}
			else
			{
				// 是标识符 
				token.type = IDENTIFIER;
				token.line = lineNumber;
				return token;
			}
		}
		else if(isdigit(ch))
		{
			bool hasDot = false;	// 判断是否有小数点 
			while(true)
			{
				ch = readChar();
				
				if(hasDot && ch == '.')
				{
					// 第二个小数点了
					token.type = NUMBER;
					token.line = lineNumber;
					// 出错 
					token.errcode = 1;
					return token; 
				}
				
				if(ch == '.' && !hasDot)
				{
					token.value = token.value + ch;
					hasDot = true;
					continue;	// 避免走下面的那个if 
				}
				
				if(isdigit(ch) || ch == '.')
				{
					token.value = token.value + ch;
				}
				else
				{
					break;
				}
			}
			ungetChar(ch);
			token.type = NUMBER;
			return token;
		}
		else
		{
			switch(ch)
			{
			case ';':
			case '(':
			case ')':
			case ',':
			case '{':
			case '}':
			case '[':
			case ']':
			case ':':
			case '.':
				// 分隔符 
				token.type = SEPERATOR;
				token.value = string("") + ch;
				token.line = lineNumber;
				return token;
			case '+': 
			case '-': 
			case '=':
			case '*':
			case '%':
			case '>':
			case '<': 
				// 处理类似+=, -=, *=, /=等的 
				if(readChar() == '=')
				{
					token.value = string("") + ch + '=';
				}
				ungetChar(ch);
				// 处理类似于++, --, **
				if(readChar() == ch)
				{
					token.value = string("") + ch + ch;
				}
				else
				{
					ungetChar(ch);
				}
				token.type = OPERATOR;
				token.line = lineNumber;
				return token;
			case '\"': {	// 字符串！是不是有点棘手
				string result = "\"";
				while(true)
				{
					ch = readChar();
					if(ch == '\\')	// 遇到转义字符
					{
						ch = readChar();
						switch(ch)
						{
						case '\\':
							result = result + '\\';
							break;
						case 'n':
							result = result + '\n';
							break;
						case 'r':
							result = result + '\r';
							break;
						case '\'':
							result = result + '\'';
							break;
						case '\"':
							result = result + '\"';
							break;
						default:
							result = result + ch;
							token.type = STRING;
							token.value = result;
							token.line = lineNumber;
							token.errcode = -4;
							return token;
						}
					}
					else
					{
						result = result + ch;
					}
				}
			}
			case '\'':	// 字符，注意是宽字符 
				string result = "\'";
				ch = readChar();
				
				break;
			case '/': {
				if(readChar() == '/')
				{
					while(!isspace(readChar()))
					{
					}
					ungetChar(0);
					token.value = "<comment>";
					token.line = lineNumber;
					return token;
				}
				else
				{
					token.value = "/";
					ungetChar(ch);
					token.type = OPERATOR;
					token.line = lineNumber;
					return token;
				}
				// ungetChar(ch);
				
			}
				
			default:
				token.type = EMPTY;
				token.value = string("") + ch;
				token.errcode = 2;
				token.line = lineNumber;
				return token;
			}
		}
		token.type = EMPTY;
		token.value = "<why reaching here?>";
		token.errcode = -1;
		token.line = lineNumber;
		return token;
	}
	// 是否是关键字
	bool Lexer::isKeyword(const char *tk)
	{
		static const char * keywords[] = {
			// 数据类型 
			"int", "int64", "byte", "uint", "uint64", "int8", "int16", "uint16",
			"float", "double", /* 宽字符 */"char", "const"
			// 控制流程 
			"while", "for", "if", "elseif", "else", "switch", "case", "default",
			"repeat", "until", "break", "return", "static",
			// 布尔逻辑
			"and", "not", "or", "true", "false",
			// 面向对象
			"class", "public", "private", "protected", "extends", "this",
			"super", "null", "typeof", "static", "new"
			// 异常
			"throw", "try", "catch", "ensure",
			// 模块
			"module", "export", "import" 
		};
		for(int i = 0; i < sizeof(keywords) / sizeof(const char*); ++i)
		{
			if(strcmp(tk, keywords[i]) == 0)
			{
				return true;
			}
		}
		return false;
	} 
	// 处理诸如++，--，==等操作符
	// 只能和read()联合使用 
	Token Lexer::processDoubleOperator(char op)
	{
		Token token;
		if(readChar() == op)
		{
			token.value = string("") + op + op;
		}
		else
		{
			token.value = string("") + op;
			ungetChar(op);
		}
		token.type = OPERATOR;
		token.line = lineNumber;
		return token;
	} 
	// 读取下一个字符 
	char Lexer::readChar()
	{
		char c = buf[index++];
		return c;
	}
	// 字符回溯 
	void Lexer::ungetChar(char c)
	{
		if(c != EOF)
			--index;
	}
}

#endif
