#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<string>
#include<vector>
#include<QDebug>
#include<QMessageBox>
#define NON_TERM_NUM 52
#define TERM_NUM 26



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("syntactic analyzer");
    this->resize(1500,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}


using namespace std;
vector<string> id_table;
QString scanner_out;
QString sem_out;

bool IsLetter(char ch)
{
    if ((ch >= 'a'&&ch <= 'z')|| (ch >= 'A'&&ch <= 'Z'))
        return true;
    else
        return false;
}

bool IsDigit(char ch)
{
    if (ch>='0'&&ch<='9')
        return true;
    else
        return false;
}

int scanner(string str)
{
    vector<string> result;

    int i = 0;
    string strToken = "";
    while (i<str.length())
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
                //cout << strToken << endl;
                //cout << "<$int,->" << endl;
                result.push_back("<$int,->\n");
                scanner_out.append("<$int,->\n");
            }
            else if ("void" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$void,->" << endl;
                result.push_back("<$void,->\n");
                scanner_out.append("<$void,->\n");
            }
            else if ("if" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$if,->" << endl;
                result.push_back("<$if,->\n");
                scanner_out.append("<$if,->\n");
            }
            else if ("else" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$else,->" << endl;
                result.push_back("<$else,->\n");
                scanner_out.append("<$else,->\n");
            }
            else if ("while" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$while,->" << endl;
                result.push_back("<$while,->\n");
                scanner_out.append("<$while,->\n");
            }
            else if ("return" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$return,->" << endl;
                result.push_back("<$return,->\n");
                scanner_out.append("<$return,->\n");
            }
            else if ("char" == strToken)
            {
                result.push_back("<$char,->\n");
                scanner_out.append("<$char,->\n");
            }
            else if ("const" == strToken)
            {
                result.push_back("<$const,->\n");
                scanner_out.append("<$const,->\n");
            }
            else if ("unsigned" == strToken)
            {
                result.push_back("<$unsigned,->\n");
                scanner_out.append("<$unsigned,->\n");
            }
            else if ("bool" == strToken)
            {
                result.push_back("<$bool,->\n");
                scanner_out.append("<$bool,->\n");
            }
            else if ("true" == strToken)
            {
                result.push_back("<$true,->\n");
                scanner_out.append("<$true,->\n");
            }
            else if ("false" == strToken)
            {
                result.push_back("<$false,->\n");
                scanner_out.append("<$false,->\n");
            }
