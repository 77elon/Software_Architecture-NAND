#include <iostream> //Standard C++ Header
#include <vector> //Vector List
#include <string> //String class, getline
#include <algorithm> //Find
#include <fstream> //File Stream
#include <stack> //index saving Temporary

#include <stdlib.h>
#include <time.h> //Random index...

#include <chrono>
#include <ctime> //get current system date

#pragma warning(disable:4996)

using namespace std;

class Info
{
public:
	string name, num;
	int rental;
	Info(const string Iname = "", const string Inum = "", const int Irental = 0) // empty input => ""
		:name(Iname), num(Inum), rental(Irental)
	{
		if (Inum == "") //video input == ""
		{
			srand((unsigned)time(NULL));
			int temp = rand() % 1000000; //gen serial number
			num = to_string(temp);
		}

	}
	bool operator== (const Info& o1)
	{
		if (o1.num != "") //�����ϴ� �����͸� ������� ���ϰ� ��.
		{
			return o1.num == num;
		}
		else if (o1.name != "")
		{
			return o1.name == name;
		}
		else
		{
			return o1.rental == rental;
		}
	}
	template <class T>
	void operator =(const T& o1) //R_Info
	{
		if (num == "") // User Info, video�� �����ڸ� ������ serial ���� �����Ǳ⿡...
		{
			name = o1.u_name; //usage (Info) = (R_Info)
			num = o1.u_num;
		}
		else
		{
			name = o1.v_name;
			num = o1.v_num;
		}
	}
};

class R_Info
{
public:
	string v_name, v_num, u_name, u_num, rental_date, return_date;

	R_Info(const string Iv_name = "", const string Iv_num = "", const string Iu_name = "", const string Iu_num = "", const string Irental_date = "", string Ireturn_date ="")
		:v_name(Iv_name), v_num(Iv_num), u_name(Iu_name), u_num(Iu_num), rental_date(Irental_date), return_date(Ireturn_date)
	{
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[11];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, 11, "%Y-%m-%d", timeinfo); //size = 10 + \0 => 11
		string str(buffer);
		rental_date = str;
	}
	void operator =(const Info& o1)
	{
		if (o1.num.length() > 6) // User Info, num�� 6�ڸ��� ���� �ʱ⿡...
		{
			u_name = o1.name; //usage (R_Info) = (Info)
			u_num = o1.num;
		}
		else
		{
			v_name = o1.name;
			v_num = o1.num;
		}
	}
	bool operator== (const R_Info& o1) //object compare
	{
		if (o1.v_name != "")
		{
			return o1.v_name == v_name;
		}
		else if (o1.v_num != "")
		{
			return o1.v_num == v_num;
		}
		else if (o1.u_name != "")
		{
			return o1.u_name == u_name;
		}
		else if (o1.u_num != "")
		{
			return o1.u_num == u_num;
		}
		else if (o1.return_date != "")
		{
			return o1.return_date == return_date;
		}
		else
		{
			return o1.rental_date == rental_date; //auto generated 
		}
	}
};

bool name_check(Info c1, Info c2)
{
	return c1.name < c2.name;
}

void v_frame()
{
	system("cls");
	cout << "����";
	cout.width(15);
	cout << "���� �̸� ";
	cout.width(6);
	cout << "������ȣ ";
	cout.width(6);
	cout << "�뿩 ����" << endl;;
}

void u_frame()
{
	system("cls");
	cout << "����";
	cout.width(10);
	cout << "�̸� ";
	cout.width(13);
	cout << "��ȭ��ȣ ";
	cout.width(15);
	cout << "�뿩 ���� " << endl;
}

void r_frame()
{
	system("cls");
	cout << "����";
	cout.width(10);
	cout << "�̸� ";
	cout.width(13);
	cout << "��ȭ��ȣ ";
	cout.width(15);
	cout << "���� �̸�";
	cout.width(9);
	cout << "������ȣ";
	cout.width(10);
	cout << "�뿩 ����";
	cout.width(12);
	cout << "�ݳ� ����" << endl;
	//u_name, u_num, v_name, v_num, rental_date, return_date
}

