#include "employee.h"

OrdinaryEmployees::OrdinaryEmployees(int id, string name, int job) {
	this->worker_id = id;
	this->worker_name = name;
	this->worker_job = job;
}
string OrdinaryEmployees::get_job() {
	return "��ͨԱ��";
}
void OrdinaryEmployees::showInfo() {
	std::cout << "ְ����ţ�" << this->worker_id
		<< "\tְ��������" << this->worker_name
		<< "\t��λ��" << this->get_job()
		<< "\t��λְ����ɾ�����������" << std::endl;
}
