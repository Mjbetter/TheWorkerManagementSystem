#pragma once//��ֹͷ�ļ��ظ�����
#include <iostream>
#include <string>

using namespace std;

class Worker {
public:
	int worker_id=0;//ְ��id
	string worker_name;//ְ������
	int worker_job=0;//���ű��
	//��ø�λְ��
	virtual string get_job() = 0;
	//��ʾ������Ϣ
	virtual void showInfo() = 0;
};