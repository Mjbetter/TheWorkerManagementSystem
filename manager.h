#pragma once
#include "worker.h"
using namespace std;
class Manager :public Worker {
public:
	Manager(int id, string name, int job);
	virtual string get_job();
	virtual void showInfo();
};