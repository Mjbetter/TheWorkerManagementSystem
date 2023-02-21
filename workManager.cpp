#include "workManager.h"

bool  cmp1(Worker* worker1, Worker* worker2) {
	return worker1->worker_id < worker2->worker_id;
}
bool  cmp2(Worker* worker1, Worker* worker2) {
	return worker1->worker_id > worker2->worker_id;
}

WorkManager::WorkManager() {
	//�ļ�������ʱ����ʼ������
	ifstream ifs(FILENAME, ios::in);
	if (!(ifs.is_open())) {
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڵ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڲ��Ҵ�������
	this->m_EmpNum = this->get_EmpNum();
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum*sizeof(Worker)];
	//���ļ��е����ݣ��浽������
	this->init_Emp();
}

void WorkManager::show_menu() {
	std::cout << "---------------------" << std::endl;
	std::cout << "0���˳��������" << std::endl;
	std::cout << "1������ְ����Ϣ" << std::endl;
	std::cout << "2����ʾְ����Ϣ" << std::endl;
	std::cout << "3��ɾ����ְְ��" << std::endl;
	std::cout << "4���޸�ְ����Ϣ" << std::endl;
	std::cout << "5������ְ����Ϣ" << std::endl;
	std::cout << "6�����ձ������" << std::endl;
	std::cout << "7����������ĵ�" << std::endl;
	std::cout << "---------------------" << std::endl << std::endl;
	std::cout << "��������Ҫʹ�õĹ������" << std::endl;
}

void WorkManager::Add_Workers() {
	system("cls");
	std::cout << "��������Ҫ���ӵ�ְ��������:" << std::endl;
	int numbers = 0;//�����û����������
	while (std::cin >> numbers) {
		if (numbers < 0) {
			std::cout << "�������������Ϊ���������������룺" << endl;
		}
		else {
			//��������ӿռ��С
			int newSize = this->m_EmpNum + numbers;
			//�����¿ռ�
			Worker** newSpace = new Worker * [newSize*sizeof(Worker)];
			//��ԭ���ռ��µ����ݿ������¿ռ���
			if (this->m_EmpArray != NULL) {
				for (int i = 0; i < this->m_EmpNum; i++) {
					newSpace[i] = this->m_EmpArray[i];
				}
			}
			//���������
			for (int i = 0; i < numbers; i++) {
				int id;//ְ�����
				string name;//ְ������
				int dSelect;//����ѡ��
				std::cout << "�������" << i + 1 << "����ְ���ı��:" << std::endl;
				std::cin >> id;
				while (this->isExitEmp(id) == -1) {
					std::cout << "��ְ������Ѵ��ڣ�����������:" << std::endl;
					std::cin >> id;
				}
				std::cout << "�������" << i + 1 << "����ְ��������:" << std::endl;
				std::cin >> name;
				std::cout << "��ѡ���" << i + 1 << "����ְ���Ĳ���:" << std::endl;
				std::cout << "1����ְͨ��" << std::endl;
				std::cout << "2������" << std::endl;
				std::cout << "3���ϰ�" << std::endl;
				std::cin >> dSelect;
				Worker* worker = NULL;
				switch (dSelect) {
				case 1:
					worker = new OrdinaryEmployees(id, name, dSelect);
					break;
				case 2:
					worker = new Manager(id, name, dSelect);
					break;
				case 3:
					worker = new Boss(id, name, dSelect);
					break;
				default:
					break;
				}
				//������ְ��ְ�𣬱��浽������
				newSpace[this->m_EmpNum + i] = worker;
			}
			//�ͷ�ԭ�пռ�
			delete[] this->m_EmpArray;
			//�����¿ռ��ָ��
			this->m_EmpArray = newSpace;
			//�����µ�ְ������
			this->m_EmpNum = newSize;
			//�����ļ���Ϊ��
			this->m_FileIsEmpty = false;
			//��ʾ
			std::cout << "�ɹ����" << numbers << "����Ա" << std::endl;
			this->save();
			break;
		}
	}
	system("pause");
	system("cls");
}

int WorkManager::get_EmpNum() {
	ifstream ifs(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		//ͳ������
		num++;
	}
	return num;
}

void WorkManager::init_Emp() {
	ifstream ifs(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;
		if (did == 1) {
			worker = new OrdinaryEmployees(id, name, did);
		}
		if (did == 2) {
			worker = new Manager(id, name, did);
		}
		if (did == 3) {
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index++] = worker;
	}
	ifs.close();
}

void WorkManager::save() {
	ofstream ofs(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->worker_id << " "
			<< this->m_EmpArray[i]->worker_name << " "
			<< this->m_EmpArray[i]->worker_job << " " << endl;
	}
	ofs.close();
}

