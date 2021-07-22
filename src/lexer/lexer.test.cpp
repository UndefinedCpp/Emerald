#include <iostream>
#include <string>
#include <cstring>
#include "lexer.h"

using namespace std;
LexerMsp::Lexer* lex;
int main()
{
	char input[256];
	LexerMsp::Token tk;
	memset(input, 0, sizeof(input));
	int cnt = 0;
	// QueryPerformanceFrequency(&tc);


	while(true)
	{
		cnt = 0;
		cout << "> ";
		cin.getline(input, 256);
		
		lex = new LexerMsp::Lexer(input);
		while(true)
		{
			// QueryPerformanceCounter(&t1);
			tk = lex->read();
			// QueryPerformanceCounter(&t2);
			// cout << "TimeConsume:" << ((t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart); 
			
			if(tk.errcode != 0xff)
			{
				cout << "[error]" << tk.value << endl;
				break;
			}
			else if(tk.type == LexerMsp::EMPTY && tk.errcode == 0xff)
			{
				cout << "(DONE)" << endl;
				break;
			}
			else
			{
				cout << "(" << tk.type << ": " << tk.value << ") ";
				if(++cnt % 10 == 0)
					cout << endl;
			}
		}
		delete lex;
	}
}
