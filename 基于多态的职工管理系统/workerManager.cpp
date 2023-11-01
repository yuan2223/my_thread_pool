#include "workerManager.h"

//����ʵ�� WorkerManage �Ĺ��캯������������
WorkerManager::WorkerManager()
{
	// �ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in); // ���ļ�
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_Empnum = 0;
		this->EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
	}
	
	//�ļ����� ����û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ�� ��" << endl;
		this->m_Empnum = 0;
		this->EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}	

	//�ļ����ڣ�����¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ: " << num << endl;
	this->m_Empnum = num;

	//���ٿռ�
	this->EmpArray = new Worker * [this->m_Empnum];
	//���ļ��е����ݴ浽������
	this->init_Emp();
	
}

//��ȡ�ļ���ְ������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�  ��
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) //ifs��ÿһ�е�����
	{
		num++;
	}
	return num;
}

//��������
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);  //������ķ�ʽ���ļ� д�ļ�
	for (int i = 0; i < this->m_Empnum; i++)
	{
		ofs << this->EmpArray[i]->m_id << " "
			<< this->EmpArray[i]->m_name << " "
			<< this->EmpArray[i]->m_dept_id << endl;
	}
	//�ر��ļ�
	ofs.close();
}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "****************************************" << endl;
	cout << "**********��ӭʹ��ְ������ϵͳ**********" << endl;
	cout << "************ 0 �˳�������� ************" << endl;
	cout << "************ 1 ����ְ����Ϣ ************" << endl;
	cout << "************ 2 ��ʾְ����Ϣ ************" << endl;
	cout << "************ 3 ɾ����ְ��Ϣ ************" << endl;
	cout << "************ 4 �޸�ְ����Ϣ ************" << endl;
	cout << "************ 5 ����ְ����Ϣ ************" << endl;
	cout << "************ 6 ��������ĵ� ************" << endl;
	cout << "****************************************" << endl;
}
//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

//���ְ��
void WorkerManager::AddEmp()
{
	cout << "���������ְ��������" << endl;
	int add_num = 0;
	cin >> add_num;
	if (add_num > 0)
	{
		//��������¿ռ�Ĵ�С
		int NewSize = this->m_Empnum + add_num; //�¿ռ����� = ԭ�������� + ��������
		
		//���ٿռ�
		Worker** newSpace = new Worker * [NewSize]; //ÿ�����ݵ������� Worker*  

		//��ԭ���ռ��µ����ݿ������¿ռ���
		if (this->EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				newSpace[i] = this->EmpArray[i];
			}
		}
		//���������
		for (int i = 0; i < add_num; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "����Ա���ı��: " << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����Ա��������: " << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ " << endl;
			cin >> dSelect;  //1 2 3

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//��Ա����ָ����Ҫ���浽��������
			newSpace[this->m_Empnum + i] = worker;
		}

		//�ͷ�ԭ���Ŀռ�
		delete[] this->EmpArray;//�ͷ�������Ҫ����[]\

		//�����¿ռ��ָ��
		this->EmpArray = newSpace;

		//����ְ������
		this->m_Empnum = NewSize;

		this->m_FileIsEmpty = false;
		cout << "�ɹ����" << add_num << "����Ա��" << endl;

		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}
	//���������������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

void WorkerManager:: init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else 
		{
			worker = new Boss(id, name, dId);
		}
		this->EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_Empnum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->EmpArray[i]->showInfo(); //��Boss Employee Manager �ж��� showInfo()����
		}
	}
	system("pause");
	system("cls");
}

//ɾ��Ա��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;;
	}
	else
	{
		cout << "������Ҫɾ����ְ�����" << endl;
		int id = 0;
		cin >> id;
		int ret = this->IsExit(id);
		if (ret == -1)
		{
			cout << "ְ��������" << endl;
		}
		else
		{
			for (int i = ret; i < this->m_Empnum - 1; i++)
			{
				this->EmpArray[i] = this->EmpArray[i + 1];
			}
			//������������Ա����
			this->m_Empnum--;
			//���ݸ��µ��ļ�
			this->save();
			cout << "ɾ���ɹ�!" << endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExit(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_Empnum; i++)
	{
		if (id == this->EmpArray[i]->m_id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//�޸���Ϣ
void WorkerManager::Mod_Emp()
{
	//ֱ�Ӹ���m_dept_id����� Ա������Ա��
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫ�޸�ְ���ı��" << endl;
		int ret = 0;
		cin >> ret;
		int index = this->IsExit(ret);
		if (index == -1)
		{
			cout << "��ְ��������" << endl;
		}
		else
		{
			delete this->EmpArray[index];
			int id;
			string name;
			int dSelect;
			cout << "�������µ�id" << endl;
			cin >> id;
			cout << "�������µ�����" << endl;
			cin >> name;
			cout << "�������µĵĸ�λ" << endl;
			cin >> dSelect;

			Worker* worker = NULL; //��������ָ��

			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			}
				
			//�������ݵ�������
			this->EmpArray[index] = worker;
			this->save();
			
			cout << "�޸ĳɹ�" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		int id = 0;
		cout << "������Ҫ���ҵı��" << endl;
		cin >> id;
		int ret = this->IsExit(id);
		if (ret == -1)
		{
			cout << "���޴���" << endl;
		}
		else
		{
			this->EmpArray[ret]->showInfo();
		}
	} 
	system("pause");
	system("cls");
}

//����ļ�
void WorkerManager::Clea_File()
{
	cout << "ȷ����� " << endl;
	cout << "1 ȷ��" << endl;
	cout << " 2 ����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//������� ɾ���ļ������´���
		ofs.close();

		if (this->EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (this->EmpArray[i] != NULL)
				{
					delete this->EmpArray[i];
				}
			}
			this->m_Empnum = 0;
			delete[] this->EmpArray;
			this->EmpArray = NULL;
			this->m_FileIsEmpty = true;

		}
		cout << "����ɹ�" << endl;

	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	//�ֶ��ͷŶ���������
	if (this->EmpArray != NULL)
	{
		for (int i = 0; i < this->m_Empnum; i++)
		{
			if (this->EmpArray[i] != NULL)
			{
				delete this->EmpArray[i];
			}
		}
		delete[] this->EmpArray;
		this->EmpArray = NULL;
	}
}
