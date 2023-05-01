#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include"syntactic_analyzer.h"

using namespace std;
enum non_termin
{
	Program, SubProgram, TempProgram, Declaration, Type,
	TempBound, Function, Parameter, TempInt, RightEnd_1,
	IntParameter, Block, NumDeclaration, IntParameter_1, TempSentence,
	TempSentence_1, TempReturn, TempSentence_3, ReturnSentence, ReturnValue,
	WhileSentence, IfSentence, TempSentence_2, Expression, Relop,
	TempExpression, Token, TempSentence_4, Token_1, Token_2,
	Token_3, Call, TempSentence_5, TempExpression_1, RightEnd,
	Extra_1, TempLeftParenthesis, ParameterNum, SentenceEnd, TempFunction,
	Extra_2, JumpElse, Extra_3, Extra_4, Extra_5,
	Extra_6, Extra_7, Extra_8, Extra_9, Extra_10,
	Extra_11, Extra_12
};
string non_termin_string[NON_TERM_NUM] =
{
	"Program", "SubProgram", "TempProgram", "Declaration", "Type",
	"TempBound", "Function", "Parameter", "TempInt", "RightEnd_1",
	"IntParameter", "Block", "NumDeclaration", "IntParameter_1", "TempSentence",
	"TempSentence_1", "TempReturn", "TempSentence_3", "ReturnSentence", "ReturnValue",
	"WhileSentence", "IfSentence", "TempSentence_2", "Expression", "Relop",
	"TempExpression", "Token", "TempSentence_4", "Token_1", "Token_2",
	"Token_3", "Call", "TempSentence_5", "TempExpression_1", "RightEnd",
	"Extra_1", "TempLeftParenthesis", "ParameterNum", "SentenceEnd", "TempFunction",
	"Extra_2", "JumpElse", "Extra_3", "Extra_4", "Extra_5",
	"Extra_6", "Extra_7", "Extra_8", "Extra_9", "Extra_10",
	"Extra_11", "Extra_12"
};
//终结符，用枚举量表示
enum termin
{
	_int, _void, _else, _if, _while,
	_return, _ID, _NUM, _assign, _plus,
	_minus, _multiply, _divide, _lower, _lower_equal,
	_larger, _larger_equal, _equal, _unequal,
	_bound, _comma, _left_parenthesis, _right_parenthesis,
	_left_brace, _right_brace, _end
};
string termin_string[TERM_NUM] = {
	"int","void","else","if","while",
	"return","$ID","$NUM","=","+",
	"-","*","/","<","<=",
	">",">=","==","!=",
	";",",","(",")",
	"{","}","#"
};
//产生式
vector<vector<int>> produce_array =
{
	{},
	{Program,SubProgram},//1
	{SubProgram,Declaration,TempProgram},//2
	{TempProgram,SubProgram},//3
	{Declaration,_int + NON_TERM_NUM,_ID + NON_TERM_NUM,Type},//4
	{Declaration,_void + NON_TERM_NUM,_ID + NON_TERM_NUM,Function},//5
	{Type,Extra_4,TempBound},//6
	{Type,Function},//7
	{TempBound,_bound + NON_TERM_NUM},//8
	{Function,TempLeftParenthesis,_left_parenthesis + NON_TERM_NUM,Parameter,ParameterNum,_right_parenthesis + NON_TERM_NUM,Block,TempFunction},//9
	{Parameter,TempInt},//10
	{Parameter,_void + NON_TERM_NUM},//11
	{TempInt,IntParameter,RightEnd_1},//12
	{RightEnd_1,_comma + NON_TERM_NUM,TempInt},//13
	{IntParameter,_int + NON_TERM_NUM,_ID + NON_TERM_NUM,Extra_4},//14
	{Block,_left_brace + NON_TERM_NUM,NumDeclaration,TempSentence,_right_brace + NON_TERM_NUM},//15
	{NumDeclaration,IntParameter_1,Extra_4,_bound + NON_TERM_NUM,NumDeclaration},//16
	{IntParameter_1,_int + NON_TERM_NUM,_ID + NON_TERM_NUM},//17
	{TempSentence,TempReturn,TempSentence_1},//18
	{TempSentence_1,TempSentence},//19
	{TempReturn,IfSentence},//20
	{TempReturn,WhileSentence},//21
	{TempReturn,ReturnSentence},//22
	{TempReturn,TempSentence_3},//23
	{TempSentence_3,Extra_5,Extra_9,_ID + NON_TERM_NUM,Extra_9,_assign + NON_TERM_NUM,Expression,Extra_6,Extra_12,_bound + NON_TERM_NUM},//24
	{ReturnSentence,_return + NON_TERM_NUM,ReturnValue,SentenceEnd,_bound + NON_TERM_NUM},//25
	{ReturnValue,Expression},//26
	{WhileSentence,_while + NON_TERM_NUM,Extra_1,_left_parenthesis + NON_TERM_NUM,Extra_5,Expression,Extra_7,_right_parenthesis + NON_TERM_NUM,Block,Extra_8},//27
	{IfSentence,_if + NON_TERM_NUM,Extra_1,_left_parenthesis + NON_TERM_NUM,Extra_5,Expression,Extra_7,_right_parenthesis + NON_TERM_NUM,Block,Extra_2,TempSentence_2,Extra_3},//28
	{TempSentence_2,JumpElse,_else + NON_TERM_NUM,Extra_1,Block,Extra_2},//29
	{Expression,TempExpression,Relop},//30
	{Relop,Extra_9,_lower + NON_TERM_NUM,Expression},//31
	{Relop,Extra_9,_lower_equal + NON_TERM_NUM,Expression},//32
	{Relop,Extra_9,_larger + NON_TERM_NUM,Expression},//33
	{Relop,Extra_9,_larger_equal + NON_TERM_NUM,Expression},//34
	{Relop,Extra_9,_equal + NON_TERM_NUM,Expression},//35
	{Relop,Extra_9,_unequal + NON_TERM_NUM,Expression},//36
	{TempExpression,TempSentence_4,Token},//37
	{Token,Extra_9,_plus + NON_TERM_NUM,TempExpression,Extra_6},//38
	{Token,Extra_9,_minus + NON_TERM_NUM,TempExpression,Extra_6},//39
	{TempSentence_4,Token_2,Token_1},//40
	{Token_1,Extra_9,_multiply + NON_TERM_NUM,TempSentence_4,Extra_6},//41
	{Token_1,Extra_9,_divide + NON_TERM_NUM,TempSentence_4,Extra_6},//42
	{Token_2,Extra_9,_NUM + NON_TERM_NUM},//43
	{Token_2,_left_parenthesis + NON_TERM_NUM,Expression,_right_parenthesis + NON_TERM_NUM},//44
	{Token_2,Extra_9,_ID + NON_TERM_NUM,Token_3},//45
	{Token_3,Call},//46
	{Call,Extra_10,_left_parenthesis + NON_TERM_NUM,TempExpression_1,Extra_11,_right_parenthesis + NON_TERM_NUM},//47
	{TempSentence_5,TempExpression_1},//48
	{TempExpression_1,Expression,RightEnd},//49
	{RightEnd,Extra_11,_comma + NON_TERM_NUM, TempExpression_1}//50
};
int table[NON_TERM_NUM][TERM_NUM];
void init_predict_table()
{
	memset(table, -1, NON_TERM_NUM*TERM_NUM * sizeof(int));
	//将预测分析表中有状态转移的部分输入
	//Program
	table[Program][_int] = table[Program][_void] = 1;
	//SubProgram
	table[SubProgram][_int] = table[SubProgram][_void] = 2;
	//TempProgram
	table[TempProgram][_int] = table[TempProgram][_void] = 3;
	table[TempProgram][_end] = 0;
	//Declaration
	table[Declaration][_int] = 4;
	table[Declaration][_void] = 5;
	//Type
	table[Type][_bound] = 6;
	table[Type][_left_parenthesis] = 7;
	//TempBound
	table[TempBound][_bound] = 8;
	//Function
	table[Function][_left_parenthesis] = 9;
	//Parameter
	table[Parameter][_int] = 10;
	table[Parameter][_void] = 11;
	table[Parameter][_right_parenthesis] = 0;
	//TempInt
	table[TempInt][_int] = 12;
	//RightEnd_1
	table[RightEnd_1][_comma] = 13;
	table[RightEnd_1][_right_parenthesis] = 0;
	//IntParameter
	table[IntParameter][_int] = 14;
	//Block
	table[Block][_left_brace] = 15;
	//NumDeclaration
	table[NumDeclaration][_int] = 16;
	table[NumDeclaration][_if] = table[NumDeclaration][_while] = table[NumDeclaration][_return] = table[NumDeclaration][_ID] = 0;
	//IntParameter_1
	table[IntParameter_1][_int] = 17;
	//TempSentence
	table[TempSentence][_if] = table[TempSentence][_while] = table[TempSentence][_return] = table[TempSentence][_ID] = 18;
	//TempSentence_1
	table[TempSentence_1][_if] = table[TempSentence_1][_while] = table[TempSentence_1][_return] = table[TempSentence_1][_ID] = 19;
	table[TempSentence_1][_right_brace] = 0;
	//TempReturn
	table[TempReturn][_if] = 20;
	table[TempReturn][_while] = 21;
	table[TempReturn][_return] = 22;
	table[TempReturn][_ID] = 23;
	//TempSentence_3
	table[TempSentence_3][_ID] = 24;
	//ReturnSentence
	table[ReturnSentence][_return] = 25;
	//ReturnValue
	table[ReturnValue][_ID] = table[ReturnValue][_NUM] = table[ReturnValue][_left_parenthesis] = 26;
	table[ReturnValue][_bound] = 0;
	//WhileSentence
	table[WhileSentence][_while] = 27;
	//IfSentence
	table[IfSentence][_if] = 28;
	//TempSentence_2
	table[TempSentence_2][_else] = 29;
	table[TempSentence_2][_if] = table[TempSentence_2][_while] = table[TempSentence_2][_return] = table[TempSentence_2][_ID] = table[TempSentence_2][_right_brace] = 0;
	//Expression
	table[Expression][_ID] = table[Expression][_NUM] = table[Expression][_left_parenthesis] = 30;
	//Relop
	table[Relop][_lower] = 31;
	table[Relop][_lower_equal] = 32;
	table[Relop][_larger] = 33;
	table[Relop][_larger_equal] = 34;
	table[Relop][_equal] = 35;
	table[Relop][_unequal] = 36;
	table[Relop][_bound] = table[Relop][_comma] = table[Relop][_right_parenthesis] = 0;
	//TempExpression
	table[TempExpression][_ID] = table[TempExpression][_NUM] = table[TempExpression][_left_parenthesis] = 37;
	//Token
	table[Token][_plus] = 38;
	table[Token][_minus] = 39;
	table[Token][_lower] = table[Token][_lower_equal] = table[Token][_larger] = table[Token][_larger_equal] = table[Token][_equal] = table[Token][_unequal] = table[Token][_bound] = table[Token][_comma] = table[Token][_right_parenthesis] = 0;
	//TempSentence_4
	table[TempSentence_4][_ID] = table[TempSentence_4][_NUM] = table[TempSentence_4][_left_parenthesis] = 40;
	//Token_1
	table[Token_1][_multiply] = 41;
	table[Token_1][_divide] = 42;
	table[Token_1][_plus] = table[Token_1][_minus] = table[Token_1][_lower] = table[Token_1][_lower_equal] = table[Token_1][_larger] = table[Token_1][_larger_equal] = table[Token_1][_equal] = table[Token_1][_unequal] = table[Token_1][_bound] = table[Token_1][_comma] = table[Token_1][_right_parenthesis] = 0;
	//Token_2
	table[Token_2][_ID] = 45;
	table[Token_2][_NUM] = 43;
	table[Token_2][_left_parenthesis] = 44;
	//Token_3
	table[Token_3][_plus] = table[Token_3][_minus] = table[Token_3][_multiply] = table[Token_3][_divide] = table[Token_3][_lower] = table[Token_3][_lower_equal] = table[Token_3][_larger] = table[Token_3][_larger_equal] = table[Token_3][_equal] = table[Token_3][_unequal] = table[Token_3][_bound] = table[Token_3][_comma] = table[Token_3][_right_parenthesis] = 0;
	table[Token_3][_left_parenthesis] = 46;
	//Call
	table[Call][_left_parenthesis] = 47;
	//TempSentence_5
	table[TempSentence_5][_ID] = table[TempSentence_5][_NUM] = table[TempSentence_5][_left_parenthesis] = 48;
	table[TempSentence_5][_right_parenthesis] = 0;
	//TempExpression_1
	table[TempExpression_1][_ID] = table[TempExpression_1][_NUM] = table[TempExpression_1][_left_parenthesis] = 49;
	//RightEnd
	table[RightEnd][_comma] = 50;
	table[RightEnd][_right_parenthesis] = 0;
	//Extra_1
	table[Extra_1][_left_parenthesis] = table[Extra_1][_left_brace] = 0;
	//TempLeftParenthesis
	table[TempLeftParenthesis][_left_parenthesis] = 0;
	//ParameterNum
	table[ParameterNum][_right_parenthesis] = 0;
	//SentenceEnd
	table[SentenceEnd][_bound] = 0;
	//TempFunction
	table[TempFunction][_int] = table[TempFunction][_void] = table[TempFunction][_end] = 0;
	//Extra_2
	table[Extra_2][_if] = table[Extra_2][_while] = table[Extra_2][_return] = table[Extra_2][_ID] = table[Extra_2][_right_brace] = table[Extra_2][_else] = 0;
	//JumpElse
	table[JumpElse][_else] = 0;
	//Extra_3
	table[Extra_3][_if] = table[Extra_3][_while] = table[Extra_3][_return] = table[Extra_3][_ID] = table[Extra_3][_right_brace] = 0;
	//Extra_4
	table[Extra_4][_bound] = table[Extra_4][_comma] = table[Extra_4][_right_parenthesis] = 0;
	//Extra_5
	table[Extra_5][_NUM] = table[Extra_5][_left_parenthesis] = table[Extra_5][_ID] = 0;
	//Extra_6
	table[Extra_6][_plus] = table[Extra_6][_minus] = table[Extra_6][_lower] = table[Extra_6][_lower_equal] = table[Extra_6][_larger] = table[Extra_6][_larger_equal] = table[Extra_6][_equal] = table[Extra_6][_unequal] = table[Extra_6][_bound] = table[Extra_6][_comma] = table[Extra_6][_right_parenthesis] = 0;
	//Extra_7
	table[Extra_7][_right_parenthesis] = 0;
	//Extra_8
	table[Extra_8][_if] = table[Extra_8][_while] = table[Extra_8][_return] = table[Extra_8][_ID] = table[Extra_8][_right_parenthesis] = 0;
	//push
	table[Extra_9][_ID] = table[Extra_9][_NUM] = table[Extra_9][_assign] = table[Extra_9][_plus] = table[Extra_9][_minus] = table[Extra_9][_multiply] = table[Extra_9][_divide] = table[Extra_9][_larger] = table[Extra_9][_larger_equal] = table[Extra_9][_lower] = table[Extra_9][_lower_equal] = table[Extra_9][_equal] = table[Extra_9][_unequal] = 0;
	//Extra_10
	table[Extra_10][_left_parenthesis] = 0;
	//Extra_11
	table[Extra_11][_comma] = table[Extra_11][_right_parenthesis] = 0;
	//Extra_12
	table[Extra_12][_plus] = table[Extra_12][_minus] = table[Extra_12][_lower] = table[Extra_12][_lower_equal] = table[Extra_12][_larger] = table[Extra_12][_larger_equal] = table[Extra_12][_equal] = table[Extra_12][_unequal] = table[Extra_12][_bound] = table[Extra_12][_comma] = table[Extra_12][_right_parenthesis] = table[Extra_12][_multiply] = table[Extra_12][_divide] = 0;
}

