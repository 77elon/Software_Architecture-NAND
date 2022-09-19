#include <iostream>
#include <string>

 //for debugging, reallocation
#include <fstream>

using namespace std;

class Flash
{
public:
	char Sector[512]; // 512 + 1 byte, Pointer == (Variable *= 4)
	int Valid_Check = 0; // length of data?
	Flash()
	{
		for (int i = 0; i < 512; i++)
		{
			Sector[i] = 0; //init data allocation, 0 Fill
		}
	}
	/*Flash(const int& v1)
	{
		for (int i = 0; i < 512; i++)
		{
			Sector[i] = 65 + v1; //0x41 1st A, 2nd B...
		}
	}*/ //이는 의미가 없다. why? 결국 0 Fill 만이 제일 적게 수명을 깎는다... A, B, C Fill 또한 Write임을 인지...
};

void Sector_Frame()
{
	cout << "섹터 번호";
	cout.width(20);
	cout << "데이터 길이" << endl;
}
void SectorData_Frame()
{
	cout << endl;
	cout << "섹터 데이터" << endl;
}

Flash* pos; // 8 byte
int secsize;

void Input_Func(string& o1, const unsigned int& v1)
{
	cin >> o1;
	while (true) //isDegit을 사용하지 않은 이유? 사실 String의 각 인덱스를 색인하는 것은 시간낭비!
	{
		if (cin.fail() || o1.length() > v1)
		{
			cout << "다시 입력해주세요." << endl;
			cin.clear(); //오류가 발생한 스트림 초기화
			cin.ignore(256, '\n'); //입력된 값 초기화
			cin >> o1;
		}
		else
		{
			break;
		}
	}
}

int Conv__Func(string& o1)
{
	int conv;
	try
	{
		conv = stoi(o1);
	}
	catch (...) //입력 함수에서 isDegit으로 적절히 거를 수 있지만, 만약 숫자와 영어가 같이 들어온다면??
	{
		cout << "엑세스하려는 블록이나 섹터를 \"숫자로만\" 입력해주세요!" << endl;
		return -1;
	}
	return conv;
}

void Exit_Func(const string o1)
{
	if (o1 == "exit" || o1 == "Exit" || o1 == "EXIT")
	{
		if (pos) //data allocated check
		{
			delete[] pos;
		}
		exit(0);
	}
}

void SecSave_Func(Flash*& o1)
{
	if (!pos)
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
	else
	{
		ofstream s_ofs;
		s_ofs.open("Reallocation.txt");
		for (int i = 0; i < secsize; i++) 	//size != 0 saving!!, secsize exist
		{
			if (o1[i].Valid_Check) //data is Full
			{
				s_ofs << i << " " << o1[i].Sector << " " << o1[i].Valid_Check << " " << "\n";
			}
		}
		s_ofs.close();
		cout << "파일이 정상적으로 저장되었습니다." << endl;
	}
}
void SecLoad_Func(Flash*& o1)
{
	if (!pos)
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
	else
	{
		ifstream s_ifs;
		s_ifs.open("Reallocation.txt");
		if (s_ifs.is_open())
		{
			int index;
			Flash temp;
			while (s_ifs >> index >> temp.Sector >> temp.Valid_Check && index < secsize) //if file index > secsize?
			{
				o1[index] = temp; //Object Copy
			}
			cout << "파일이 정상적으로 로드되었습니다." << endl;
		}
		else
		{
			cout << "저장된 파일이 없습니다." << endl;
		}
		s_ifs.close(); //file Stream...
	}
}

