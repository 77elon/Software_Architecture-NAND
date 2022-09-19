#include <iostream> //Standard C++ Header
#include <vector> //Vector List
#include <string> //String class, getline
#include <algorithm> //Find
#include <fstream> //File Stream

using namespace std;

class Info
{
public:
	string name, num;
	Info(string Iname = "", string Inum = "")
		:name(Iname), num(Inum)
	{

	}
	bool operator== (const string c1)
	{
		return name == c1;
	}
};

bool name_check(Info c1, Info c2)
{
	return c1.name < c2.name;
}

bool num_check(Info c1, Info c2)
{
	return c1.num < c2.num;
}

template<class T>
void Add_func(vector<T>& o1)
{
	system("cls"); //clear console
	Info Object1;
	string Iname, Inum;
	int sort_check;
	cout << "�����Ͻ� ����� �̸��� �Է��ϼ���!" << endl;
	cin >> Iname;
	cout << "�����Ͻ� ����� ��ȭ��ȣ�� �Է��ϼ���!" << endl;
	cin >> Inum;
	Object1.name = Iname;
	Object1.num = Inum;
	/*if (Object1.num.length() == 12 || Object1.num.length() == 9)
	{
		o1.push_back(Object1);
	}
	else */ //�÷ο���Ʈ��� �ۼ��ϸ� �� �κ��� �ڵ尡 �ۼ��Ǿ�� �ϴµ�, �ǵ��� ���� ������ �ؿ��� �� ���� �߰��ϰڽ��ϴ�.
	if (Object1.num.length() == 11) //��ȭ��ȣ ������ ���� ������ �ۼ�
	{
		cout << "�޴��� ��ȣ�Դϴ�." << endl;
		Object1.num.insert(3, "-");
		Object1.num.insert(8, "-");
	}
	else if (Object1.num.length() == 8)
	{
		cout << "Ư������ ��ȭ��ȣ�Դϴ�." << endl;
		Object1.num.insert(4, "-");
	}
	o1.push_back(Object1); //List�� ��ȭ��ȣ ����
	cout << "��ȭ��ȣ�� ����Ǿ����ϴ�." << endl;
	if (o1.size() != 1)
	{
		cout << "�̸� �� ������ ���Ͻø� 1���� �Է��Ͻð�, ��ȭ��ȣ �� ������ ���Ͻø� 2���� �Է��ϼ���." << endl;
		cin >> sort_check;

		while (true)
		{
			if (sort_check == 1)
			{
				sort(o1.begin(), o1.end(), name_check);
				cout << "�̸� ������ ���ĵǾ����ϴ�. " << endl;
				break;
			}
			else if (sort_check == 2)
			{
				sort(o1.begin(), o1.end(), num_check);
				cout << "��ȣ ������ ���ĵǾ����ϴ�. " << endl;
				break;
			}
			cout << "�ٽ� �Է����ּ���." << endl;
		}
	}
}

template<class T>
void Search_func(vector<T>& o1)
{
	system("cls"); //clear console
	string Iname;
	cout << "�˻��Ͻ� ����� �̸��� �Է����ּ���." << endl;
	cin >> Iname;
	if (o1.empty())
	{
		cout << "��ȭ��ȣ�ΰ� ����ֽ��ϴ�." << endl;
		return;
	}
	else
	{
		auto it = find(o1.begin(), o1.end(), Iname); //iterator type
		cout << o1.at(it - o1.begin()).name << "�� ��ȭ��ȣ�� " << o1.at(it - o1.begin()).num << "�Դϴ�." << endl;

	}
}

template<class T>
void Delete_func(vector<T>& o1)
{
	system("cls"); //clear console
	string Iname;
	cout << "�����Ͻ� ����� �̸��� �Է����ּ���." << endl;
	cin >> Iname;
	if (o1.empty())
	{
		cout << "��ȭ��ȣ�ΰ� ����ֽ��ϴ�." << endl;
		return;
	}
	else
	{
		auto it = find(o1.begin(), o1.end(), Iname);
		cout << o1.at(it - o1.begin()).name << "�� ��ȭ��ȣ�� ���ŵǾ����ϴ�." << endl;
		o1.erase(it);
	}
}

