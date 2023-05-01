#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
void semantic(vector<string> result);//控制器，调用工具函数
bool is_exist_in_table(string par);//判断符号是否在符号表当中
void definition(vector<string> &test);//变量定义语义分析
bool assign(vector<string> &test);//变量赋值语义分析
bool _plus(vector<string> &test);//加法语义分析
bool _multiply(vector<string> &test);//乘法语义分析
bool _minus(vector<string> &test);//减法语义分析
bool _divide(vector<string> &test);//除法语义分析

int get_par_index(string par);//获取变量在符号表当中的入口
void print_test(vector <string> test);//打印中间代码
void print_par(vector <string> par_name, vector<int> par_value);//打印变量符号表，测试用
bool par_is_letter(string par);//区分变量和数字
vector<string> strip(vector<string> &test);//分解字符串，以语句为单位分析
bool if_sentence(vector<string> &test);//if语义分析
bool while_sentence(vector<string> &test);//while语义分析
bool return_sentence(vector<string> &test);//return语义分析
bool else_sentence(vector<string> &test);//else语义分析