else
            {
                int index=0;
                //cout << strToken << endl;
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
                //cout << "<$ID," << index << ">" << endl;
                result.push_back("<$ID,"+to_string(index)+">\n");
                scanner_out.append("<$ID,"+QString::number(index,10)+">\n");
                i--;
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
            //cout << strToken << endl;
            result.push_back("<$VALUE,"+strToken+">\n");
            scanner_out.append("<$VALUE,"+QString::fromStdString(strToken)+">\n");
            //cout << "<$VALUE," << strToken << ">" << endl;
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
                scanner_out.append("<$EQUAL,->\n");
            }
            else
            {
                //cout << str[i] << endl;
                //cout << "<$ASSIGN,->" << endl;
                result.push_back("<$ASSIGN,->\n");
                scanner_out.append("<$ASSIGN,->\n");
                i++;
            }
        }
        else if ('+' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$PLUS,->" << endl;
            result.push_back("<$PLUS,->\n");
            scanner_out.append("<$PLUS,->\n");
            i++;
        }
        else if ('-' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$MINUS,->" << endl;
            result.push_back("<$MINUS,->\n");
            scanner_out.append("<$MINUS,->\n");
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
                scanner_out.append("<$RIGHT_COMM,->\n");
            }
            else
            {
                //cout << "<$MULT,->" << endl;
                result.push_back("<$MULT,->\n");
                scanner_out.append("<$MULT,->\n");
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
                scanner_out.append("<$LEFT_COMM,->\n");
            }
            else if ('/' == str[i + 1])
            {
                i++;
                strToken = "//";
                //cout << strToken<<endl;
                strToken = "";
                //cout << "<$LEFT_COMM,->" << endl;
                result.push_back("<$LINE_COMMENT,->\n");
                scanner_out.append("<$LINE_COMMENT,->\n");
            }
            else
            {
                //cout << str[i] << endl;
                //cout << "<$DIV,->" << endl;
                result.push_back("<$DIV,->\n");
                scanner_out.append("<$LINE_COMMENT,->\n");
                i++;
            }
        }
        else if ('>' == str[i])
        {
            if ('=' == str[i + 1])
            {
                i+=2;
                strToken = ">=";
                //cout << strToken << endl;
                //cout << "<$GREATER_OR_EQUAL,->" << endl;
                result.push_back("<$GREATER_OR_EQUAL,->\n");
                scanner_out.append("<$GREATER_OR_EQUAL,->\n");
                strToken = "";
            }
            else
            {
                //cout << str[i] << endl;
                //cout << "<$GREATER,->" << endl;
                result.push_back("<$GREATER,->\n");
                scanner_out.append("<$GREATER,->\n");
                i++;
            }
        }
        else if ('<' == str[i])
        {
            if ('=' == str[i + 1])
            {
                i+=2;
                strToken = "<=";
                //cout << "<$LOWER_OR_EQUAL,->" << endl;
                //cout << strToken << endl;
                result.push_back("<$LOWER_OR_EQUAL,->\n");
                scanner_out.append("<$LOWER_OR_EQUAL,->\n");
                strToken = "";
            }
            else
            {
                //cout << str[i] << endl;
                //cout << "<$LOWER,->" << endl;
                result.push_back("<$LOWER,->\n");
                scanner_out.append("<$LOWER,->\n");
                i++;
            }
        }
        else if ('!' == str[i])
        {
            if ('=' == str[i + 1])
            {
                i+=2;
                strToken = "!=";
                //cout << strToken<<endl;
                //cout << "<$UNEQUAL,->" << endl;
                result.push_back("<$UNEQUAL,->\n");
                scanner_out.append("<$UNEQUAL,->\n");
                strToken = "";
            }
        }
        else if ('(' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$LPAR,->" << endl;
            result.push_back("<$LPAR,->\n");
            scanner_out.append("<$LPAR,->\n");
            i++;
        }
        else if (')' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$RPAR,->" << endl;
            result.push_back("<$RPAR,->\n");
            scanner_out.append("<$RPAR,->\n");
            i++;
        }
        else if ('{' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$LBRACE,->" << endl;
            result.push_back("<$LBRACE,->\n");
            scanner_out.append("<$LBRACE,->\n");
            i++;
        }
        else if ('}' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$RBRACE,->" << endl;
            result.push_back("<$RBRACE,->\n");
            scanner_out.append("<$RBRACE,->\n");
            i++;
        }
        else if ('[' == str[i])
        {
            result.push_back("<$LSQUARE_BRACKET,->\n");
            scanner_out.append("<$LSQUARE_BRACKET,->\n");
            i++;
        }
        else if (']' == str[i])
        {
            result.push_back("<$RSQUARE_BRACKET,->\n");
            scanner_out.append("<$RSQUARE_BRACKET,->\n");
            i++;
        }
        else if ('\"' == str[i])
        {
            result.push_back("<$DOUBLE_QUOTE,->\n");
            scanner_out.append("<$DOUBLE_QUOTE,->\n");
            i++;
        }
        else if ('\'' == str[i])
        {
            result.push_back("<$SINGLE_QUOTE,->\n");
            scanner_out.append("<$SINGLE_QUOTE,->\n");
            i++;
        }
        else if (';' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$BOUND,->" << endl;
            result.push_back("<$BOUND,->\n");
            scanner_out.append("<$BOUND,->\n");
            i++;
        }
        else if (',' == str[i])
        {
        //cout << str[i] << endl;
        //cout << "<$BOUND,->" << endl;
            result.push_back("<$COMMA,->\n");
            scanner_out.append("<$COMMA,->\n");
            i++;
        }
        else if (' ' == str[i])
        {
            while (str[i]==' ')
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }
    return 0;
}


