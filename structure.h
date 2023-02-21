#ifndef _xxxx_
#define _xxxx_
#include <iostream>
#include <string>

using namespace std;

class Worker {
public:
	int worker_id;//ְ��id
	string worker_name;//ְ������
	int worker_job;//���ű��
	//��ø�λְ��
	virtual string get_job() = 0;
	//��ʾ������Ϣ
	virtual void showInfo() = 0;
};

class OrdinaryEmployees :public Worker{
public:
	OrdinaryEmployees(int id, string name, int job) {
		worker_id = id;
		worker_name = name;
		worker_job = job;
	}
	virtual string get_job() {
		return "��ͨԱ��";
	}
	virtual void showInfo() {
		std::cout << "ְ����ţ�" << this->worker_id
			<< "\tְ��������" << this->worker_name
			<< "\t��λ��" << this->get_job()
			<< "\t��λְ����ɾ�����������" << std::endl;
	}
};
class Manager :public Worker {
public:
	Manager(int id, string name, int job) {
		worker_id = id;
		worker_name = name;
		worker_job = job;
	}
	virtual string get_job() {
		return "����";
	}
	virtual void showInfo() {
		std::cout << "ְ����ţ�" << this->worker_id
			<< "\tְ��������" << this->worker_name
			<< "\t��λ��" << this->get_job()
			<< "\t��λְ������ϰ彻�������񣬲��ַ���Ա��" << std::endl;
	}
};
class Boss :public Worker {
public:
	Boss(int id, string name, int job) {
		worker_id = id;
		worker_name = name;
		worker_job = job;
	}
	virtual string get_job() {
		return "�ϰ�";
	}
	virtual void showInfo() {
		std::cout << "ְ����ţ�" << this->worker_id
			<< "\tְ��������" << this->worker_name
			<< "\t��λ��" << this->get_job()
			<< "\t��λְ�𣺸����������񣬷ַ�����" << std::endl;
	}
};
#endif // !1
