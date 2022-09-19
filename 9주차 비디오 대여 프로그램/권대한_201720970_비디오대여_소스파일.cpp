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
		if (o1.num != "") //존재하는 데이터를 기반으로 비교하게 함.
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
		if (num == "") // User Info, video는 생성자를 지나면 serial 강제 생성되기에...
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
		if (o1.num.length() > 6) // User Info, num이 6자리를 넘지 않기에...
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
	cout << "순서";
	cout.width(15);
	cout << "비디오 이름 ";
	cout.width(6);
	cout << "고유번호 ";
	cout.width(6);
	cout << "대여 상태" << endl;;
}

void u_frame()
{
	system("cls");
	cout << "순서";
	cout.width(10);
	cout << "이름 ";
	cout.width(13);
	cout << "전화번호 ";
	cout.width(15);
	cout << "대여 상태 " << endl;
}

void r_frame()
{
	system("cls");
	cout << "순서";
	cout.width(10);
	cout << "이름 ";
	cout.width(13);
	cout << "전화번호 ";
	cout.width(15);
	cout << "비디오 이름";
	cout.width(9);
	cout << "고유번호";
	cout.width(10);
	cout << "대여 일자";
	cout.width(12);
	cout << "반납 일자" << endl;
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
		if (o1.at(T1.top()).rental == 0) //rental status 0 : 기본, > 0 : 대여중 1~, < 0 : -1은 연체, 분실을 뜻함
		{
			cout << "재고 있음" << endl;
		}
		else if (o1.at(T1.top()).rental > 0)
		{
			cout << "대여 중" << endl;
		}
		else if (o1.at(T1.top()).rental < 0)
		{
			cout << "연체/분실" << endl;
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
			cout << "기본상태" << endl;
		}
		else if (o1.at(T1.top()).rental > 0)
		{
			cout << "대여 중" << endl;
		}
		else if (o1.at(T1.top()).rental < 0)
		{
			cout << "연체/분실" << endl;
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
	if (v_ifs.is_open() && u_ifs.is_open() && r_ifs.is_open()) //모든 파일이 로드 되었다면?
	{
		cout << "파일을 모두 성공적으로 불러왔습니다. " << endl;
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
		cout << "리스트를 모두 불러왔습니다. 오늘도 좋은 하루 되세요~ " << endl;
	}
	else
	{
		cout << "저장된 List를 불러오지 못했습니다. " << endl;
		cout << "List의 파일 규격은 다음과 같습니다." << endl;
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
	vector<Info>::reverse_iterator v_iter, u_iter; //역순으로 저장..., 굳이 파일을 되돌리기에는 연산이 더 많이 필요하기에
	vector<R_Info>::reverse_iterator r_iter;
	if (!o1.empty())
	{
		for (v_iter = o1.rbegin(); v_iter != o1.rend(); v_iter++)
		{
			v_ofs << o1.at(v_iter - o1.rbegin()).name << " " << o1.at(v_iter - o1.rbegin()).num << " " << o1.at(v_iter - o1.rbegin()).rental << " " << "\n";
		}
		cout << "VideoList를 저장중입니다..." << endl;
	}
	if (!o2.empty())
	{
		for (u_iter = o2.rbegin(); u_iter != o2.rend(); u_iter++)
		{
			u_ofs << o2.at(u_iter - o2.rbegin()).name << " " << o2.at(u_iter - o2.rbegin()).num << " " << o2.at(u_iter - o2.rbegin()).rental << " " << "\n";
		}
		cout << "UserList를 저장중입니다..." << endl;
	}
	if (!o3.empty())
	{
		for (r_iter = o3.rbegin(); r_iter != o3.rend(); r_iter++)
		{
			r_ofs << o3.at(r_iter - o3.rbegin()).u_name << " " << o3.at(r_iter - o3.rbegin()).u_num << " " << o3.at(r_iter - o3.rbegin()).v_name << " " << o3.at(r_iter - o3.rbegin()).v_num << " " << o3.at(r_iter - o3.rbegin()).rental_date << " " << o3.at(r_iter - o3.rbegin()).return_date << " " << "\n";
		}
		cout << "RentalList를 저장중입니다..." << endl;
	}
	cout << "모든 저장작업이 종료되었습니다." << endl;
	v_ofs.close(); //Fileoutput Stream close!!
	u_ofs.close();
	r_ofs.close();
}

void v_add(vector<Info>& o1)
{
	system("cls");
	Info T1;
	cout << "비디오 정보를 추가합니다. " << endl;
	cout << "추가하실 비디오 이름을 입력해주세요." << endl;
	cin >> T1.name;
	o1.push_back(T1);
	if (o1.size() != 1) //1번째 구동이 아니라면 정렬처리
	{
		sort(o1.begin(), o1.end(), name_check); // name sorting
	}

}

void u_add(vector<Info>& o1)
{
	system("cls");
	Info T1;
	cout << "사용자 정보를 추가합니다. " << endl;
	cout << "추가하실 사용자 이름을 입력해주세요." << endl;
	cin >> T1.name;
	cout << "사용자의 휴대폰 번호를 입력해주세요." << endl;
	cin >> T1.num;
	if (T1.num.length() == 11) //하이픈 체크
	{
		T1.num.insert(3, "-");
		T1.num.insert(8, "-");
	}
	o1.push_back(T1);
	if (o1.size() != 1) //1번째 구동이 아니라면 정렬처리
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
		it = find(it, o1.end(), T1); //또 그 위치 find but,,, stack에 저장하기 위해
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

void r_search(vector<R_Info>& o1, R_Info& T1, stack<int>& T2) //R_Info 리스트를 마지막에 다루다보니,모두 vu_search로 작성되어 있다 
{
	vu_search(o1, T1, T2);
}

void v_search(vector<Info>& o1)
{
	system("cls");
	if (o1.empty())
	{
		cout << "비디오 리스트가 비어있습니다." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		stack<int> t_index;
		int check = 0;
		cout << "검색하실 정보는 무엇인가요? (1 : 이름, 2 : 대여 정보)" << endl;
		cin >> check;

		if (check == 1)
		{
			cout << "이름을 입력해주세요" << endl;
			cin >> object1.name;
			object1.num = ""; // algorithm...
			vu_search(o1, object1, t_index);
			cout << "검색된 정보는 다음과 같습니다. " << endl;
			v_frame(); // frame output
			v_output(o1, t_index); //video, user search result output
			system("pause");
		}
		else if (check == 2)
		{
			cout << "대여 정보를 입력해주세요 (-1 : 연체/분실, 0 : 재고 있음, 1 : 대여 중)" << endl;
			cin >> object1.rental;
			object1.num = ""; // algorithm...
			vu_search(o1, object1, t_index);
			cout << "검색된 정보는 다음과 같습니다. " << endl;
			v_frame(); // frame output
			v_output(o1, t_index); //video search result output
			system("pause");
		}
		else
		{
			cout << "다시 입력해주세요" << endl;
		}
	}
}

void u_search(vector<Info>& o1)
{
	system("cls");
	if (o1.empty())
	{
		cout << "사용자 리스트가 비어있습니다." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		stack<int> t_index;
		int check = 0;
		cout << "검색하실 정보는 무엇인가요? (1 : 이름, 2 : 전화번호, 3 : 대여 정보)" << endl;
		cin >> check;

		if (check == 1)
		{
			cout << "이름을 입력해주세요" << endl;
			cin >> object1.name;
			object1.num = ""; // algorithm...
			vu_search(o1, object1, t_index);
			cout << "검색된 정보는 다음과 같습니다. " << endl;
			u_frame(); // frame output
			u_output(o1, t_index); //video, user search result output
			system("pause");
		}
		else if (check == 2)
		{
			cout << "전화번호를 입력해주세요 (하이픈 구분 없음)" << endl;
			cin >> object1.num;
			if (object1.num.length() == 11)
			{
				object1.num.insert(3, "-");
				object1.num.insert(8, "-");
			}
			vu_search(o1, object1, t_index);
			cout << "검색된 정보는 다음과 같습니다. " << endl;
			u_frame(); // frame output
			u_output(o1, t_index); //video search result output
			system("pause");
		}
		else if (check == 3)
		{
			cout << "대여 정보를 입력해주세요 (-1 : 연체/분실, 0 : 재고 있음, n : 대여 중인 사용자 수)" << endl;
			cin >> object1.rental;
			object1.num = ""; // algorithm...
			vu_search(o1, object1, t_index);
			cout << "검색된 정보는 다음과 같습니다. " << endl;
			u_frame(); // frame output
			u_output(o1, t_index); //video search result output
			system("pause");
		}
		else
		{
			cout << "다시 입력해주세요" << endl;
			system("pause");
		}

	}
}

void v_edit(vector<Info>& o1) 
{
	system("cls");
	if (o1.empty())
	{
		cout << "비디오 목록이 비어있습니다." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		int check = 0;
		int index = 0;

		stack<int> t_index, t_index1;
		cout << "수정하실 비디오 이름을 입력해주세요." << endl;
		cin >> object1.name;
		object1.num = ""; // random index clear
		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index; // stack issue.. stack을 사용하면 안 됬다.
		if (t_index.size() > 1)
		{
			v_frame();
			v_output(o1, t_index1);
			cout << "발견된 비디오가 2개 이상입니다. 수정하실 비디오를 선택해주세요. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else if (t_index.size() < 1)
		{
			cout << "해당 조건과 일치하는 비디오가 발견되지 않았습니다." << endl;
			system("pause");
			return;
		}
		else
		{
			index = t_index.top();
		}
		if (o1.at(index).rental)
		{
			cout << "사용자가 대여 중입니다. 반납 후 시도 해 주세요." << endl;
			system("pause");
			return;
		}
		//Video List Index를 기반으로 R_Info의 리스트를 색인(operator 재정의), 렌탈 리스트의 비디오 이름 수정
		cout << "수정하실 이름을 입력해주세요 " << endl;
		cin >> o1.at(index).name;
		cout << "이름 수정이 완료되었습니다." << endl;
		sort(o1.begin(), o1.end(), name_check);
	}
}

void u_edit(vector<Info>& o1) 
{
	system("cls");
	if (o1.empty())
	{
		cout << "사용자 목록이 비어있습니다." << endl;
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
		cout << "수정하실 사용자 이름을 입력해주세요." << endl;
		cin >> object1.name;
		object1.num = ""; // random index clear
		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index; // stack issue.. stack을 사용하면 안 됬다.
		if (t_index.size() > 1)
		{
			u_frame();
			u_output(o1, t_index1);
			cout << "발견된 사용자가 2명 이상입니다. 수정하실 사용자를 번호로 선택해주세요. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else if (t_index.size() < 1)
		{
			cout << "해당 조건과 일치하는 사용자가 발견되지 않았습니다." << endl;
			system("pause");
			return;
		}
		else
		{
			index = t_index.top();
		}
		if (o1.at(index).rental)
		{
			cout << "사용자가 대여 중입니다. 반납 후 시도 해 주세요." << endl;
			system("pause");
			return;
		}
		cout << "수정하실 데이터를 선택해주세요 (1: 이름, 2: 전화번호)" << endl;
		cin >> u_check;
		if (u_check == 1)
		{
			//User List Index를 기반으로 R_Info의 리스트를 색인(operator 재정의), 렌탈 리스트의 사용자 이름 수정
			cout << "수정하실 이름을 입력해주세요 " << endl;
			cin >> o1.at(index).name;
			cout << "이름 수정이 완료되었습니다." << endl;
		}
		else if (u_check == 2)
		{
			//User List Index를 기반으로 R_Info의 리스트를 색인(operator 재정의), 렌탈 리스트의 사용자 번호 수정
			cout << "수정하실 전화번호를 입력해주세요 " << endl;
			cin >> o1.at(index).num;
			cout << "번호 수정이 완료되었습니다." << endl;
		}
		sort(o1.begin(), o1.end(), name_check);
	}
}

void v_erase(vector<Info>& o1, vector<R_Info>& o3)
{
	system("cls");
	if (o1.empty())
	{
		cout << "비디오 목록이 비어있습니다." << endl;
		system("pause");
		return;
	}
	else
	{
		Info object1;
		int check = 0;
		int index = 0;
		stack<int> t_index, t_index1;
		cout << "제거하실 비디오 이름을 입력해주세요." << endl;
		cin >> object1.name;
		object1.num = ""; // random index clear
		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index; // stack issue.. stack을 사용하면 안 됬다.
		if (t_index.size() > 1)
		{
			v_frame();
			v_output(o1, t_index1);
			cout << "발견된 비디오가 2개 이상입니다. 제거하실 비디오를 선택해주세요. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else if (t_index.size() < 1)
		{
			cout << "해당 조건과 일치하는 비디오가 발견되지 않았습니다." << endl;
			system("pause");
			return;
		}
		else
		{
			index = t_index.top();
		}
		if (o1.at(index).rental)
		{
			cout << "비디오가 대여 중입니다. 반납 후 시도 해 주세요." << endl;
			system("pause");
			return;
		}
		cout << "비디오 제거가 완료되었습니다." << endl;
		o1.erase(o1.begin() + index);
		sort(o1.begin(), o1.end(), name_check);
	}
}

void u_erase(vector<Info>& o1, vector<R_Info>& o3) 
{
	system("cls");
	if (o1.empty())
	{
		cout << "사용자 목록이 비어있습니다." << endl;
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
		cout << "제거하실 사용자 이름을 입력해주세요." << endl;
		cin >> object1.name;
		object1.num = ""; // random index clear
		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index; // stack issue.. stack을 사용하면 안 됬다.
		if (t_index.size() > 1)
		{
			u_frame();
			u_output(o1, t_index1);
			cout << "발견된 사용자가 2명 이상입니다. 제거하실 사용자를 번호로 선택해주세요. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index.pop();
			}
			index = t_index.top();
		}
		else if (t_index.size() < 1)
		{
			cout << "해당 조건과 일치하는 사용자가 발견되지 않았습니다." << endl;
			system("pause");
			return;
		}
		else
		{
			index = t_index.top();
		}
		if (o1.at(index).rental) // 0 <, 0, > 0
		{
			cout << "사용자가 대여 중입니다. 반납 후 시도 해 주세요." << endl;
			system("pause");
			return;
		}
		cout << "사용자 제거가 완료되었습니다." << endl;
		o1.erase(o1.begin() + index);
		sort(o1.begin(), o1.end(), name_check);
	}
}

void av_output(vector<Info>& o1, vector<R_Info>& o3)
{
	system("cls"); //clear console
	if (!o1.empty())
	{
		cout << "전체 비디오 목록을 출력합니다." << endl;

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
				cout << "재고 있음" << endl;
			}
			else if (iter.rental > 0)
			{
				cout << "대여 중" << endl;
			}
			else if (iter.rental < 0)
			{
				cout << "연체/분실" << endl;
			}
		}
	}
	else
	{
		cout << "등록된 전화번호가 없습니다." << endl;
		return;
	}
	cout << "현재 비디오 List에는 " << o1.size() << "개의 비디오가 있으며,";
	cout << "대여 중인 비디오는 " << o3.size() << "개가 있습니다." << endl;
	system("pause");
}
void au_output(vector<Info>& o1, vector<R_Info>& o3)
{
	system("cls"); //clear console
	if (!o1.empty())
	{
		cout << "전체 사용자 목록을 출력합니다." << endl;

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
				cout << "기본상태" << endl;
			}
			else if (iter.rental > 0)
			{
				cout << "대여 중" << endl;
			}
			else if (iter.rental < 0)
			{
				cout << "연체/분실" << endl;
			}
		}
	}
	else
	{
		cout << "등록된 사용자가 없습니다." << endl;
		return;
	}
	cout << "현재 사용자 List에는 " << o1.size() << "명의 사용자가 있으며,";
	cout << "대여 중인 비디오는 " << o3.size() << "개가 있습니다." << endl;
	system("pause");
}

void ar_output(vector<R_Info>& o3)
{
	system("cls"); //clear console
	if (!o3.empty())
	{
		cout << "대여 목록을 출력합니다." << endl;

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
		cout << "대여 중인 비디오가 없습니다." << endl;
		return;
	}
	cout << "대여 중인 비디오는 " << o3.size() << "개가 있습니다." << endl;
}

void v_rental(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3)
{
	system("cls");
	if (o1.empty())
	{
		cout << "비디오 목록이 비어있습니다." << endl;
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

		cout << "대여하실 비디오 이름을 입력해주세요." << endl;
		cin >> object1.name;

		vu_search(o1, object1, t_index); //saving index
		t_index1 = t_index;
		if (t_index1.size() == 0)
		{
			cout << "해당 조건과 일치하는 비디오가 발견되지 않았습니다." << endl;
			system("pause");
			return;
		}
		else if (t_index1.size() > 1)
		{
			v_frame();
			v_output(o1, t_index1);
			cout << "발견된 비디오가 2개 이상입니다. 대여하실 비디오를 선택해주세요. " << endl;
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
		cout << "대여자 이름을 입력해주세요." << endl;
		cin >> object2.name;
		vu_search(o2, object2, t_index2); //find user index
		t_index3 = t_index2;
		if (t_index2.size() == 0)
		{
			cout << "해당 조건과 일치하는 사용자가 없습니다." << endl;
			system("pause");
			return;
		}
		else if (t_index2.size() > 1)
		{
			u_frame();
			u_output(o2, t_index3);
			cout << "발견된 사용자가 2명 이상입니다. 대여자를 번호로 선택해주세요. " << endl;
			cin >> check;
			for (int i = 1; i < check; i++)
			{
				t_index2.pop();
			}
		}
		cout << "반납 일을 입력해주세요. ex)2020-11-01" << endl;
		cin >> object3.return_date;


		index1 = t_index2.top();
		o1.at(index).rental = 1; //video Only one at same time
		o2.at(index1).rental++; //user rental status
		object3 = o2.at(index1);
		object3 = o1.at(index); //copy of user, video data
		o3.push_back(object3);

		cout << "비디오 대여처리가 완료되었습니다." << endl;
		system("pause");
	}
}
void v_return(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3)
{
	system("cls");
	if (o3.empty())
	{
		cout << "대여 목록이 비어있습니다." << endl;
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
		cout << "반납하실 비디오 이름을 입력해주세요." << endl;
		cin >> object1.v_name;

		r_search(o3, object1, t_index); //saving index
		t_index1 = t_index;
		//R_Info indexing...
		if (t_index1.size() == 0)
		{
			cout << "해당 조건과 일치하는 비디오가 발견되지 않았습니다." << endl;
			system("pause");
			return;
		}
		else if (t_index1.size() > 1)
		{
			r_frame();
			r_output(o3, t_index1); //need double stack...
			cout << "발견된 비디오가 2개 이상입니다. 반납하실 비디오를 선택해주세요. " << endl;
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

		cout << "비디오 반납처리가 완료되었습니다." << endl;
		system("pause");
	}
}

void v_menu(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3) //function for videodata access
{
	int check = 0;
	while (true)
	{
		system("cls");
		cout << "비디오 데이터를 관리합니다." << endl;
		cout << "1. 추가, 2. 검색, 3. 수정, 4. 제거, 5. 출력, 6. 대여, 7. 반납, 8. 상위 레벨로 이동" << endl;
		cout << "기능 >> ";
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
			cout << "비디오 관리 함수를 종료합니다." << endl;
			return;
		default:
			cout << "다시 입력해주세요!" << endl;
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
		cout << "사용자 데이터를 관리합니다." << endl;
		cout << "1. 추가, 2. 검색, 3. 수정, 4. 제거, 5. 출력, 6. 대여, 7. 반납, 8. 상위 레벨로 이동" << endl;
		cout << "기능 >> ";
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
			cout << "사용자 관리 함수를 종료합니다." << endl;
			return;
		default:
			cout << "다시 입력해주세요!" << endl;
			continue;
		}
	}
}

void menu(vector<Info>& o1, vector<Info>& o2, vector<R_Info>& o3) //using data selection....
{
	int check = 0;
	while (true) // 1 or 2일경우 다음 함수로 진행
	{
		system("cls");
		cout << "관리하고 싶은 데이터를 고르세요 (1 : 비디오 데이터, 2 : 사용자 데이터, 3 : 대여목록 출력, 4 : 프로그램 종료)" << endl;
		cout << "기능 >> ";
		cin >> check;
		if (check != 1 && check != 2 && check != 3 && check != 4)
		{
			system("cls");
			cout << "다시 입력해주세요" << endl;
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
	menu(videodata, userdata, rentaldata); //메인 기능 함수 실행
}