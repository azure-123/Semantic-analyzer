#pragma once
#include<string>
#include<vector>
using namespace std;
bool IsLetter(char ch);//判断是否为字母
bool IsDigit(char ch);//判断是否为数字
vector<string> scanner(string str);//扫描器，进行词法分析
vector<string> scanner_1(string str);//修改的扫描器，进行的词法分析用于中间代码生成

