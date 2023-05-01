#include<iostream>
#include<string>
#include"lex_analyzer.h"
#include"syntactic_analyzer.h"
#include"semantic_analyzer.h"

using namespace std;
int main()
{
	string test;
	vector<string> result;
	vector<string> result_1;
	cout << "请输入代码(另起一行#结尾):" << endl;
	while (true)
	{
		if (test[0] == '#')
			break;
		getline(cin, test);
		result = scanner(test);
		result_1 = scanner_1(test);
		result.push_back("\n");
	}
	int len = result.size();
	cout << "语法分析：" << endl;
	init_predict_table();
	print_produce_expression();
	bool flag=print_process(result_1);
	if (flag)
	{
		cout << "中间代码生成：" << endl;
		semantic(result);
	}
	return 0;
}