vector<string> scanner_else(string str)
{
    vector<string> result;
    vector<string> lex_string;
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
                lex_string.push_back("$ID");
                i--;
            }
            strToken = "";
            if (str[i] == ';'||str[i] == ')'||str[i]=='(')
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
            lex_string.push_back("$NUM");
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
    return lex_string;
}

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
    {TempSentence_3,Extra_5,Extra_9,_ID + NON_TERM_NUM,Extra_9,_assign+NON_TERM_NUM,Expression,Extra_6,Extra_12,_bound+NON_TERM_NUM},//24
    {ReturnSentence,_return + NON_TERM_NUM,ReturnValue,SentenceEnd,_bound+NON_TERM_NUM},//25
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
    table[Extra_3][_if] = table[Extra_3][_while] = table[Extra_3][_return] = table[Extra_3][_ID] = table[Extra_3][_right_brace]=0;
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
    table[Extra_12][_plus] = table[Extra_12][_minus] = table[Extra_12][_lower] = table[Extra_12][_lower_equal] = table[Extra_12][_larger] = table[Extra_12][_larger_equal] = table[Extra_12][_equal] = table[Extra_12][_unequal] = table[Extra_12][_bound] = table[Extra_12][_comma] = table[Extra_12][_right_parenthesis] = table[Extra_12][_multiply] = table[Extra_12][_divide]=0;

    /*for (int i = 0; i < NON_TERM_NUM; i++)
    {
        for (int j = 0; j < TERM_NUM; j++)
        {
            cout<<setw(3)<<table[i][j];
        }
        cout << endl;
    }*/
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

vector <string> par_name;
vector<int> par_value;
int gen = 0;
int temp_num = 0;

bool par_is_letter(string par)
{
    if (par[0] >= '0'&&par[0] <= '9')
        return true;
    else
        return false;
}

bool is_exist_in_table(string par)
{
    for (int i = 0; i < par_name.size(); i++)
    {
        if (par == par_name[i])
        {
            return true;
        }
    }
    return false;
}

int get_par_index(string par)
{
    for (int i = 0; i < par_name.size(); i++)
    {
        if (par_name[i] == par)
        {
            return i;
        }
    }
    return -1;
}

void definition(vector<string> &test)
{
    int i = 0;
    int len = test.size();
    /*for (int i = 0; i < test.size(); i++)
    {*/
    while (true)
    {
        if (test[i] == "int"&&test[i + 2] != "(" && !is_exist_in_table(test[i + 1]))
        {
            par_name.push_back(test[i + 1]);
            par_value.push_back(0);
            if (test[i + 2] == ";")
            {
                for (int j = 0; j < 4; j++)
                {
                    test.erase(test.begin() + i);
                }
                len -= 4;
                i--;
            }
        }
        i++;
        if (i == len)
        {
            break;
        }
    }
}

bool assign(vector<string> &test)
{
    bool is_flag = false;
    int i = 0;
    int len = test.size();
    /*for (int i = 0; i < test.size(); i++)
    {*/
    while (true)
    {
        if (is_exist_in_table(test[i]) && test[i + 1] == "="&&test[i + 2][0] >= '0'&&test[i + 2][0] <= '9')
        {
            for (int j = 0; j < par_value.size(); j++)
            {
                if (par_name[j] == test[i])
                {
                    par_value[j] = atoi(test[i + 2].c_str());
                    is_flag = true;
                    cout << gen << ":(" << "=," << par_value[j] << ",_," << par_name[j] << ")" << endl;
                    sem_out.append(QString::number(gen)+":(=,"+QString::number(par_value[j])+",_,"+QString::fromStdString(par_name[j])+")\n");
                    for (int k = 0; k < 4; k++)
                    {
                        test.erase(test.begin());
                    }
                    len -= 4;
                    i--;
                    gen++;
                    break;
                }
            }
        }
        else if (is_exist_in_table(test[i]) && test[i + 1] == "="&&test[i + 3] == ";")
        {
            int index1 = get_par_index(test[i]);
            int index2 = get_par_index(test[i + 2]);
            par_value[index1] = par_value[index2];
            is_flag = true;
            cout << gen << ":(" << "=," << par_name[index2] << ",_," << par_name[index1] << ")" << endl;
            sem_out.append(QString::number(gen)+":(=,"+QString::fromStdString(par_name[index2])+",_,"+QString::fromStdString(par_name[index1])+")\n");
            gen++;
        }
        i++;
        if (len <= i || i <= 0)
        {
            break;
        }
    }
    return is_flag;
}

