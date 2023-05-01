#include<iostream>
#include<string>
#include<vector>
#include"semantic_analyzer.h"
using namespace std;
vector <string> par_name;
vector<int> par_value;
int gen = 0;
int temp_num = 0;

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
			bool mult_result = _multiply(temp);
			bool div_result = _divide(temp);
			bool plus_result = _plus(temp);
			bool minus_result = _minus(temp);
			if (!assign_result)
				assign_result = assign(temp);
			if (!if_result)
				if_result = if_sentence(temp);
			if (!else_result)
				else_result = else_sentence(temp);
			if (!while_result)
				while_result = while_sentence(temp);
			if (!return_result)
				return_result = return_sentence(temp);

			if (!plus_result && !mult_result&&!div_result&&!minus_result)
				break;
		}
		temp = strip(test);
	}
	cout << gen << ":(j,_,_," << gen - 4 << ")" << endl;
	cout << ++gen<<":" << endl;
	
	//print_par(par_name, par_value);
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

bool _plus(vector<string> &test)
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
				gen++;
			}
		}
		i++;
		if (i >= len)
			break;
	}
	return is_flag;
}

bool _multiply(vector<string> &test)
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
				gen++;
			}
		}
		i++;
		if (i >= len)
			break;
	}
	return is_flag;
}

bool _minus(vector<string> &test)
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
				gen++;
			}
		}
		i++;
		if (i >= len)
			break;
	}
	return is_flag;
}

bool _divide(vector<string> &test)
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
				gen++;
			}
		}
		i++;
		if (i >= len)
			break;
	}
	return is_flag;
}


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
		gen++;
		cout << gen << ":(j,_,_," << gen+4 << ")" << endl;
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
		gen++;
		return true;
	}
	return false;
}