void Sector_read(Flash*& o1, int& v1)
{
	Sector_Frame();
	int i = 0;
	cout.width(5);
	cout << v1;
	cout.width(19);
	cout << o1[v1].Valid_Check;
	SectorData_Frame();
	while (i < 512 && o1[v1].Sector[i] != 0)
	{
		if (i != 0 && i % 30 == 0)
		{
			cout << endl;
		}
		cout << o1[v1].Sector[i];
		++i;
	}
	cout << endl;

	//data validate check
	if (i == o1[v1].Valid_Check && o1[v1].Valid_Check)
	{
		cout << "데이터의 온전히 저장되어 있습니다." << endl;
	}
	else
	{
		cout << "Sector가 비어있거나, 손상되었습니다." << endl;
	}
}
void Sector_write(Flash*& o1, int& v1, const string& o2)
{
	const char* data = o2.c_str();
	unsigned int i = 0;
	while (i < o2.length()) //어차피 512byte를 넘는 데이터는 입력단에서...
	{
		o1[v1].Sector[i] = data[i]; //casting 불가하기에
		++i;
	}
	o1[v1].Valid_Check = (int)o2.length(); //data size saving
}

void Indexing_Func(Flash*& o1, int& v1)
{
	int temp = v1;
	int temp1 = v1;
	while (temp < secsize && temp1 >= 0)
	{
		if (temp + 1 == secsize) //end
		{
			--temp1;
		}
		else if (temp1 - 1 < 0) //first
		{
			++temp;
		}
		else //middle
		{
			++temp;
			--temp1;
		}
		if (!o1[temp].Valid_Check) //if temp isEmpty 증산체크
		{
			v1 = temp;
			return;
		}
		if (!o1[temp1].Valid_Check)// if temp isEmpty 증감체크
		{
			v1 = temp1;
			return;
		}
	}
}
void Block_Erase(Flash*& o1, int& v1) //v1 is blk index 0-31, 32-63, 64-95
{
	int start =  v1 * 32;
	int end = (v1 + 1) * 32; // end 전까지
	while (start < end)
	{
		memset(o1[start].Sector, '\0', 512); //0-511 Data Clear
		o1[start].Valid_Check = 0;
		++start; //end 전까지
	}
}

void Rinit(Flash*& o1, int& v1)
{
	Flash* temp = new Flash[2048 * v1]; //dynamic array allocation
	o1 = temp;
	secsize = v1 * 2048; //secsize / 32 == blksize
}
void init(Flash*& o1, int& v1)
{
	system("cls");
	bool temp = false;
	if (pos) //if allocated
	{
		cout << "이미 Flash Memory가 할당되어 있습니다. 재할당하시겠습니까? (Y / N)" << endl;
		string check = "", check1 = "";
		while (check != "y" && check != "Y" && check != "n" && check != "N")
		{
			Input_Func(check, 1);
		}
		if (check == "n" || check == "N")
		{
			return;
		}
		else if (check == "y" || check == "Y")
		{
			cout << "기존 할당된 메모리보다 작은 사이즈로 재할당시, 데이터 손실이 발생할 수 있습니다. 그래도 진행하시겠습니까? (Y / N)" << endl;
			while (check1 != "y" && check1 != "Y" && check1 != "n" && check1 != "N")
			{
				Input_Func(check1, 1);
			}
			if (check1 == "n" || check1 == "N")
			{
				return;
			}
			temp = true; //need data restore!!
			//file saving Func
			SecSave_Func(o1);
			delete[] o1; //mem release
		}
	}
	cout << v1 << "MB의 용량 " << v1 * 2048 << "섹터 크기를 가진 Flash Memory를 생성합니다." << endl;
	Rinit(o1, v1); //real init, dynamic allocation
	if (temp)
	{
		//file loading Func
		SecLoad_Func(o1);
	}
}

void Flash_read(Flash*& o1, int& v1)
{
	system("cls");
	if (!pos) //array isEmpty
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
	else if (pos && v1 < secsize)
	{
		Sector_read(o1, v1); //real read func
	}
	else
	{
		cout << "할당된 저장소를 초과한 공간의 데이터를 읽고자 하였습니다. " << endl; //Err
	}
}