void v_output(vector<Info>& o1, stack<int>& T1)
{
	int count = 0;
	while (!T1.empty())
	{
		cout.width(2);
		cout << ++count;
		cout.width(12);
		cout << o1.at(T1.top()).name;
		cout.width(12);
		cout << o1.at(T1.top()).num;
		cout.width(11);
		if (o1.at(T1.top()).rental == 0) //rental status 0 : �⺻, > 0 : �뿩�� 1~, < 0 : -1�� ��ü, �н��� ����
		{
			cout << "��� ����" << endl;
		}
		else if (o1.at(T1.top()).rental > 0)
		{
			cout << "�뿩 ��" << endl;
		}
		else if (o1.at(T1.top()).rental < 0)
		{
			cout << "��ü/�н�" << endl;
		}
		T1.pop();
	}
}
void u_output(vector<Info>& o1, stack<int>& T1)
{
	int count = 0;
	while (!T1.empty())
	{
		cout.width(3);
		cout << ++count;
		cout.width(11);
		cout << o1.at(T1.top()).name;
		cout.width(15);
		cout << o1.at(T1.top()).num;
		cout.width(12);
		if (o1.at(T1.top()).rental == 0)
		{
			cout << "�⺻����" << endl;
		}
		else if (o1.at(T1.top()).rental > 0)
		{
			cout << "�뿩 ��" << endl;
		}
		else if (o1.at(T1.top()).rental < 0)
		{
			cout << "��ü/�н�" << endl;
		}
		T1.pop();
	}
}

void r_output(vector<R_Info>& o1, stack<int>& T1)
{
	int count = 0;
	while (!T1.empty())
	{
		cout.width(3);
		cout << ++count;
		cout.width(11);
		cout << o1.at(T1.top()).u_name;
		cout.width(15);
		cout << o1.at(T1.top()).u_num;
		cout.width(15);
		cout << o1.at(T1.top()).v_name;
		cout.width(15);
		cout << o1.at(T1.top()).v_num;
		cout.width(12);
		cout << o1.at(T1.top()).rental_date;
		cout.width(12);
		cout << o1.at(T1.top()).return_date << endl;
		T1.pop();
	}
}

void auto_fileload(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3)
{
	ifstream v_ifs, u_ifs, r_ifs;
	v_ifs.open("VideoList.txt");
	u_ifs.open("UserList.txt");
	r_ifs.open("RentalList.txt");
	if (v_ifs.is_open() && u_ifs.is_open() && r_ifs.is_open()) //��� ������ �ε� �Ǿ��ٸ�?
	{
		cout << "������ ��� ���������� �ҷ��Խ��ϴ�. " << endl;
		Info T1, T2;
		R_Info T3;
		while (v_ifs >> T1.name >> T1.num >> T1.rental)
		{
			o1.push_back(T1);
		}
		while (u_ifs >> T2.name >> T2.num >> T2.rental)
		{
			o2.push_back(T2);
		}
		while (r_ifs >> T3.u_name >> T3.u_num >> T3.v_name >> T3.v_num >> T3.rental_date >> T3.return_date)
		{
			o3.push_back(T3);
		}
		cout << "����Ʈ�� ��� �ҷ��Խ��ϴ�. ���õ� ���� �Ϸ� �Ǽ���~ " << endl;
	}
	else
	{
		cout << "����� List�� �ҷ����� ���߽��ϴ�. " << endl;
		cout << "List�� ���� �԰��� ������ �����ϴ�." << endl;
		cout << "VideoList.txt, UserList.txt, RentalList.txt" << endl;
	}

	v_ifs.close();
	u_ifs.close();
	r_ifs.close();
}


