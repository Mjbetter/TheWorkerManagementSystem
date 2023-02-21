#include "employee.h"

OrdinaryEmployees::OrdinaryEmployees(int id, string name, int job) {
	this->worker_id = id;
	this->worker_name = name;
	this->worker_job = job;
}
string OrdinaryEmployees::get_job() {
	return "普通员工";
}
void OrdinaryEmployees::showInfo() {
	std::cout << "职工编号：" << this->worker_id
		<< "\t职工姓名：" << this->worker_name
		<< "\t岗位：" << this->get_job()
		<< "\t岗位职责：完成经理交给的任务" << std::endl;
}