void WorkManager::Show_Emp() {
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty) {
		std::cout << "�ļ������ڻ��߼�¼Ϊ��" << std::endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Delete_Emp() {
	if (this->m_FileIsEmpty) {
		return;
	}
	else {
		//������Ҫɾ����ְ���ı��
		int id;
		std::cout << "������Ҫɾ����ְ���ı��:" << std::endl;
		std::cin >> id;
		int judge = this->isExitEmp(id);
		if (judge == 0) {
			std::cout << "ɾ��ʧ�ܣ�û���ҵ����ְ��" << std::endl;
			return;
		}
		else {
			for (int i = 0; i < this->m_EmpNum-1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			std::cout << "ɾ���ɹ�" << std::endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkManager::isExitEmp(int id) {
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->worker_id == id) {
			return 1;
		}
	}
	return 0;
}

void WorkManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		std::cout << "�ļ������ڻ�Ϊ�գ�" << std::endl;
	}
	else {
		int id=-1;
		std::cout << "������Ҫ�޸ĵ�ְ����ID" << std::endl;
		std::cin >> id;
		int ret = this->isExitEmp(id);
		if (ret != -1) {
			//ɾ��ԭ��ְ������Ϣ
			delete this->m_EmpArray[ret];
			//¼���ְ���µ���Ϣ
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			std::cout << "�鵽��" << id << "��ְ��,�������µ�ְ����ţ�" << std::endl;
			std::cin >> newId;
			while (this->isExitEmp(newId) == 1) {
				std::cout << "��Ա������Ѵ��ڣ�����������:" << std::endl;
				std::cin >> newId;
			}
			std::cout << "�鵽��" << id << "��ְ�����������µ�ְ������:" << std::endl;
			std::cin >> newName;
			std::cout << "�鵽��" << id << "��ְ�����������µ�ְ����λ:" << std::endl;
			std::cout << "1����ͨԱ��" << std::endl;
			std::cout << "2������" << std::endl;
			std::cout << "3���ϰ�" << std::endl;
			std::cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new OrdinaryEmployees(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//�������ݵ�������
			this->m_EmpArray[ret] = worker;
			std::cout << "�޸ĳɹ�" << std::endl;
			//���浽�ļ���
			this->save();
		}
		else {
			std::cout << "���޴���" << std::endl;		
		}
	}
	system("pause");
	system("cls");
}
void WorkManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		std::cout << "�ļ������ڻ���Ϊ��!" << endl;
	}
	else {
		std::cout << "��������ҵķ������߷�ʽ" << std::endl;
		std::cout << "1.����ְ���ı�Ų���" << std::endl;
		std::cout << "2.����ְ������������" << std::endl;
		int dSelect = 0;
		while (1) {
			std::cin >> dSelect;
			if (dSelect == 1 || dSelect == 2) break;
			std::cout << "�������Ŵ���������������:" << std::endl;
		}
		if (dSelect == 1) {
			//���ձ�Ų���
			std::cout << "������Ҫ��ѯ�ı��:" << std::endl;
			int id = -1;
			std::cin >> id;
			while (this->isExitEmp(id)==0) {
				std::cout << "�ñ�Ų����ڣ�������������:" << std::endl;
				std::cin >> id;
			}
			std::cout << "���ҳɹ�����ְ������Ϣ����:" << std::endl;
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->worker_id == id) {
					this->m_EmpArray[i]->showInfo();
				}
			}

		}
		else if (dSelect == 2) {
			//����ְ��������������
			string name;
			int judge = 0;
			std::cout << "������Ҫ���ҵ�����" << std::endl;
			std::cin >> name;
			for (int i = 0; i < this->m_EmpNum; i++) {
				std::cout << "���ҽ������:" << std::endl;
				if (this->m_EmpArray[i]->worker_name == name) {
					judge++;
					std::cout << "�ҵ����Ϊ" << this->m_EmpArray[i]->worker_id << "��ְ����Ϣ����:" << std::endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (judge == 0) {
				std::cout << "δ�ҵ��κ��������ְ��" << std::endl;
			}
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		std::cout << "�ļ������ڻ���Ϊ��!" << endl;
	}
	else {
		std::cout << "��ѡ����������:" << std::endl;
		std::cout << "1.��ŴӴ�С����" << std::endl;
		std::cout << "2.��Ŵ�С��������" << std::endl;
		int dSelect = 0;
		while (1) {
			std::cin >> dSelect;
			if (dSelect == 1 || dSelect == 2) break;
			std::cout << "�������Ų���ȷ���������������:" << std::endl;
		}
		//����һ��Ŀǰ������
		Worker** temp = this->m_EmpArray;
		if (dSelect == 1) {
			sort(temp, temp + this->m_EmpNum, cmp2);
		}
		else if(dSelect == 2) {
			sort(temp, temp + this->m_EmpNum, cmp1);
		}
		std::cout << "����ɹ����������:" << std::endl;
		for (int i = 0; i < this->m_EmpNum; i++) {
			temp[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Clean_File() {
	if (this->m_FileIsEmpty) {
		std::cout << "�ļ������ڻ���Ϊ��!" << endl;
	}
	else {
		std::cout << "ȷ�������?" << std::endl;
		std::cout << "1.ȷ��" << std::endl;
		std::cout << "2.����" << std::endl;
		int dSelect = 0;
		while (1) {
			std::cin >> dSelect;
			if (dSelect == 1 || dSelect == 2) break;
			std::cout << "�������Ų���ȷ���������������:" << std::endl;
		}
		if (dSelect == 1) {
			ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
			ofs.close();
			if (this->m_EmpArray != NULL) {
				//ɾ��������ÿ��ְ������
				for (int i = 0; i < this->m_EmpNum; i++) {
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
				delete[] this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;
			}
			std::cout << "��ճɹ�" << std::endl;
			system("pause");
			system("cls");
		}
	}
}

WorkManager::~WorkManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}