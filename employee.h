#pragma once
#include "worker.h"

using namespace std;

class OrdinaryEmployees :public Worker {
public:
	OrdinaryEmployees(int id, string name, int job);
	virtual string get_job();
	virtual void showInfo();
};