void Flash_write(Flash*& o1, int& v1, const string& o2)
{
	system("cls");
	if (!pos)
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
	else if (pos && v1 < secsize)
	{
		string check = "";
		if (o1[v1].Valid_Check != 0) //sector is Full
		{
			cout << "해당 Sector가 사용 중입니다. Override 하시겠습니까? (Y / N)" << endl;
			while (check != "y" && check != "Y" && check != "n" && check != "N")
			{
				Input_Func(check, 1);
			}
			if (check == "y" || check == "Y") //Find Fastest Sector Index
			{
				cout << "FTL Algorithm 없이는 Override 할 수 없습니다. " << endl;
				cout << "비어있는 가장 빠른 Sector에 데이터를 저장합니다. " << endl;
				//Indexing Func..
				Indexing_Func(o1, v1);
				cout << "데이터가 " << v1 << "번 Sector에 저장될 예정입니다." << endl;

			}
			if (check == "n" || check == "N") 
			{
				return;
			}
		}
		cout << "입력된 Sector " << v1 << "에 데이터를 저장합니다." << endl;
		//real write fun
		Sector_write(o1, v1, o2);
		Sector_read(o1, v1); //write result
	}
	else
	{
		cout << "할당된 저장소를 초과한 공간에 데이터를 쓰고자 하였습니다. " << endl; //Err
	}
}

void Flash_erase(Flash*& o1, int& v1) //v1 is blk index
{
	system("cls");
	if (!pos)
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
	else if (pos && v1 < (secsize / 32))
	{
		Block_Erase(o1, v1);
		cout << "Block " << v1 << "의 삭제가 완료되었습니다." << endl;
	}
	else
	{
		cout << "할당된 저장소를 초과한 공간의 데이터를 지우고자 하였습니다. " << endl; //Err
	}
}

void Status_Func()
{
	system("cls");
	if (pos)
	{
		cout << secsize << "의 Sector 크기를 가지고 있으며, " << secsize / 2048 << "MB의 크기를 가지고 있습니다." << endl;
	}
	else if (!pos)
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
}

void Exec_Func(Flash*& o1)
{
	string Input1 = "", Input2 = "", Input3 = ""; //write data!!
	while (true)
	{
		cout << "시뮬레이션 하고 싶은 명령을 내려주세요. (init, read, write, erase, status, save, load, exit)" << endl;
		Input_Func(Input1, 6); //maximum length set
		Exit_Func(Input1); //Trusted Input...!
		if (Input1 == "init" || Input1 == "Init" || Input1 == "INIT") //if init + Eng Input?? => Error
		{
			Input_Func(Input2, 3); // xxxMB
			int temp = Conv__Func(Input2); //Mem Size
			if (temp == -1 || temp < 0)
			{
				continue;
			}
			init(o1, temp);
			pos = o1;
		}
		else if (Input1 == "read" || Input1 == "Read" || Input1 == "READ")
		{
			Input_Func(Input2, 6); //Maximum 488MB Sector
			int temp = Conv__Func(Input2); //PSN Posit
			if (temp == -1 || temp < 0)
			{
				continue;
			}
			//read fun
			Flash_read(o1, temp);
		}
		else if (Input1 == "write" || Input1 == "Write" || Input1 == "WRITE")
		{
			Input_Func(Input2, 6); //Maximum 488MB Sector
			int temp = Conv__Func(Input2); //PSN Posit
			if (temp == -1 || temp < 0)
			{
				continue;
			}
			Input_Func(Input3, 512); //data input
			//write fun
			Flash_write(o1, temp, Input3);
			Input3 = ""; //Write에서만 사용되기에 상관은 없지만...
		}
		else if (Input1 == "erase" || Input1 == "Erase" || Input1 == "ERASE")
		{
			Input_Func(Input2, 4); //Maximum 156.2343MB Block
			int temp = Conv__Func(Input2); //PSN Posit
			if (temp == -1 || temp < 0)
			{
				continue;
			}
			Flash_erase(o1, temp);
		}
		else if (Input1 == "status" || Input1 == "Status" || Input1 == "STATUS") 
		{
			Status_Func();
		}
		else if (Input1 == "save" || Input1 == "Save" || Input1 == "SAVE")
		{
			SecSave_Func(o1);
		}
		else if (Input1 == "load" || Input1 == "Load" || Input1 == "LOAD")
		{
			SecLoad_Func(o1);
		}
		else
		{
			continue;
		}
	}
}

int main()
{
	Flash* data;
	Exec_Func(data);
}
