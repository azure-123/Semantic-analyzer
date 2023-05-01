#pragma once
#include<string>
using namespace std;
//非终结符，用枚举量表示
#define NON_TERM_NUM 52
#define TERM_NUM 26


void init_predict_table();//对预测表进行初始化
void print_produce_expression();//打印文法产生式
int find_non_termin_index(string expression);//查找非终结符的索引
int find_termin_index(string token);//查找终结符的索引
bool print_process(vector<string> input_string);//进行归约过程并将结果打印


