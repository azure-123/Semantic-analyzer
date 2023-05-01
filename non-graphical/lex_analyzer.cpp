#include<iostream>
#include<string>
#include<vector>
////////////////token marking///////////////////////
#define $int	1
#define $void	2
#define $if		3
#define $else	4
#define $while	5
#define $return 6
#define $ID		7
#define $ASSIGN 8
#define $PLUS	9
#define $MINUS	10
#define $MULT	11
#define $DIV	12
#define $EQUAL	13
#define $GREATER 14
#define $GREATER_EQ 15
#define $LOWER	16
#define $LOWER_EQ 17
#define $UNEQUAL 18
#define $BOUND	19
#define $COMMA	20
#define $LEFT_COMM 21
#define $RIGHT_COMM 22
#define $LINE_COMM 23
#define $LPAR	24
#define $RPAR	25
#define $LBRACE 26
#define $RBARCE 27
#define $VALUE	28
//////////////////////////////////
using namespace std;
vector<string> id_table;
vector<string> result;
vector<string> lex_string;
vector<string> lex_string_1;

bool IsLetter(char ch)
{
	if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		return true;
	else
		return false;
}

bool IsDigit(char ch)
{
	if (ch >= '0'&&ch <= '9')
		return true;
	else
		return false;
}

vector<string> scanner(string str)
{
	

	int i = 0;
	string strToken = "";
	while (i < str.length())
	{
		if (IsLetter(str[i]))
		{
			while (IsLetter(str[i]) || IsDigit(str[i]))
			{
				strToken.push_back(str[i]);
				i++;
			}
			if ("int" == strToken)
			{
				result.push_back("<$int,->\n");
				lex_string.push_back("int");
			}
			else if ("void" == strToken)
			{
				result.push_back("<$void,->\n");
				lex_string.push_back("void");
			}
			else if ("if" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$if,->" << endl;
				result.push_back("<$if,->\n");
				lex_string.push_back("if");
			}
			else if ("else" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$else,->" << endl;
				result.push_back("<$else,->\n");
				lex_string.push_back("else");
			}
			else if ("while" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$while,->" << endl;
				result.push_back("<$while,->\n");
				lex_string.push_back("while");
			}
			else if ("return" == strToken)
			{
				result.push_back("<$return,->\n");
				lex_string.push_back("return");
			}
			else
			{
				int index = 0;
				for (int i = 0; i < id_table.size(); i++)
				{
					if (strToken == id_table[i])
					{
						index = i + 1;
					}
				}
				if (index == 0)
				{
					id_table.push_back(strToken);
					index = id_table.size();
				}
				result.push_back("<$ID," + to_string(index) + ">\n");
				lex_string.push_back(strToken);
				i--;
			}
			strToken = "";
			if (str[i] == ';' || str[i] == ')' || str[i] == '(')
			{
				strToken.push_back(str[i]);
				result.push_back(strToken);
				lex_string.push_back(strToken);
			}
			strToken = "";
			i++;
		}
		else if (IsDigit(str[i]))
		{
			while (IsDigit(str[i]))
			{
				strToken.push_back(str[i]);
				i++;
			}
			result.push_back("<$VALUE," + strToken + ">\n");
			lex_string.push_back(strToken);
			strToken = "";
			//i++;
		}
		else if ('=' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i++;
				strToken = "==";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$EQUAL,->" << endl;
				result.push_back("<$EQUAL,->\n");
				lex_string.push_back("==");
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$ASSIGN,->" << endl;
				result.push_back("<$ASSIGN,->\n");
				lex_string.push_back("=");
				i++;
			}
		}
		else if ('+' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$PLUS,->" << endl;
			result.push_back("<$PLUS,->\n");
			lex_string.push_back("+");
			i++;
		}
		else if ('-' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$MINUS,->" << endl;
			result.push_back("<$MINUS,->\n");
			lex_string.push_back("-");
			i++;
		}
		else if ('*' == str[i])
		{
			if ('/' == str[i + 1])
			{
				i++;
				strToken = "*/";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$RIGHT_COMM,->" << endl;
				result.push_back("<$RIGHT_COMM,->\n");
				lex_string.push_back("*/");
			}
			else
			{
				//cout << "<$MULT,->" << endl;
				result.push_back("<$MULT,->\n");
				lex_string.push_back("*");
				i++;
			}
		}
		else if ('/' == str[i])
		{
			if ('*' == str[i + 1])
			{
				i++;
				strToken = "/*";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$LEFT_COMM,->" << endl;
				result.push_back("<$LEFT_COMM,->\n");
				lex_string.push_back("/*");
			}
			else if ('/' == str[i + 1])
			{
				i++;
				strToken = "//";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$LEFT_COMM,->" << endl;
				result.push_back("<$LINE_COMMENT,->\n");
				lex_string.push_back("//");
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$DIV,->" << endl;
				result.push_back("<$DIV,->\n");
				lex_string.push_back("/");
				i++;
			}
		}
		else if ('>' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i += 2;
				strToken = ">=";
				result.push_back("<$GREATER_OR_EQUAL,->\n");
				lex_string.push_back(">=");
				strToken = "";
			}
			else
			{
				result.push_back("<$GREATER,->\n");
				lex_string.push_back(">");
				i++;
			}
		}
		else if ('<' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i += 2;
				strToken = "<=";
				result.push_back("<$LOWER_OR_EQUAL,->\n");
				lex_string.push_back("<=");
				strToken = "";
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$LOWER,->" << endl;
				result.push_back("<$LOWER,->\n");
				lex_string.push_back("<");
				i++;
			}
		}
		else if ('!' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i += 2;
				strToken = "!=";
				//cout << strToken<<endl;
				//cout << "<$UNEQUAL,->" << endl;
				result.push_back("<$UNEQUAL,->\n");
				lex_string.push_back("!=");
				strToken = "";
			}
		}
		else if ('(' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$LPAR,->" << endl;
			result.push_back("<$LPAR,->\n");
			lex_string.push_back("(");
			i++;
		}
		else if (')' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$RPAR,->" << endl;
			result.push_back("<$RPAR,->\n");
			lex_string.push_back(")");
			i++;
		}
		else if ('{' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$LBRACE,->" << endl;
			result.push_back("<$LBRACE,->\n");
			lex_string.push_back("{");
			i++;
		}
		else if ('}' == str[i])
		{
			result.push_back("<$RBRACE,->\n");
			lex_string.push_back("}");
			i++;
		}
		else if (';' == str[i])
		{
			result.push_back("<$BOUND,->\n");
			lex_string.push_back(";");
			i++;
		}
		else if (',' == str[i])
		{
			result.push_back("<$COMMA,->\n");
			lex_string.push_back(",");
			i++;
		}
		else if (' ' == str[i])
		{
			while (str[i] == ' ')
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	lex_string.push_back("\n");
	return lex_string;
}

