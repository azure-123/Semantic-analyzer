#pragma once
#include<string>
using namespace std;
//���ս������ö������ʾ
#define NON_TERM_NUM 52
#define TERM_NUM 26


void init_predict_table();//��Ԥ�����г�ʼ��
void print_produce_expression();//��ӡ�ķ�����ʽ
int find_non_termin_index(string expression);//���ҷ��ս��������
int find_termin_index(string token);//�����ս��������
bool print_process(vector<string> input_string);//���й�Լ���̲��������ӡ


