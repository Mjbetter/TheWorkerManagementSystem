#include "manager.h"


Manager::Manager(int id, string name, int job) {
	this->worker_id = id;
	this->worker_name = name;
	this->worker_job = job;
}
string Manager::get_job() {
	return "����";
}
void Manager::showInfo() {
	std::cout << "ְ����ţ�" << this->worker_id
		<< "\tְ��������" << this->worker_name
		<< "\t��λ��" << this->get_job()
		<< "\t��λְ������ϰ彻�������񣬲��ַ���Ա��" << std::endl;
}