void auto_filesave(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3)
{
	system("cls"); //clear console

	ofstream v_ofs, u_ofs, r_ofs;
	v_ofs.open("VideoList.txt");
	u_ofs.open("UserList.txt");
	r_ofs.open("RentalList.txt");
	vector<Info>::reverse_iterator v_iter, u_iter; //�������� ����..., ���� ������ �ǵ����⿡�� ������ �� ���� �ʿ��ϱ⿡
	vector<R_Info>::reverse_iterator r_iter;
	if (!o1.empty())
	{
		for (v_iter = o1.rbegin(); v_iter != o1.rend(); v_iter++)
		{
			v_ofs << o1.at(v_iter - o1.rbegin()).name << " " << o1.at(v_iter - o1.rbegin()).num << " " << o1.at(v_iter - o1.rbegin()).rental << " " << "\n";
		}
		cout << "VideoList�� �������Դϴ�..." << endl;
	}
	if (!o2.empty())
	{
		for (u_iter = o2.rbegin(); u_iter != o2.rend(); u_iter++)
		{
			u_ofs << o2.at(u_iter - o2.rbegin()).name << " " << o2.at(u_iter - o2.rbegin()).num << " " << o2.at(u_iter - o2.rbegin()).rental << " " << "\n";
		}
		cout << "UserList�� �������Դϴ�..." << endl;
	}
	if (!o3.empty())
	{
		for (r_iter = o3.rbegin(); r_iter != o3.rend(); r_iter++)
		{
			r_ofs << o3.at(r_iter - o3.rbegin()).u_name << " " << o3.at(r_iter - o3.rbegin()).u_num << " " << o3.at(r_iter - o3.rbegin()).v_name << " " << o3.at(r_iter - o3.rbegin()).v_num << " " << o3.at(r_iter - o3.rbegin()).rental_date << " " << o3.at(r_iter - o3.rbegin()).return_date << " " << "\n";
		}
		cout << "RentalList�� �������Դϴ�..." << endl;
	}
	cout << "��� �����۾��� ����Ǿ����ϴ�." << endl;
	v_ofs.close(); //Fileoutput Stream close!!
	u_ofs.close();
	r_ofs.close();
}

void v_add(vector<Info>& o1)
{
	system("cls");
	Info T1;
	cout << "���� ������ �߰��մϴ�. " << endl;
	cout << "�߰��Ͻ� ���� �̸��� �Է����ּ���." << endl;
	cin >> T1.name;
	o1.push_back(T1);
	if (o1.size() != 1) //1��° ������ �ƴ϶�� ����ó��
	{
		sort(o1.begin(), o1.end(), name_check); // name sorting
	}

}

void u_add(vector<Info>& o1)
{
	system("cls");
	Info T1;
	cout << "����� ������ �߰��մϴ�. " << endl;
	cout << "�߰��Ͻ� ����� �̸��� �Է����ּ���." << endl;
	cin >> T1.name;
	cout << "������� �޴��� ��ȣ�� �Է����ּ���." << endl;
	cin >> T1.num;
	if (T1.num.length() == 11) //������ üũ
	{
		T1.num.insert(3, "-");
		T1.num.insert(8, "-");
	}
	o1.push_back(T1);
	if (o1.size() != 1) //1��° ������ �ƴ϶�� ����ó��
	{
		sort(o1.begin(), o1.end(), name_check); // name sorting
	}

}
template <class T>
void vu_search(vector<T>& o1, T& T1, stack<int>& T2)
{
	auto it = find(o1.begin(), o1.end(), T1);	//index find!!
	while (true)
	{
		it = find(it, o1.end(), T1); //�� �� ��ġ find but,,, stack�� �����ϱ� ����
		if (it != o1.end())
		{
			T2.push(it - o1.begin());
			++it;
		}
		else
		{
			break;
		}
	}
}

void r_search(vector<R_Info>& o1, R_Info& T1, stack<int>& T2) //R_Info ����Ʈ�� �������� �ٷ�ٺ���,��� vu_search�� �ۼ��Ǿ� �ִ� 
{
	vu_search(o1, T1, T2);
}