vector<string> scanner_1(string str)
{
	int i = 0;
	string strToken = "";
	while (i < str.length())
	{
		if (IsLetter(str[i]))
		{
			while (IsLetter(str[i]) || IsDigit(str[i]))
			{
				strToken.push_back(str[i]);
				i++;
			}
			if ("int" == strToken)
			{
				result.push_back("<$int,->\n");
				lex_string_1.push_back("int");
			}
			else if ("void" == strToken)
			{
				result.push_back("<$void,->\n");
				lex_string_1.push_back("void");
			}
			else if ("if" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$if,->" << endl;
				result.push_back("<$if,->\n");
				lex_string_1.push_back("if");
			}
			else if ("else" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$else,->" << endl;
				result.push_back("<$else,->\n");
				lex_string_1.push_back("else");
			}
			else if ("while" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$while,->" << endl;
				result.push_back("<$while,->\n");
				lex_string_1.push_back("while");
			}
			else if ("return" == strToken)
			{
				result.push_back("<$return,->\n");
				lex_string_1.push_back("return");
			}
			else
			{
				int index = 0;
				for (int i = 0; i < id_table.size(); i++)
				{
					if (strToken == id_table[i])
					{
						index = i + 1;
					}
				}
				if (index == 0)
				{
					id_table.push_back(strToken);
					index = id_table.size();
				}
				result.push_back("<$ID," + to_string(index) + ">\n");
				lex_string_1.push_back("$ID");
				i--;
			}
			strToken = "";
			if (str[i] == ';' || str[i] == ')' || str[i] == '(')
			{
				strToken.push_back(str[i]);
				result.push_back(strToken);
				lex_string_1.push_back(strToken);
			}
			strToken = "";
			i++;
		}
		else if (IsDigit(str[i]))
		{
			while (IsDigit(str[i]))
			{
				strToken.push_back(str[i]);
				i++;
			}
			result.push_back("<$VALUE," + strToken + ">\n");
			lex_string_1.push_back("$NUM");
			strToken = "";
			//i++;
		}
		else if ('=' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i++;
				strToken = "==";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$EQUAL,->" << endl;
				result.push_back("<$EQUAL,->\n");
				lex_string_1.push_back("==");
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$ASSIGN,->" << endl;
				result.push_back("<$ASSIGN,->\n");
				lex_string_1.push_back("=");
				i++;
			}
		}
		else if ('+' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$PLUS,->" << endl;
			result.push_back("<$PLUS,->\n");
			lex_string_1.push_back("+");
			i++;
		}
		else if ('-' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$MINUS,->" << endl;
			result.push_back("<$MINUS,->\n");
			lex_string_1.push_back("-");
			i++;
		}
		else if ('*' == str[i])
		{
			if ('/' == str[i + 1])
			{
				i++;
				strToken = "*/";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$RIGHT_COMM,->" << endl;
				result.push_back("<$RIGHT_COMM,->\n");
				lex_string_1.push_back("*/");
			}
			else
			{
				//cout << "<$MULT,->" << endl;
				result.push_back("<$MULT,->\n");
				lex_string_1.push_back("*");
				i++;
			}
		}
		else if ('/' == str[i])
		{
			if ('*' == str[i + 1])
			{
				i++;
				strToken = "/*";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$LEFT_COMM,->" << endl;
				result.push_back("<$LEFT_COMM,->\n");
				lex_string_1.push_back("/*");
			}
			else if ('/' == str[i + 1])
			{
				i++;
				strToken = "//";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$LEFT_COMM,->" << endl;
				result.push_back("<$LINE_COMMENT,->\n");
				lex_string_1.push_back("//");
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$DIV,->" << endl;
				result.push_back("<$DIV,->\n");
				lex_string_1.push_back("/");
				i++;
			}
		}
		else if ('>' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i += 2;
				strToken = ">=";
				result.push_back("<$GREATER_OR_EQUAL,->\n");
				lex_string_1.push_back(">=");
				strToken = "";
			}
			else
			{
				result.push_back("<$GREATER,->\n");
				lex_string_1.push_back(">");
				i++;
			}
		}
		else if ('<' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i += 2;
				strToken = "<=";
				result.push_back("<$LOWER_OR_EQUAL,->\n");
				lex_string_1.push_back("<=");
				strToken = "";
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$LOWER,->" << endl;
				result.push_back("<$LOWER,->\n");
				lex_string_1.push_back("<");
				i++;
			}
		}
		else if ('!' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i += 2;
				strToken = "!=";
				//cout << strToken<<endl;
				//cout << "<$UNEQUAL,->" << endl;
				result.push_back("<$UNEQUAL,->\n");
				lex_string_1.push_back("!=");
				strToken = "";
			}
		}
		else if ('(' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$LPAR,->" << endl;
			result.push_back("<$LPAR,->\n");
			lex_string_1.push_back("(");
			i++;
		}
		else if (')' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$RPAR,->" << endl;
			result.push_back("<$RPAR,->\n");
			lex_string_1.push_back(")");
			i++;
		}
		else if ('{' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$LBRACE,->" << endl;
			result.push_back("<$LBRACE,->\n");
			lex_string_1.push_back("{");
			i++;
		}
		else if ('}' == str[i])
		{
			result.push_back("<$RBRACE,->\n");
			lex_string_1.push_back("}");
			i++;
		}
		else if (';' == str[i])
		{
			result.push_back("<$BOUND,->\n");
			lex_string_1.push_back(";");
			i++;
		}
		else if (',' == str[i])
		{
			result.push_back("<$COMMA,->\n");
			lex_string_1.push_back(",");
			i++;
		}
		else if (' ' == str[i])
		{
			while (str[i] == ' ')
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	return lex_string_1;
}

