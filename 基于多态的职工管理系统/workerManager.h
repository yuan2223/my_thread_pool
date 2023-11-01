#pragma once //��ֹͷ�ļ��ظ�����
#include<iostream>
#include "worker.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std;

class WorkerManager
{
public:
	WorkerManager();//���캯����ʼ������

	//չʾ�˵�
	void Show_Menu();
	//�˳�ϵͳ
	void ExitSystem();
	
	//��¼ְ������
	int m_Empnum;

	//ְ������ָ��
	Worker** EmpArray;

	//���ְ��
	void AddEmp();
	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ�յı�־'
	bool m_FileIsEmpty;

	//ͳ���ļ��е���Ա����
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();
	//�ж�ְ���Ƿ���� ���ڷ���ְ������������±� �����ڷ���-1
	int IsExit(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����Ա��
	void Find_Emp();

	//����ļ�
	void Clea_File();


	~WorkerManager();

};
