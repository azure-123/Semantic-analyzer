#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
void semantic(vector<string> result);//�����������ù��ߺ���
bool is_exist_in_table(string par);//�жϷ����Ƿ��ڷ��ű���
void definition(vector<string> &test);//���������������
bool assign(vector<string> &test);//������ֵ�������
bool _plus(vector<string> &test);//�ӷ��������
bool _multiply(vector<string> &test);//�˷��������
bool _minus(vector<string> &test);//�����������
bool _divide(vector<string> &test);//�����������

int get_par_index(string par);//��ȡ�����ڷ��ű��е����
void print_test(vector <string> test);//��ӡ�м����
void print_par(vector <string> par_name, vector<int> par_value);//��ӡ�������ű�������
bool par_is_letter(string par);//���ֱ���������
vector<string> strip(vector<string> &test);//�ֽ��ַ����������Ϊ��λ����
bool if_sentence(vector<string> &test);//if�������
bool while_sentence(vector<string> &test);//while�������
bool return_sentence(vector<string> &test);//return�������
bool else_sentence(vector<string> &test);//else�������

