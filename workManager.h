#pragma
#include <iostream>
#include <fstream>
#include "worker.h"
#include "manager.h"
#include "employee.h"
#include "boss.h"
#include <algorithm>

#define FILENAME "information.txt"
using namespace std;

class WorkManager {
public:
	//���캯��
	WorkManager();
	//չʾ�˵�
	void show_menu();
	//���ְ������
	void Add_Workers();
	//�����ļ�
	void save();
	//ͳ������
	int get_EmpNum();
	//��ʼ��
	void init_Emp();
	//չʾְ����Ϣ
	void Show_Emp();
	//ɾ��ְ��
	void Delete_Emp();
	//�ж�ְ���Ƿ����
	int isExitEmp(int id);
	//�޸�ְ��
	void Mod_Emp();
	//����ְ��
	void Find_Emp();
	//��ְ����Ž�������չʾ
	void Sort_Emp();
	//����ļ�
	void Clean_File();

	//��¼ְ������
	int m_EmpNum;
	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	//ְ��ָ�������ָ��
	Worker** m_EmpArray;
	//��������
	~WorkManager();
};