template<class T>
void Save_func(vector<T>& o1)
{
	system("cls"); //clear console
	if (o1.empty())
	{
		cout << "��ȭ��ȣ�ΰ� ����ֽ��ϴ�. �߰��ϰ� �õ����ּ���!" << endl;
		return;
	}
	else
	{
		string Filename;
		cout << "�����Ϸ��� �����̸��� �Է����ּ���! ex)Daehan's P.B.txt" << endl;
		cin >> Filename;
		ofstream ofs;
		ofs.open(Filename);
		vector<Info>::reverse_iterator iter;
		for (iter = o1.rbegin(); iter!=o1.rend(); iter++)
		{
			ofs << o1.at(iter - o1.rbegin()).name << " " << o1.at(iter - o1.rbegin()).num << " " << "\n";
		}
		cout << Filename << "�� ��ȭ��ȣ ������ �Ϸ�Ǿ����ϴ�." << endl;
		ofs.close(); //Fileoutput Stream close!!
	}
}

template<class T>
void Load_func(vector<T>& o1)
{
	system("cls"); //clear console
	string Filename;
	string check;
	T Temp;
	cout << "�ҷ������� �����̸��� �Է����ּ���! ex)Daehan's P.B.txt" << endl;
	cin >> Filename;
	ifstream ifs;
	ifs.open(Filename);
	if (ifs.is_open())
	{
		cout << Filename << "�� ���������� �ҷ��Խ��ϴ�. " << endl;

		if (!o1.empty())
		{
			cout << "�������� �Էµ� ��ȭ��ȣ�θ� ���� ��ȭ��ȣ�� �ҷ����ðڽ��ϱ�? (�Է� : Y/N)";
			cin >> check;
		}
		if (check == "y" || check =="Y")
		{
			cout << "��ȭ��ȣ�θ� ���� ���Ϸκ��� ��ȭ��ȣ�� �ҷ��ɴϴ�." << endl;
			o1.clear();
		}
		else if (check == "n" || check == "N")
		{
			cout << "�������� �Էµ� ��ȭ��ȣ�� ���� �ҷ��ɴϴ�." << endl;
		}
		else
		{
			cout << "��ȭ��ȣ�� �ҷ��ɴϴ�." << endl;
		}
		while (ifs >> Temp.name >> Temp.num)
		{
			o1.push_back(Temp);
		}
		cout << "�̸� ������� �ڵ����ĵ˴ϴ�." << endl;
		sort(o1.begin(), o1.end(), name_check);
	}
	else
	{
		cout << "������ �������� �ʽ��ϴ�. �ٽ� �Է����ּ���!" << endl;
	}
	ifs.close(); //Fileinput Stream close!!
}

template<class T>
void Output_func(vector<T>& o1)
{
	system("cls"); //clear console
	int count = 0;
	if (!o1.empty())
	{
		cout << "��ϵ� ��ȭ��ȣ�� ����մϴ�." << endl << endl;
		
		cout.width(5);
		cout << "����";
		cout.width(6);
		cout << "�̸�";
		cout.width(13);
		cout << "��ȭ��ȣ" << endl;

		for (const auto& iter : o1) //value_type iterator
		{
			cout.width(3);
			cout << ++count;
			cout.width(9);
			cout << iter.name;

			if (iter.num.length() == 9)
			{
				cout.width(13);
				cout << iter.num << endl;
			}
			else
			{
				cout.width(15);
				cout << iter.num << endl;
			}
		}
	}
	else
	{
		cout << "��ϵ� ��ȭ��ȣ�� �����ϴ�." << endl;
		system("pause"); //remind
	}
}

template<class T>
void menu(vector<T>& o1)
{
	int check = 0;
	while (check != 7)
	{
		cout << "���ϴ� ����� �Է��ϼ���." << endl;
		cout << "1. ��ȭ��ȣ �߰�, 2. ��ȭ��ȣ �˻�, 3. ��ȭ��ȣ ���� " << endl << "4. ��ȭ��ȣ ����, 5. ��ȭ��ȣ �ε�, 6. ��ȭ��ȣ ���, 7. ���α׷� ����" << endl;
		cout << "��� >> ";
		cin >> check;
		switch (check)
		{
		case 1:
			Add_func(o1);
			break;
		case 2:
			Search_func(o1);
			break;
		case 3:
			Delete_func(o1);
			break;
		case 4:
			Save_func(o1);
			break;
		case 5:
			Load_func(o1);
			break;
		case 6:
			Output_func(o1);
			break;
		case 7:
			cout << "���α׷��� �����մϴ�. " << endl;
			break;
		default:
			cout << "�ٽ� �Է����ּ���!" << endl;
			return;
		}
	}
}


int main()
{
	vector<Info> List;
	cout << "��ȭ��ȣ�� ���α׷��� �����մϴ�." << endl;
	menu(List);
}