void print_produce_expression()
{
	cout << "文法产生式:" << endl;
	for (int i = 0; i < produce_array.size(); i++)
	{
		for (int j = 0; j < produce_array[i].size(); j++)
		{
			if (produce_array[i][j] < NON_TERM_NUM)
				cout << non_termin_string[produce_array[i][j]] << " ";
			else
				cout << termin_string[produce_array[i][j] % NON_TERM_NUM] << " ";
			if (j == 0)
			{
				cout << "-> ";
			}
		}
		if(i!=0)
			cout << endl;
	}
}

int find_non_termin_index(string Expressionession)
{
	for (int i = 0; i < NON_TERM_NUM; i++)
	{
		if (non_termin_string[i] == Expressionession)
		{
			return i;
		}
	}
	return -1;
}

int find_termin_index(string token)
{
	for (int i = 0; i < TERM_NUM; i++)
	{
		if (termin_string[i] == token)
		{
			return i;
		}
	}
	return -1;
}

bool print_process(vector<string> input_string)
{
	vector<string> analyze_stack;
	analyze_stack.push_back("#");
	analyze_stack.push_back(non_termin_string[Program]);
	input_string.push_back("#");
	int count = 0;
	while (!analyze_stack.empty())
	{
		count++;
		cout << "第" << count << "步：" << endl;
		cout << "语法栈:";
		for (int i = 0; i < analyze_stack.size(); i++)
		{
			cout << analyze_stack[i] << " ";
		}
		cout << endl;
		cout << "输入串:";
		for (int i = 0; i < input_string.size(); i++)
		{
			cout << input_string[i] << " ";
		}
		cout << endl << endl;
		if (analyze_stack[analyze_stack.size() - 1] != input_string[0])//若分析栈的栈顶和输入串的栈顶不同
		{
			//找出在预测分析表中的入口位置
			int non_termin_index = find_non_termin_index(analyze_stack[analyze_stack.size() - 1]);
			int termin_index = find_termin_index(input_string[0]);
			//预测表中的产生式编号
			int produce_index = table[non_termin_index][termin_index];
			//进行归约操作
			if (produce_index == -1)
			{
				cout << "error!" << endl;
				return false;
			}
			else if (produce_index == 0)
			{
				analyze_stack.pop_back();
			}
			else
			{
				analyze_stack.pop_back();
				for (int i = produce_array[produce_index].size() - 1; i > 0; i--)
				{
					if (produce_array[produce_index][i] < NON_TERM_NUM)
					{
						analyze_stack.push_back(non_termin_string[produce_array[produce_index][i]]);
					}
					else
					{
						analyze_stack.push_back(termin_string[produce_array[produce_index][i] % NON_TERM_NUM]);
					}
				}
			}
		}
		else
		{
			analyze_stack.pop_back();
			input_string.erase(input_string.begin());
		}
	}
	return true;
}