void v_search(vector<Info>& o1)
{
	system("cls");
	if (o1.empty())
	{
		cout << "���� ����Ʈ�� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		stack<int> t_index;
		int check = 0;
		cout << "�˻��Ͻ� ������ �����ΰ���? (1 : �̸�, 2 : �뿩 ����)" << endl;
		cin >> check;

		if (check == 1)
		{
			cout << "�̸��� �Է����ּ���" << endl;
			cin >> object1.name;
			object1.num = ""; // algorithm...
			vu_search(o1, object1, t_index);
			cout << "�˻��� ������ ������ �����ϴ�. " << endl;
			v_frame(); // frame output
			v_output(o1, t_index); //video, user search result output
			system("pause");
		}
		else if (check == 2)
		{
			cout << "�뿩 ������ �Է����ּ��� (-1 : ��ü/�н�, 0 : ��� ����, 1 : �뿩 ��)" << endl;
			cin >> object1.rental;
			object1.num = ""; // algorithm...
			vu_search(o1, object1, t_index);
			cout << "�˻��� ������ ������ �����ϴ�. " << endl;
			v_frame(); // frame output
			v_output(o1, t_index); //video search result output
			system("pause");
		}
		else
		{
			cout << "�ٽ� �Է����ּ���" << endl;
		}
	}
}

void u_search(vector<Info>& o1)
{
	system("cls");
	if (o1.empty())
	{
		cout << "����� ����Ʈ�� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		stack<int> t_index;
		int check = 0;
		cout << "�˻��Ͻ� ������ �����ΰ���? (1 : �̸�, 2 : ��ȭ��ȣ, 3 : �뿩 ����)" << endl;
		cin >> check;

		if (check == 1)
		{
			cout << "�̸��� �Է����ּ���" << endl;
			cin >> object1.name;
			object1.num = ""; // algorithm...
			vu_search(o1, object1, t_index);
			cout << "�˻��� ������ ������ �����ϴ�. " << endl;
			u_frame(); // frame output
			u_output(o1, t_index); //video, user search result output
			system("pause");
		}
		else if (check == 2)
		{
			cout << "��ȭ��ȣ�� �Է����ּ��� (������ ���� ����)" << endl;
			cin >> object1.num;
			if (object1.num.length() == 11)
			{
				object1.num.insert(3, "-");
				object1.num.insert(8, "-");
			}
			vu_search(o1, object1, t_index);
			cout << "�˻��� ������ ������ �����ϴ�. " << endl;
			u_frame(); // frame output
			u_output(o1, t_index); //video search result output
			system("pause");
		}
		else if (check == 3)
		{
			cout << "�뿩 ������ �Է����ּ��� (-1 : ��ü/�н�, 0 : ��� ����, n : �뿩 ���� ����� ��)" << endl;
			cin >> object1.rental;
			object1.num = ""; // algorithm...
			vu_search(o1, object1, t_index);
			cout << "�˻��� ������ ������ �����ϴ�. " << endl;
			u_frame(); // frame output
			u_output(o1, t_index); //video search result output
			system("pause");
		}
		else
		{
			cout << "�ٽ� �Է����ּ���" << endl;
			system("pause");
		}

	}
}