bool s_plus(vector<string> &test)
{
    bool is_flag = false;
    int len = test.size();
    int i = 0;
    while (true)
    {
        if (test[i] == "+")
        {

            int index1 = get_par_index(test[i - 1]);
            int index2 = get_par_index(test[i + 1]);
            if (index1 != -1 && index2 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                par_value.push_back(par_value[index1] + par_value[index2]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }

                is_flag = true;
                cout << gen << ":(" << "+," << par_name[index1] << "," << par_name[index2] << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(+,"+QString::fromStdString(par_name[index1])+","+QString::fromStdString(par_name[index2])+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
            else if (test[i - 1][0] >= '0'&&test[i - 1][0] <= '9'&&index2 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                int value = atoi(test[i - 1].c_str());
                par_value.push_back(value + par_value[index2]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }
                is_flag = true;
                cout << gen << ":(" << "+," << par_name[index2] << "," << value << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(+,"+QString::fromStdString(par_name[index2])+","+QString::number(value)+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
            else if (test[i + 1][0] >= '0'&&test[i + 1][0] <= '9'&&index1 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                int value = atoi(test[i + 1].c_str());
                par_value.push_back(value + par_value[index1]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }
                is_flag = true;
                cout << gen << ":(" << "+," << par_name[index1] << "," << value << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(+,"+QString::fromStdString(par_name[index1])+","+QString::number(value)+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
        }
        i++;
        if (i >= len)
            break;
    }
    return is_flag;
}

bool s_multiply(vector<string> &test)
{
    bool is_flag = false;
    int len = test.size();
    int i = 0;
    while (true)
    {
        if (test[i] == "*")
        {
            int index1 = get_par_index(test[i - 1]);
            int index2 = get_par_index(test[i + 1]);
            if (index1 != -1 && index2 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                par_value.push_back(par_value[index1] * par_value[index2]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }
                is_flag = true;
                cout << gen << ":(" << "*," << par_name[index1] << "," << par_name[index2] << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(*,"+QString::fromStdString(par_name[index1])+","+QString::fromStdString(par_name[index2])+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
            else if (test[i - 1][0] >= '0'&&test[i - 1][0] <= '9'&&index2 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                int value = atoi(test[i - 1].c_str());
                par_value.push_back(value*par_value[index2]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }

                is_flag = true;
                cout << gen << ":(" << "*," << par_name[index2] << "," << value << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(*,"+QString::fromStdString(par_name[index2])+","+QString::number(value)+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
            else if (test[i + 1][0] >= '0'&&test[i + 1][0] <= '9'&&index1 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                int value = atoi(test[i + 1].c_str());
                par_value.push_back(value * par_value[index1]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }

                is_flag = true;
                cout << gen << ":(" << "*," << par_name[index1] << "," << value << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(*,"+QString::fromStdString(par_name[index1])+","+QString::number(value)+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
        }
        i++;
        if (i >= len)
            break;
    }
    return is_flag;
}

bool s_minus(vector<string> &test)
{
    bool is_flag = false;
    int len = test.size();
    int i = 0;
    while (true)
    {
        if (test[i] == "-")
        {
            int index1 = get_par_index(test[i - 1]);
            int index2 = get_par_index(test[i + 1]);
            if (index1 != -1 && index2 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                par_value.push_back(par_value[index1] - par_value[index2]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }
                is_flag = true;
                cout << gen << ":(" << "-," << par_name[index1] << "," << par_name[index2] << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(-,"+QString::fromStdString(par_name[index1])+","+QString::fromStdString(par_name[index2])+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
            else if (test[i - 1][0] >= '0'&&test[i - 1][0] <= '9'&&index2 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                int value = atoi(test[i - 1].c_str());
                par_value.push_back(value - par_value[index2]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }

                is_flag = true;
                cout << gen << ":(" << "-," << par_name[index2] << "," << value << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(-,"+QString::fromStdString(par_name[index2])+","+QString::number(value)+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
            else if (test[i + 1][0] >= '0'&&test[i + 1][0] <= '9'&&index1 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                int value = atoi(test[i + 1].c_str());
                par_value.push_back(value - par_value[index1]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }

                is_flag = true;
                cout << gen << ":(" << "-," << par_name[index1] << "," << value << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(-,"+QString::fromStdString(par_name[index1])+","+QString::number(value)+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
        }
        i++;
        if (i >= len)
            break;
    }
    return is_flag;
}

bool s_divide(vector<string> &test)
{
    bool is_flag = false;
    int len = test.size();
    int i = 0;
    while (true)
    {
        if (test[i] == "/")
        {
            int index1 = get_par_index(test[i - 1]);
            int index2 = get_par_index(test[i + 1]);
            if (index1 != -1 && index2 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                par_value.push_back(par_value[index1] / par_value[index2]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }
                is_flag = true;
                cout << gen << ":(" << "/," << par_name[index1] << "," << par_name[index2] << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(/,"+QString::fromStdString(par_name[index1])+","+QString::fromStdString(par_name[index2])+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
            else if (test[i - 1][0] >= '0'&&test[i - 1][0] <= '9'&&index2 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                int value = atoi(test[i - 1].c_str());
                par_value.push_back(value / par_value[index2]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }

                is_flag = true;
                cout << gen << ":(" << "/," << par_name[index2] << "," << value << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(/,"+QString::fromStdString(par_name[index2])+","+QString::number(value)+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
            else if (test[i + 1][0] >= '0'&&test[i + 1][0] <= '9'&&index1 != -1)
            {
                par_name.push_back("T" + to_string(temp_num));
                temp_num++;
                int value = atoi(test[i + 1].c_str());
                par_value.push_back(value / par_value[index1]);
                for (int j = 0; j < 2; j++)
                {
                    test.erase(test.begin() + i - 1);
                }
                test[i - 1] = par_name[par_name.size() - 1];
                len -= 3;
                if (test[i - 2] == "("&&test[i] == ")")
                {
                    test.erase(test.begin() + i);
                    test.erase(test.begin() + i - 2);
                    len -= 2;
                }

                is_flag = true;
                cout << gen << ":(" << "/," << par_name[index1] << "," << value << "," << par_name[par_name.size() - 1] << ")" << endl;
                sem_out.append(QString::number(gen)+":(/,"+QString::fromStdString(par_name[index1])+","+QString::number(value)+","+QString::fromStdString(par_name[par_name.size()-1])+")\n");
                gen++;
            }
        }
        i++;
        if (i >= len)
            break;
    }
    return is_flag;
}




void print_test(vector <string> test)
{
    for (int i = 0; i < test.size(); i++)
    {
        cout << test[i] << " ";
    }
    cout << endl;
}

void print_par(vector <string> par_name, vector<int> par_value)
{
    for (int i = 0; i < par_value.size(); i++)
    {
        cout << par_name[i] << " " << par_value[i] << endl;
    }
}

vector<string> strip(vector<string> &test)
{
    //int len = test.size();
    for(int i=0;i<test.size();i++)
    {
        cout<<test[i]<<" ";

    }
    vector<string> temp;
    int i = 0;
    while (true)
    {
        if (test[0] == "\n")
        {
            test.erase(test.begin());
            return temp;
        }
        else if (test[0] == "{"&&test[1] == "\n")
        {
            test.erase(test.begin());
            test.erase(test.begin());
        }
        else if (test[0] == "}"&&test[1] == "\n")
        {
            test.erase(test.begin());
            test.erase(test.begin());
        }
        else
        {
            temp.push_back(test[0]);
            test.erase(test.begin());
        }
        if(test.size()<=0)
        {
            return temp;
        }
    }
    return temp;
}

bool if_sentence(vector<string> &test)
{
    int len = test.size();
    if (len == 0)
        return false;
    if (test[0] == "if")
    {
        cout << gen << ":(j" << test[3] << "," << test[2] << "," << test[4] << "," << gen + 6 << ")" << endl;
        sem_out.append(QString::number(gen)+":(j"+QString::fromStdString(test[3])+","+QString::fromStdString(test[2])+","+QString::fromStdString(test[4])+","+QString::number(gen+6)+")\n");
        gen++;
        return true;
    }
    return false;
}

bool while_sentence(vector<string> &test)
{
    int len = test.size();
    if (len == 0)
        return false;
    if (test[0] == "while")
    {
        cout << gen << ":(j" << test[3] << "," << test[2] << "," << test[4] << "," << gen+2 << ")" << endl;
        sem_out.append(QString::number(gen)+":(j"+QString::fromStdString(test[3])+","+QString::fromStdString(test[2])+","+QString::fromStdString(test[4])+","+QString::number(gen+2)+")\n");
        gen++;
        cout << gen << ":(j,_,_," << gen+4 << ")" << endl;
        sem_out.append(QString::number(gen)+":(j,_,_,"+QString::number(gen+4)+")\n");
        gen++;
        return true;
    }
    return false;
}

bool return_sentence(vector<string> &test)
{
    int len = test.size();
    if (len == 0)
        return false;
    if (test[0] == "return")
    {
        return true;
    }
    return false;
}

bool else_sentence(vector<string> &test)
{
    int len = test.size();
    if (len == 0)
        return false;
    if (test[0] == "else")
    {
        cout << gen << ":(j,_,_," << gen + 2 << ")" << endl;
        sem_out.append(QString::number(gen)+":(j,_,_,"+QString::number(gen+2)+")\n");
        gen++;
        return true;
    }
    return false;
}


void semantic(vector<string> test)
{
    //将定义的变量取出来，放在符号表中
    definition(test);
    //预处理
    while (test[0] != ")")
    {
        test.erase(test.begin());
    }
    test.erase(test.begin());
    while (test[0] == "\n")
    {
        test.erase(test.begin());
    }
    //print_test(test);

    //对变量的赋值部分，为符号表中的变量进行赋值
    /*bool is_exist = assign(test);
    if (!is_exist)
    {
        cout << "该变量未定义！";
    }*/
    //print_test(test);
    vector<string> temp = strip(test);
    /*for (int i = 0; i < temp.size(); i++)
    {
        cout << temp[i] << " ";
    }
    cout << endl;*/
    while (test.size() > 0 && temp.size() > 0)
    {
        bool if_result = false;
        bool assign_result = false;
        bool while_result = false;
        bool return_result = false;
        bool else_result = false;
        while (true)
        {
            //print_test(temp);
            bool mult_result = s_multiply(temp);
            cout<<"s_mult"<<endl;
            bool div_result = s_divide(temp);
            cout<<"s_div"<<endl;
            bool plus_result = s_plus(temp);
            cout<<"s_plus"<<endl;
            bool minus_result = s_minus(temp);
            cout<<"s_minus"<<endl;
            if (!assign_result)
                assign_result = assign(temp);
            cout<<"s_assign"<<endl;
            if (!if_result)
                if_result = if_sentence(temp);
            cout<<"s_if"<<endl;
            if (!else_result)
                else_result = else_sentence(temp);
            cout<<"s_else"<<endl;
            if (!while_result)
                while_result = while_sentence(temp);
            cout<<"s_while"<<endl;
            if (!return_result)
                return_result = return_sentence(temp);
            cout<<"s_return"<<endl;

            if (!plus_result && !mult_result&&!div_result&&!minus_result)
                break;
        }

        temp = strip(test);

    }
    cout << gen << ":(j,_,_," << gen - 4 << ")" << endl;
    sem_out.append(QString::number(gen)+":(j,_,_,"+QString::number(gen-4)+")\n");
    cout << ++gen<<":" << endl;
    sem_out.append(QString::number(gen)+":\n");

    //print_par(par_name, par_value);
}



void MainWindow::on_pushButton_3_clicked()
{
    QString input=ui->plainTextEdit->toPlainText();
    qDebug()<<input;
    string s_input=input.toStdString();
    scanner(s_input);
    string s_output;
    ui->textBrowser->setText(scanner_out);
}

void MainWindow::on_pushButton_clicked()
{
    QString output;
    for (int i = 0; i < produce_array.size(); i++)
        {
            for (int j = 0; j < produce_array[i].size(); j++)
            {
                if (produce_array[i][j] < NON_TERM_NUM)
                {
                    //cout << non_termin_string[produce_array[i][j]] << " ";
                    qDebug()<<QString::fromStdString(non_termin_string[produce_array[i][j]]+" ");
                    output.append(QString::fromStdString(non_termin_string[produce_array[i][j]]+" "));
                }
                else
                {
                    //cout << termin_string[produce_array[i][j] % 35] << " ";
                    qDebug()<<QString::fromStdString(termin_string[produce_array[i][j]%NON_TERM_NUM]+" ");
                    output.append(QString::fromStdString(termin_string[produce_array[i][j]%NON_TERM_NUM]+" "));
                 }
                if (j == 0)
                {
                    //cout << "-> ";
                    qDebug()<<"->";
                    output.append("-> ");
                }
            }
            //cout << endl;
            output.append("\n");
        }
    ui->textBrowser->setText(output);
}

void MainWindow::on_pushButton_2_clicked()
{
    vector<string> input_string;
    QString input=ui->plainTextEdit->toPlainText();
    qDebug()<<input;
    string s_input=input.toStdString();
    input_string=scanner_else(s_input);
    init_predict_table();
    QString syn_output;
    int count=0;


    vector<string> analyze_stack;
        analyze_stack.push_back("#");
        analyze_stack.push_back(non_termin_string[Program]);
        input_string.push_back("#");
        while (!analyze_stack.empty())
        {
            count++;
            syn_output.append("Step "+QString::number(count)+"\n");
            syn_output.append("stack: ");
            for (int i = 0; i < analyze_stack.size(); i++)
            {
                //cout << analyze_stack[i] << " ";
                syn_output.append(QString::fromStdString(analyze_stack[i])+" ");
            }
            //cout << "                     ";
            syn_output.append("\n");
            syn_output.append("string: ");
            for (int i = 0; i < input_string.size(); i++)
            {
                //cout << input_string[i] << " ";
                syn_output.append(QString::fromStdString(input_string[i])+" ");
            }
            //cout << endl;
            syn_output.append("\n\n");
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
                    //cout << "error!" << endl;
                    syn_output.append("error!");
                    ui->textBrowser->setText(syn_output);
                    QMessageBox::critical(this, tr("Syntactic Error"),
                                                        "Error: Step "+QString::number(count),
                                                        QMessageBox::Abort);
                    return;
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
    ui->textBrowser->setText(syn_output);
}

vector<string> scanner_1(string str)
{
    vector<string> result;
    vector<string> lex_string_1;
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
                    lex_string_1.push_back(strToken);
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
                lex_string_1.push_back(strToken);
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
            else if('\n'==str[i])
            {
                lex_string_1.push_back("\n");
                i++;
            }
            else
            {
                i++;
            }
        }
        lex_string_1.push_back("\n");
        return lex_string_1;
}


void MainWindow::on_pushButton_4_clicked()
{
    vector<string> input_string;
    vector<string> sem_input_string;
    QString input=ui->plainTextEdit->toPlainText();
    qDebug()<<input;
    string s_input=input.toStdString();

    input_string=scanner_else(s_input);
    sem_input_string=scanner_1(s_input);
//    for (int i=0;i<sem_input_string.size();i++)
//    {
//       qDebug() <<QString::fromStdString(sem_input_string[i])<<endl;
//    }

    init_predict_table();
    QString syn_output;
    int count=0;

    vector<string> analyze_stack;
        analyze_stack.push_back("#");
        analyze_stack.push_back(non_termin_string[Program]);
        input_string.push_back("#");
        while (!analyze_stack.empty())
        {
            count++;
            syn_output.append("Step "+QString::number(count)+"\n");
            syn_output.append("stack: ");
            syn_output.append("\n");
            syn_output.append("string: ");
            syn_output.append("\n\n");
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
                    //cout << "error!" << endl;
                    syn_output.append("error!");
                    QMessageBox::critical(this, tr("Syntactic Error"),
                                                        "Error: Syntactic error!See syntactic analysis for more details",
                                                        QMessageBox::Abort);

                    //ui->textBrowser->setText(syn_output);
                    return;
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
        gen=0;
        sem_out="";
        temp_num=0;
        semantic(sem_input_string);
        ui->textBrowser->setText(sem_out);
}
