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
	cout << "저장하실 사용자 이름을 입력하세요!" << endl;
	cin >> Iname;
	cout << "저장하실 사용자 전화번호를 입력하세요!" << endl;
	cin >> Inum;
	Object1.name = Iname;
	Object1.num = Inum;
	/*if (Object1.num.length() == 12 || Object1.num.length() == 9)
	{
		o1.push_back(Object1);
	}
	else */ //플로우차트대로 작성하면 윗 부분의 코드가 작성되어야 하는데, 의도가 같기 때문에 밑에서 한 번에 추가하겠습니다.
	if (Object1.num.length() == 11) //전화번호 정렬을 위한 하이픈 작성
	{
		cout << "휴대폰 번호입니다." << endl;
		Object1.num.insert(3, "-");
		Object1.num.insert(8, "-");
	}
	else if (Object1.num.length() == 8)
	{
		cout << "특수목적 전화번호입니다." << endl;
		Object1.num.insert(4, "-");
	}
	o1.push_back(Object1); //List에 전화번호 저장
	cout << "전화번호가 저장되었습니다." << endl;
	if (o1.size() != 1)
	{
		cout << "이름 순 정렬을 원하시면 1번을 입력하시고, 전화번호 순 정렬을 원하시면 2번을 입력하세요." << endl;
		cin >> sort_check;

		while (true)
		{
			if (sort_check == 1)
			{
				sort(o1.begin(), o1.end(), name_check);
				cout << "이름 순으로 정렬되었습니다. " << endl;
				break;
			}
			else if (sort_check == 2)
			{
				sort(o1.begin(), o1.end(), num_check);
				cout << "번호 순으로 정렬되었습니다. " << endl;
				break;
			}
			cout << "다시 입력해주세요." << endl;
		}
	}
}

template<class T>
void Search_func(vector<T>& o1)
{
	system("cls"); //clear console
	string Iname;
	cout << "검색하실 사용자 이름을 입력해주세요." << endl;
	cin >> Iname;
	if (o1.empty())
	{
		cout << "전화번호부가 비어있습니다." << endl;
		return;
	}
	else
	{
		auto it = find(o1.begin(), o1.end(), Iname); //iterator type
		cout << o1.at(it - o1.begin()).name << "의 전화번호는 " << o1.at(it - o1.begin()).num << "입니다." << endl;

	}
}

template<class T>
void Delete_func(vector<T>& o1)
{
	system("cls"); //clear console
	string Iname;
	cout << "삭제하실 사용자 이름을 입력해주세요." << endl;
	cin >> Iname;
	if (o1.empty())
	{
		cout << "전화번호부가 비어있습니다." << endl;
		return;
	}
	else
	{
		auto it = find(o1.begin(), o1.end(), Iname);
		cout << o1.at(it - o1.begin()).name << "의 전화번호가 제거되었습니다." << endl;
		o1.erase(it);
	}
}

template<class T>
void Save_func(vector<T>& o1)
{
	system("cls"); //clear console
	if (o1.empty())
	{
		cout << "전화번호부가 비어있습니다. 추가하고 시도해주세요!" << endl;
		return;
	}
	else
	{
		string Filename;
		cout << "저장하려는 파일이름을 입력해주세요! ex)Daehan's P.B.txt" << endl;
		cin >> Filename;
		ofstream ofs;
		ofs.open(Filename);
		vector<Info>::reverse_iterator iter;
		for (iter = o1.rbegin(); iter!=o1.rend(); iter++)
		{
			ofs << o1.at(iter - o1.rbegin()).name << " " << o1.at(iter - o1.rbegin()).num << " " << "\n";
		}
		cout << Filename << "에 전화번호 저장이 완료되었습니다." << endl;
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
	cout << "불러오려는 파일이름을 입력해주세요! ex)Daehan's P.B.txt" << endl;
	cin >> Filename;
	ifstream ifs;
	ifs.open(Filename);
	if (ifs.is_open())
	{
		cout << Filename << "를 성공적으로 불러왔습니다. " << endl;

		if (!o1.empty())
		{
			cout << "이제까지 입력된 전화번호부를 비우고 전화번호를 불러오시겠습니까? (입력 : Y/N)";
			cin >> check;
		}
		if (check == "y" || check =="Y")
		{
			cout << "전화번호부를 비우고 파일로부터 전화번호를 불러옵니다." << endl;
			o1.clear();
		}
		else if (check == "n" || check == "N")
		{
			cout << "이제까지 입력된 전화번호와 같이 불러옵니다." << endl;
		}
		else
		{
			cout << "전화번호를 불러옵니다." << endl;
		}
		while (ifs >> Temp.name >> Temp.num)
		{
			o1.push_back(Temp);
		}
		cout << "이름 기반으로 자동정렬됩니다." << endl;
		sort(o1.begin(), o1.end(), name_check);
	}
	else
	{
		cout << "파일이 존재하지 않습니다. 다시 입력해주세요!" << endl;
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
		cout << "등록된 전화번호를 출력합니다." << endl << endl;
		
		cout.width(5);
		cout << "순서";
		cout.width(6);
		cout << "이름";
		cout.width(13);
		cout << "전화번호" << endl;

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
		cout << "등록된 전화번호가 없습니다." << endl;
		system("pause"); //remind
	}
}

template<class T>
void menu(vector<T>& o1)
{
	int check = 0;
	while (check != 7)
	{
		cout << "원하는 기능을 입력하세요." << endl;
		cout << "1. 전화번호 추가, 2. 전화번호 검색, 3. 전화번호 제거 " << endl << "4. 전화번호 저장, 5. 전화번호 로드, 6. 전화번호 출력, 7. 프로그램 종료" << endl;
		cout << "기능 >> ";
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
			cout << "프로그램을 종료합니다. " << endl;
			break;
		default:
			cout << "다시 입력해주세요!" << endl;
			return;
		}
	}
}


int main()
{
	vector<Info> List;
	cout << "전화번호부 프로그램을 시작합니다." << endl;
	menu(List);
}