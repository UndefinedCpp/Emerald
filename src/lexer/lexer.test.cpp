#include <iostream>
#include <string>
#include <cstring>
#include "lexer.h"
using namespace std;
LexerMsp::Lexer* lex;
int main()
{
	char input[128];
	LexerMsp::Token tk;
	memset(input, 0, sizeof(input));
	
	cout << "Type\t\tValue\t\tErrorCode" << endl;
	
	while(true)
	{
		cout << "> ";
		cin.getline(input, 128);
		
		lex = new LexerMsp::Lexer(input);
		while(true)
		{
			tk = lex->read();
			if(tk.type == LexerMsp::EMPTY)
			{
				cout << "* error: " << tk.value << endl;
				break;
			}
			else
			{
				cout << tk.type << "\t\t" << tk.value << "\t\t" << tk.errcode << endl;
			}
		}
		delete lex;
	}
}