void v_edit(vector<Info>& o1) 
{
	system("cls");
	if (o1.empty())
	{
		cout << "���� ����� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		int check = 0;
		int index = 0;

		stack<int> t_index, t_index1;
		cout << "�����Ͻ� ���� �̸��� �Է����ּ���." << endl;
		cin >> object1.name;
		object1.num = ""; // random index clear
		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index; // stack issue.. stack�� ����ϸ� �� ���.
		if (t_index.size() > 1)
		{
			v_frame();
			v_output(o1, t_index1);
			cout << "�߰ߵ� ������ 2�� �̻��Դϴ�. �����Ͻ� ������ �������ּ���. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else if (t_index.size() < 1)
		{
			cout << "�ش� ���ǰ� ��ġ�ϴ� ������ �߰ߵ��� �ʾҽ��ϴ�." << endl;
			system("pause");
			return;
		}
		else
		{
			index = t_index.top();
		}
		if (o1.at(index).rental)
		{
			cout << "����ڰ� �뿩 ���Դϴ�. �ݳ� �� �õ� �� �ּ���." << endl;
			system("pause");
			return;
		}
		//Video List Index�� ������� R_Info�� ����Ʈ�� ����(operator ������), ��Ż ����Ʈ�� ���� �̸� ����
		cout << "�����Ͻ� �̸��� �Է����ּ��� " << endl;
		cin >> o1.at(index).name;
		cout << "�̸� ������ �Ϸ�Ǿ����ϴ�." << endl;
		sort(o1.begin(), o1.end(), name_check);
	}
}

void u_edit(vector<Info>& o1) 
{
	system("cls");
	if (o1.empty())
	{
		cout << "����� ����� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		int check = 0;
		int index = 0;
		stack<int> t_index, t_index1;
		int u_check = 0;
		cout << "�����Ͻ� ����� �̸��� �Է����ּ���." << endl;
		cin >> object1.name;
		object1.num = ""; // random index clear
		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index; // stack issue.. stack�� ����ϸ� �� ���.
		if (t_index.size() > 1)
		{
			u_frame();
			u_output(o1, t_index1);
			cout << "�߰ߵ� ����ڰ� 2�� �̻��Դϴ�. �����Ͻ� ����ڸ� ��ȣ�� �������ּ���. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else if (t_index.size() < 1)
		{
			cout << "�ش� ���ǰ� ��ġ�ϴ� ����ڰ� �߰ߵ��� �ʾҽ��ϴ�." << endl;
			system("pause");
			return;
		}
		else
		{
			index = t_index.top();
		}
		if (o1.at(index).rental)
		{
			cout << "����ڰ� �뿩 ���Դϴ�. �ݳ� �� �õ� �� �ּ���." << endl;
			system("pause");
			return;
		}
		cout << "�����Ͻ� �����͸� �������ּ��� (1: �̸�, 2: ��ȭ��ȣ)" << endl;
		cin >> u_check;
		if (u_check == 1)
		{
			//User List Index�� ������� R_Info�� ����Ʈ�� ����(operator ������), ��Ż ����Ʈ�� ����� �̸� ����
			cout << "�����Ͻ� �̸��� �Է����ּ��� " << endl;
			cin >> o1.at(index).name;
			cout << "�̸� ������ �Ϸ�Ǿ����ϴ�." << endl;
		}
		else if (u_check == 2)
		{
			//User List Index�� ������� R_Info�� ����Ʈ�� ����(operator ������), ��Ż ����Ʈ�� ����� ��ȣ ����
			cout << "�����Ͻ� ��ȭ��ȣ�� �Է����ּ��� " << endl;
			cin >> o1.at(index).num;
			cout << "��ȣ ������ �Ϸ�Ǿ����ϴ�." << endl;
		}
		sort(o1.begin(), o1.end(), name_check);
	}
}

void v_erase(vector<Info>& o1, vector<R_Info>& o3)
{
	system("cls");
	if (o1.empty())
	{
		cout << "���� ����� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		int check = 0;
		int index = 0;
		stack<int> t_index, t_index1;
		cout << "�����Ͻ� ���� �̸��� �Է����ּ���." << endl;
		cin >> object1.name;
		object1.num = ""; // random index clear
		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index; // stack issue.. stack�� ����ϸ� �� ���.
		if (t_index.size() > 1)
		{
			v_frame();
			v_output(o1, t_index1);
			cout << "�߰ߵ� ������ 2�� �̻��Դϴ�. �����Ͻ� ������ �������ּ���. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else if (t_index.size() < 1)
		{
			cout << "�ش� ���ǰ� ��ġ�ϴ� ������ �߰ߵ��� �ʾҽ��ϴ�." << endl;
			system("pause");
			return;
		}
		else
		{
			index = t_index.top();
		}
		if (o1.at(index).rental)
		{
			cout << "������ �뿩 ���Դϴ�. �ݳ� �� �õ� �� �ּ���." << endl;
			system("pause");
			return;
		}
		cout << "���� ���Ű� �Ϸ�Ǿ����ϴ�." << endl;
		o1.erase(o1.begin() + index);
		sort(o1.begin(), o1.end(), name_check);
	}
}

void u_erase(vector<Info>& o1, vector<R_Info>& o3) 
{
	system("cls");
	if (o1.empty())
	{
		cout << "����� ����� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		int check = 0;
		int index = 0;
		stack<int> t_index, t_index1;
		int u_check = 0;
		cout << "�����Ͻ� ����� �̸��� �Է����ּ���." << endl;
		cin >> object1.name;
		object1.num = ""; // random index clear
		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index; // stack issue.. stack�� ����ϸ� �� ���.
		if (t_index.size() > 1)
		{
			u_frame();
			u_output(o1, t_index1);
			cout << "�߰ߵ� ����ڰ� 2�� �̻��Դϴ�. �����Ͻ� ����ڸ� ��ȣ�� �������ּ���. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else if (t_index.size() < 1)
		{
			cout << "�ش� ���ǰ� ��ġ�ϴ� ����ڰ� �߰ߵ��� �ʾҽ��ϴ�." << endl;
			system("pause");
			return;
		}
		else
		{
			index = t_index.top();
		}
		if (o1.at(index).rental) // 0 <, 0, > 0
		{
			cout << "����ڰ� �뿩 ���Դϴ�. �ݳ� �� �õ� �� �ּ���." << endl;
			system("pause");
			return;
		}
		cout << "����� ���Ű� �Ϸ�Ǿ����ϴ�." << endl;
		o1.erase(o1.begin() + index);
		sort(o1.begin(), o1.end(), name_check);
	}
}

void av_output(vector<Info>& o1, vector<R_Info>& o3)
{
	system("cls"); //clear console
	if (!o1.empty())
	{
		cout << "��ü ���� ����� ����մϴ�." << endl;

		int count = 0;
		v_frame();
		for (const auto& iter : o1) //value_type iterator
		{
			cout.width(2);
			cout << ++count;
			cout.width(12);
			cout << iter.name;
			cout.width(12);
			cout << iter.num;
			cout.width(11);
			if (iter.rental == 0)
			{
				cout << "��� ����" << endl;
			}
			else if (iter.rental > 0)
			{
				cout << "�뿩 ��" << endl;
			}
			else if (iter.rental < 0)
			{
				cout << "��ü/�н�" << endl;
			}
		}
	}
	else
	{
		cout << "��ϵ� ��ȭ��ȣ�� �����ϴ�." << endl;
		return;
	}
	cout << "���� ���� List���� " << o1.size() << "���� ������ ������,";
	cout << "�뿩 ���� ������ " << o3.size() << "���� �ֽ��ϴ�." << endl;
	system("pause");
}
void au_output(vector<Info>& o1, vector<R_Info>& o3)
{
	system("cls"); //clear console
	if (!o1.empty())
	{
		cout << "��ü ����� ����� ����մϴ�." << endl;

		int count = 0;
		u_frame();
		for (const auto& iter : o1) //value_type iterator
		{
			cout.width(3);
			cout << ++count;
			cout.width(11);
			cout << iter.name;
			cout.width(15);
			cout << iter.num;
			cout.width(12);
			if (iter.rental == 0)
			{
				cout << "�⺻����" << endl;
			}
			else if (iter.rental > 0)
			{
				cout << "�뿩 ��" << endl;
			}
			else if (iter.rental < 0)
			{
				cout << "��ü/�н�" << endl;
			}
		}
	}
	else
	{
		cout << "��ϵ� ����ڰ� �����ϴ�." << endl;
		return;
	}
	cout << "���� ����� List���� " << o1.size() << "���� ����ڰ� ������,";
	cout << "�뿩 ���� ������ " << o3.size() << "���� �ֽ��ϴ�." << endl;
	system("pause");
}

void ar_output(vector<R_Info>& o3)
{
	system("cls"); //clear console
	if (!o3.empty())
	{
		cout << "�뿩 ����� ����մϴ�." << endl;

		int count = 0;
		r_frame();
		//u_name, u_num, v_name, v_num, rental_date
		for (const auto& iter : o3) //value_type iterator
		{
			cout.width(3);
			cout << ++count;
			cout.width(11);
			cout << iter.u_name;
			cout.width(15);
			cout << iter.u_num;
			cout.width(11);
			cout << iter.v_name;
			cout.width(10);
			cout << iter.v_num;
			cout.width(12);
			cout << iter.rental_date;
			cout.width(12);
			cout << iter.return_date << endl;
		}
	}
	else
	{
		cout << "�뿩 ���� ������ �����ϴ�." << endl;
		return;
	}
	cout << "�뿩 ���� ������ " << o3.size() << "���� �ֽ��ϴ�." << endl;
}

void v_rental(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3)
{
	system("cls");
	if (o1.empty())
	{
		cout << "���� ����� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1, object2;
		R_Info object3; //Rental List Type Object
		int check = 0;
		int index = 0, index1 = 0; // video, user index
		stack<int> t_index, t_index1, t_index2, t_index3; // video index, copy of video index, user index, copy of...
		object1.num = ""; // random index clear
		object2.num = "";

		cout << "�뿩�Ͻ� ���� �̸��� �Է����ּ���." << endl;
		cin >> object1.name;

		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index;
		if (t_index1.size() == 0)
		{
			cout << "�ش� ���ǰ� ��ġ�ϴ� ������ �߰ߵ��� �ʾҽ��ϴ�." << endl;
			system("pause");
			return;
		}
		else if (t_index1.size() > 1)
		{
			v_frame();
			v_output(o1, t_index1);
			cout << "�߰ߵ� ������ 2�� �̻��Դϴ�. �뿩�Ͻ� ������ �������ּ���. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else
		{
			index = t_index1.top();
		}
		cout << "�뿩�� �̸��� �Է����ּ���." << endl;
		cin >> object2.name;
		vu_search(o2, object2, t_index2); //find user index
		t_index3 = t_index2;
		if (t_index2.size() == 0)
		{
			cout << "�ش� ���ǰ� ��ġ�ϴ� ����ڰ� �����ϴ�." << endl;
			system("pause");
			return;
		}
		else if (t_index2.size() > 1)
		{
			u_frame();
			u_output(o2, t_index3);
			cout << "�߰ߵ� ����ڰ� 2�� �̻��Դϴ�. �뿩�ڸ� ��ȣ�� �������ּ���. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index2.pop();
			}
		}
		cout << "�ݳ� ���� �Է����ּ���. ex)2020-11-01" << endl;
		cin >> object3.return_date;


		index1 = t_index2.top();
		o1.at(index).rental = 1; //video Only one at same time
		o2.at(index1).rental++; //user rental status
		object3 = o2.at(index1);
		object3 = o1.at(index); //copy of user, video data
		o3.push_back(object3);

		cout << "���� �뿩ó���� �Ϸ�Ǿ����ϴ�." << endl;
		system("pause");
	}
}
void v_return(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3)
{
	system("cls");
	if (o3.empty())
	{
		cout << "�뿩 ����� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		ar_output(o3);
		R_Info object1; //Rental List Type Object
		Info object2, object3; // Video user Type object
		object1.rental_date = ""; //erase auto generated data
		object3.num = "";
		int check = 0;
		int index = 0; // Rental List
		int v_index = 0, u_index = 0;
		stack<int> t_index, t_index1; // video index, copy of video index, user index, copy of...
		stack<int> t_index2;
		stack<int> t_index4;
		cout << "�ݳ��Ͻ� ���� �̸��� �Է����ּ���." << endl;
		cin >> object1.v_name;

		r_search(o3, object1, t_index); //saving index
		t_index1 = t_index;
		//R_Info indexing...
		if (t_index1.size() == 0)
		{
			cout << "�ش� ���ǰ� ��ġ�ϴ� ������ �߰ߵ��� �ʾҽ��ϴ�." << endl;
			system("pause");
			return;
		}
		else if (t_index1.size() > 1)
		{
			r_frame();
			r_output(o3, t_index1); //need double stack...
			cout << "�߰ߵ� ������ 2�� �̻��Դϴ�. �ݳ��Ͻ� ������ �������ּ���. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else
		{
			index = t_index1.top();
		}

		//object2 == video, object3 == user
		//video rental info reset
		object2 = o3.at(index); //copy of vid, user info
		object3 = o3.at(index);
		o3.erase(o3.begin() + index); //rental list erase

		vu_search(o1, object2, t_index2); //index saving to t_index2
		v_index = t_index2.top();
		vu_search(o2, object3, t_index4); //index saving to t_index4
		u_index = t_index4.top();
		o1.at(v_index).rental = 0; //video Only one at same time
		o2.at(u_index).rental--; //user rental status

		cout << "���� �ݳ�ó���� �Ϸ�Ǿ����ϴ�." << endl;
		system("pause");
	}
}

void v_menu(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3) //function for videodata access
{
	int check = 0;
	while (true)
	{
		system("cls");
		cout << "���� �����͸� �����մϴ�." << endl;
		cout << "1. �߰�, 2. �˻�, 3. ����, 4. ����, 5. ���, 6. �뿩, 7. �ݳ�, 8. ���� ������ �̵�" << endl;
		cout << "��� >> ";
		cin >> check;
		switch (check)
		{
		case 1:
			v_add(o1);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 2:
			v_search(o1);
			break;
		case 3:
			v_edit(o1);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 4:
			v_erase(o1, o3);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 5:
			av_output(o1, o3);
			break;
		case 6:
			v_rental(o1, o2, o3);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 7:
			v_return(o1, o2, o3);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 8:
			cout << "���� ���� �Լ��� �����մϴ�." << endl;
			return;
		default:
			cout << "�ٽ� �Է����ּ���!" << endl;
			continue;
		}
	}
}

void u_menu(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3) //function for userdata access
{
	int check = 0;
	while (true)
	{
		system("cls");
		cout << "����� �����͸� �����մϴ�." << endl;
		cout << "1. �߰�, 2. �˻�, 3. ����, 4. ����, 5. ���, 6. �뿩, 7. �ݳ�, 8. ���� ������ �̵�" << endl;
		cout << "��� >> ";
		cin >> check;
		switch (check)
		{
		case 1:
			u_add(o2);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 2:
			u_search(o2);
			break;
		case 3:
			u_edit(o2);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 4:
			u_erase(o2, o3);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 5:
			au_output(o2, o3);
			break;
		case 6:
			v_rental(o1, o2, o3);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 7:
			v_return(o1, o2, o3);
			auto_filesave(o1, o2, o3);//auto saving function
			break;
		case 8:
			cout << "����� ���� �Լ��� �����մϴ�." << endl;
			return;
		default:
			cout << "�ٽ� �Է����ּ���!" << endl;
			continue;
		}
	}
}

void menu(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3) //using data selection....
{
	int check = 0;
	while (true) // 1 or 2�ϰ�� ���� �Լ��� ����
	{
		system("cls");
		cout << "�����ϰ� ���� �����͸� ������ (1 : ���� ������, 2 : ����� ������, 3 : �뿩��� ���, 4 : ���α׷� ����)" << endl;
		cout << "��� >> ";
		cin >> check;
		if (check != 1 && check != 2 && check != 3 && check != 4)
		{
			system("cls");
			cout << "�ٽ� �Է����ּ���" << endl;
		}
		else if (check == 1)
		{
			v_menu(o1, o2, o3);
		}
		else if (check == 2)
		{
			u_menu(o1, o2, o3);
		}
		else if (check == 3)
		{
			ar_output(o3);
			system("pause");
		}
		else if (check == 4)
		{
			exit(0);
		}
	}
}

int main()
{
	vector<Info> videodata;
	vector<Info> userdata;
	vector<R_Info> rentaldata;
	auto_fileload(videodata, userdata, rentaldata); //auto file loading function
	menu(videodata, userdata, rentaldata); //���� ��� �Լ� ����
}