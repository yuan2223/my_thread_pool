#pragma once
#include<iostream>
#include<string>
using namespace std;

//ְ��������  
class Worker
{
public:
	//��ʾ������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDepeName() = 0; //���麯�� ����ʵ�� ������ʵ��

	int m_id;
	string m_name;
	int m_dept_id;
};
