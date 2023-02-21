#pragma
#include "workManager.h"

using namespace std;

int main() {
	WorkManager wm;
	while (1) {
		wm.show_menu();
		int number = 0;
		while (std::cin >> number) {
			if (!(number >= 0 && number <= 7)) {
				std::cout << "对不起，请重新输入正确的功能序号" << std::endl;
			}
			else break;
		}
		switch (number)
		{
		case 0:
			return 0;
			break;
		case 1:
			wm.Add_Workers();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Delete_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			break;
		}
	}
	return 0;
}