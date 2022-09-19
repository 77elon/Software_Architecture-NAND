#include <iostream>
#include <string>

//for debugging, reallocation
#include <fstream>
#include <vector>

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
void SectorMap_Frame()
{
	cout.width(4);
	cout << "LBN";
	cout.width(7);
	cout << "PBN" << endl;
}
void BlockMap_Frame()
{
	cout.width(4);
	cout << "LBN";
	cout.width(7);
	cout << "PBN" << endl;
}

Flash* pos, * Spare; // 8 byte + 8 byte
int secsize = 0, read = 0, write = 0, erase = 0, erase_index = 0, gavage = 0; // 4 + 4 + 4 + 4 + 4 + 4 byte

void IO_Check()
{
	if (read > 0)
	{
		cout << "읽기 연산 " << read << "회 ";
	}
	if (write > 0)
	{
		cout << "쓰기 연산 " << write << "회 ";
	}
	if (erase > 0)
	{
		cout << "지우기 연산 (PBN " << erase_index << ")";
	}
	cout << endl;
}

void Saved_Clear()
{
	read = write = erase = 0;
	delete[] Spare;
	Spare = nullptr;
}


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

void Exit_Func(const string& o1)
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

void SecSave_Func(Flash*& o1, const string& o2)
{
	if (!pos)
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
	else
	{
		ofstream s_ofs;
		s_ofs.open(o2);
		for (int i = 0; i < secsize + 32; i++) 	//size != 0 saving!!, secsize exist
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
void SecLoad_Func(Flash*& o1, const string& o2)
{
	if (!pos)
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
	else
	{
		ifstream s_ifs;
		s_ifs.open(o2);
		if (s_ifs.is_open())
		{
			int index;
			Flash temp;
			while (s_ifs >> index >> temp.Sector >> temp.Valid_Check && index < secsize + 32) //if file index > secsize?
			{
				o1[index] = temp; //Object Copy
			}
		}
		else
		{
			cout << "저장된 파일이 없습니다." << endl;
		}
		s_ifs.close(); //file Stream...
	}
}

void TableSave_func(vector<int>& o1, const string& o2, const string& o3)
{
	ofstream ofs, ofs_size;
	ofs.open(o2);
	ofs_size.open(o3);
	vector<int>::reverse_iterator iter;
	for (iter = o1.rbegin(); iter != o1.rend(); iter++)
	{
		ofs << o1.at(iter - o1.rbegin()) << " " << "\n";
	}

	ofs_size << secsize << " " << erase_index << " " << "\n";

	ofs_size.close();
	ofs.close(); //Fileoutput Stream close!!
}
void TableLoad_func(vector<int>& o1, const string& o2, const string& o3)
{
	ifstream ifs, ifs_size;
	ifs.open(o2);
	ifs_size.open(o3);
	if (ifs.is_open() && ifs_size.is_open())
	{
		int Temp = 0;
		while (ifs >> Temp)
		{
			o1.push_back(Temp);
		}

		ifs_size >> secsize >> erase_index;
	}
	else
	{
		cout << "파일이 존재하지 않습니다." << endl;
	}
	ifs_size.close();
	ifs.close(); //Fileinput Stream close!!
}

void offset_calc(int& v1, int& v2, int& v3)
{
	v2 = v1 / 32; //lbn
	v3 = v1 % 32; //offset
}
void reverse_calc(vector<int>& o1, int& v1, int& v2, int& v3, int& v4) //psn, pbn, lbn, offset
{
	v2 = v1 / 32;
	v4 = v1 % 32;
	auto it = find(o1.begin(), o1.end(), v2); //lbn find(index)
	v3 = (int)(it - o1.begin());
}

void Sector_read(Flash*& o1, int& v1)
{
	++read;
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
	++write;
	const char* data = o2.c_str();
	unsigned int i = 0;
	while (i < o2.length()) //어차피 512byte를 넘는 데이터는 입력단에서...
	{
		o1[v1].Sector[i] = data[i]; //casting 불가하기에
		++i;
	}
	o1[v1].Valid_Check = (int)o2.length(); //data size saving
}

bool Block_isEmpty(Flash*& o1, int& v1)
{
	int start_index = v1 * 32;
	//int end_index = (v1 + 1) * 32 - 1;
	int check = 0;
	int i = 0;
	for (i = 0; i < 32; i++)
	{
		if (!o1[start_index + i].Valid_Check)
		{
			check++;
		}
	}
	read += i + 1;
	return check == 32;
}
bool Block_isFull(Flash*& o1, int& v1)
{
	int check = 0;
	int i = 0;
	for (i = 0; i < 32; i++)
	{
		if (o1[v1 * 32 + i].Valid_Check)
		{
			++check;
		}
		else
		{
			break;
		}
	}
	read += i + 1;
	return check == 32;
}
void SecIndexing_Func(Flash*& o1, int& v1) //mapped psn
{
	int temp = secsize; //first spare index

	while (temp < secsize + 32) //at secsize + 31
	{
		++read;
		if (!o1[temp].Valid_Check) //if temp isEmpty 증산체크
		{
			v1 = temp;
			return;
		}
		++temp; //temp = spare space start
	}
}

void SecExist_check(Flash*& o1, vector<int>& o2, int& v1) //table, blk, data restore, but end of block write after...?
{
	Spare = new Flash[32];
	int t = 0;
	for (int i = 0; i < 32; i++)
	{
		int temp = v1 * 32 + i; //blk indexing
		auto it = find(o2.begin(), o2.end(), temp); //index find!!
		while (true)
		{
			it = find(it, o2.end(), temp);
			if (it != o2.end()) //mapping된 psn이 존재할 때
			{
				++read;
				while (pos[temp].Sector[t] != 0)
				{
					Spare[i].Sector[t] = o1[temp].Sector[t];
					t++;
				}
				Spare[i].Valid_Check = pos[temp].Valid_Check;
				++it;
			}
			else
			{
				break;
			}
		}
	}
}
void BlkExist_check(Flash*& o1, int& v1, int& v2, int& v3, int& v4) //Flash, pbn, lbn, offset, dest blk
{
	int start_index = v1 * 32;
	int spare_index = v4 * 32;
	for (int i = 0; i < 32; i++)
	{
		if (o1[start_index + i].Valid_Check != 0 && i != v3) //if data is valid, skip offset data 
		{
			int t = 0;
			++read;
			++write;
			while (t < o1[start_index + i].Valid_Check)
			{
				o1[spare_index + i].Sector[t] = o1[start_index + i].Sector[t];
				t++;
			}
			o1[spare_index + i].Valid_Check = o1[start_index + i].Valid_Check;
		}
	}
}

void Block_Erase(Flash*& o1, int& v1) //v1 is blk index 0-31, 32-63, 64-95
{
	++erase;
	erase_index = v1;
	int start = v1 * 32;
	int end = (v1 + 1) * 32; // end 전까지
	while (start < end)
	{
		memset(o1[start].Sector, '\0', 512); //0-511 Data Clear
		o1[start].Valid_Check = 0;
		++start; //end 전까지
	}
}
void Restore_Block(Flash*& o1, int& v1) //blk index, valid data restore per block
{
	for (int i = 0; i < 32; i++)
	{
		int index = v1 * 32 + i;
		if (Spare[i].Valid_Check != 0)
		{
			int t = 0;
			++write;
			while (Spare[i].Sector[t] != 0)
			{
				o1[index].Sector[t] = Spare[i].Sector[t];
				t++;
			}
			o1[index].Valid_Check = Spare[i].Valid_Check;
		}
	}
}

void Gavage_erase(Flash*& o1, vector<int>& o2)
{
	if (pos)
	{
		int spareblk = secsize / 32;
		int dest = o2.at(gavage) / 32;
		if (Block_isFull(o1, dest)) //block start point, end point isfull
		{
			//block copy needsr
			SecExist_check(o1, o2, dest);
			//Gavage Clear
			Block_Erase(o1, dest);
			Restore_Block(o1, dest);
			++gavage;
		}
		else if (gavage == spareblk)
		{
			gavage = 0;
		}
	}
}

void Mapping_init(vector<int>& o1, const string& o2)
{
	if (o1.empty())
	{
		int temp = secsize;
		int blk_temp = secsize / 32 - 1;
		while (temp != 0 && blk_temp != -1) // block start.. 0!
		{
			if (o2 == "sector")
			{
				--temp;
				o1.push_back(temp); //어차피 역순
			}
			else if (o2 == "block")
			{
				o1.push_back(blk_temp);
				--blk_temp;
			}
		}
	}
}
void init(Flash*& o1, vector<int>& o2, const string& o3, int& v1)
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
			SecSave_Func(o1, "Reallocation.txt");
			delete[] o1; //mem release
		}
	}
	cout << v1 << "MB의 용량 " << v1 * 2048 << "섹터 크기를 가진 Flash Memory를 생성합니다." << endl;

	//real init, dynamic allocation
	o1 = new Flash[2048 * v1 + 32]; //dynamic array allocation, spare block
	secsize = v1 * 2048; //secsize / 32 == blksize
	Mapping_init(o2, o3);

	if (temp)
	{
		//file loading Func
		SecLoad_Func(o1, "Reallocation.txt");
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
	else if (pos && v1 < secsize + 32)
	{
		Sector_read(o1, v1); //real read func
	}
	else
	{
		cout << "할당된 저장소를 초과한 공간의 데이터를 읽고자 하였습니다. " << endl; //Err
	}
}

void Flash_write(Flash*& o1, vector<int>& o2, int& v1, const string& o3, const string& o4)
{
	system("cls");
	if (!pos)
	{
		cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
		return;
	}
	else if (o4 == "sector" && pos && v1 < secsize + 32)
	{
		int spareblk = secsize / 32;
		if (o1[v1].Valid_Check != 0) //sector is Full
		{
			cout << "비어있는 가장 빠른 Sector에 데이터를 저장합니다. " << endl;
			//Indexing Func..
			SecIndexing_Func(o1, v1); //입력된 index 기반으로 처리하면 빠른 처리가 가능할 것!
			//spare block isFull
			if (Block_isFull(o1, spareblk)) //마지막 인덱스가 사용중일 것이므로, 마지막 인덱스의 초기화가 안된다...! 이후 메모리를 비워야 한다면?
			{
				SecExist_check(o1, o2, spareblk);
				Block_Erase(o1, spareblk);
				Restore_Block(o1, spareblk);
				v1 = secsize;
			}
			else
			{
				cout << "데이터가 " << v1 << "번 Sector에 저장될 예정입니다." << endl;
			}
		}
		else
		{
			cout << "Sector " << v1 << "에 데이터를 저장합니다." << endl;
		}
		//real write fun
		Sector_write(o1, v1, o3);
		Sector_read(o1, v1); //write result
	}
	else if (o4 == "block" && pos && v1 < secsize + 32) //at spare block
	{
		int pbn = 0, lbn = 0, offset = 0, spareblk = secsize / 32;
		reverse_calc(o2, v1, pbn, lbn, offset);
		if (o1[v1].Valid_Check != 0) //sector is Full
		{
			cout << "여분의 블록에 데이터를 저장합니다. " << endl;
			//spare block isFull
			if (Block_isEmpty(o1, spareblk))
			{
				BlkExist_check(o1, pbn, lbn, offset, spareblk);
				Block_Erase(o1, pbn); //erase_index = spareblk;
				o2.at(lbn) = spareblk;
			}
			else
			{
				int wear = erase_index;
				while (erase_index < spareblk && wear > 0) //find empty block
				{
					if (Block_isEmpty(o1, wear))
					{
						break;
					}
					wear--;
				}
				BlkExist_check(o1, pbn, lbn, offset, wear);
				Block_Erase(o1, pbn);
				o2.at(lbn) = wear;
			}
			int last = o2.at(lbn) * 32 + offset;
			cout << "데이터가 " << last << "번 Sector에 저장될 예정입니다." << endl; //psn input
			Sector_write(o1, last, o3);
			Sector_read(o1, last);
		}
		else
		{
			cout << "데이터가 " << v1 << "번 Sector에 저장될 예정입니다." << endl; //psn input
			Sector_write(o1, v1, o3);
			Sector_read(o1, v1);
		}
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
		erase_index = v1;
	}
	else
	{
		cout << "할당된 저장소를 초과한 공간의 데이터를 지우고자 하였습니다. " << endl; //Err
	}
}

void Print_Table(vector<int>& o1, const string& o2)
{
	if (pos)
	{
		if (o2 == "sector")
		{
			SectorMap_Frame();
		}
		else if (o2 == "block")
		{
			BlockMap_Frame();
		}
		else
		{
			cout << "Flash Memory 할당이 되어있지 않습니다. 확인 후 재실행해주세요. " << endl;
			return;
		}
		for (unsigned int i = 0; i < o1.size(); i++)
		{
			if (o2 =="sector" && i != 0 && i % 2048 == 0)
			{
				system("pause");
			}
			cout.width(3);
			cout << i;
			cout.width(8);
			cout << o1.at(i) << endl;;
		}
	}

}

void FTL_read(Flash*& o1, vector<int>& o2, int& v1, const string& o3)
{
	if (o3 == "sector" && pos && v1 < secsize) //input limit
	{
		Flash_read(o1, o2.at(v1));
	}
	else if (o3 == "block" && pos && v1 < secsize) //need Trusted Solver
	{
		int lbn = 0, offset = 0, psn = 0;
		offset_calc(v1, lbn, offset); //lsn, lbn, offset
		psn = o2.at(lbn) * 32 + offset;
		Flash_read(o1, psn); //Flash, psn
	}
	else
	{
		cout << "잘못된 영역에 액세스하려고 했습니다." << endl;
	}
}

void FTL_write(Flash*& o1, vector<int>& o2, int& v1, const string& o3, const string& o4) //lsn input
{
	if (o4 == "sector" && pos && v1 < secsize)
	{
		Flash_write(o1, o2, o2.at(v1), o3, o4); //Flash, Table, psn, data, sector
	}
	else if (o4 == "block" && pos && v1 < secsize) //need Trusted Solver
	{
		int lbn = 0, offset = 0, psn = 0;
		offset_calc(v1, lbn, offset); //lsn, lbn, offset
		psn = o2.at(lbn) * 32 + offset;
		Flash_write(o1, o2, psn, o3, o4); //Flash, psn, data, block
	}
	else
	{
		cout << "잘못된 영역에 액세스하려고 했습니다." << endl;
	}
}

void Sec_Func(Flash*& o1, vector<int>& o2)
{
	string Input1 = "", Input2 = "", Input3 = ""; //write data!!
	while (Input1 != "exit" && Input1 != "Exit" && Input1 != "EXIT")
	{
		cout << "시뮬레이션 하고 싶은 명령을 내려주세요. (init, read, write, table, exit)" << endl;
		Input_Func(Input1, 6); //maximum length set
		if (Input1 == "init" || Input1 == "Init" || Input1 == "INIT") //if init + Eng Input?? => Error
		{
			Input_Func(Input2, 3); // xxxMB
			int temp = Conv__Func(Input2); //Mem Size
			if (temp == -1 || temp < 0)
			{
				continue;
			}
			init(o1, o2, "sector", temp);
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
			//FTL_read fun
			Gavage_erase(o1, o2);
			FTL_read(o1, o2, temp, "sector");
			IO_Check();
			Saved_Clear();
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
			//FTL_write fun
			FTL_write(o1, o2, temp, Input3, "sector");
			Input3 = ""; //Write에서만 사용되기에 상관은 없지만...
			IO_Check();
			Saved_Clear();
		}
		else if (Input1 == "table" || Input1 == "Table" || Input1 == "TABLE")
		{
			Gavage_erase(o1, o2);
			Print_Table(o2, "sector");
		}
		else
		{
			continue;
		}
	}
	if (pos)
	{
		Gavage_erase(o1, o2);
		SecSave_Func(o1, "SecData.txt");
		TableSave_func(o2, "SecTable.txt", "SecMap_Info.txt");
		secsize = 0;
		o2.clear();
		delete[] pos;
		pos = nullptr;
	}
}
void Blk_Func(Flash*& o1, vector<int>& o2)
{
	string Input1 = "", Input2 = "", Input3 = ""; //write data!!
	while (Input1 != "exit" && Input1 != "Exit" && Input1 != "EXIT")
	{
		cout << "시뮬레이션 하고 싶은 명령을 내려주세요. (init, read, write, table, exit)" << endl;
		Input_Func(Input1, 6); //maximum length set
		if (Input1 == "init" || Input1 == "Init" || Input1 == "INIT") //if init + Eng Input?? => Error
		{
			Input_Func(Input2, 3); // xxxMB
			int temp = Conv__Func(Input2); //Mem Size
			if (temp == -1 || temp < 0)
			{
				continue;
			}
			init(o1, o2, "block", temp);
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
			//FTL_read fun
			FTL_read(o1, o2, temp, "block");
			IO_Check();
			Saved_Clear();
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
			//FTL_write fun
			FTL_write(o1, o2, temp, Input3, "block");
			Input3 = ""; //Write에서만 사용되기에 상관은 없지만...
			IO_Check();
			Saved_Clear();
		}
		else if (Input1 == "table" || Input1 == "Table" || Input1 == "TABLE")
		{
			Print_Table(o2, "sector");
		}
		else
		{
			continue;
		}
	}
	if (pos)
	{
		Gavage_erase(o1, o2);
		SecSave_Func(o1, "BlockData.txt");
		TableSave_func(o2, "BlockTable.txt", "BlockMap_Info.txt");
		secsize = 0;
		o2.clear();
		delete[] pos;
		pos = nullptr;
	}
}

void Select_Func(Flash*& o1, vector<int>& o2) //동시에 1개의 에뮬레이션만 가능하기에
{
	string Input1 = "";
	while (true)
	{
		cout << "FTL Mapping 방식을 선택하세요. (sector, block, exit)" << endl;
		Input_Func(Input1, 6);
		Exit_Func(Input1);
		if (Input1 == "sector" || Input1 == "Sector" || Input1 == "SECTOR")
		{
			//sec mapping table load func, auto init, auto restore
			TableLoad_func(o2, "SecTable.txt", "SecMap_Info.txt");
			if (secsize != 0 && !pos)
			{
				int temp = secsize / 2048;
				init(o1, o2, "sector", temp);
				pos = o1;
				//secdata load func
				SecLoad_Func(o1, "SecData.txt");
			}
			Sec_Func(o1, o2);
		}
		else if (Input1 == "block" || Input1 == "Block" || Input1 == "BLOCK")
		{
			//blk mapping table load func, allocation needs!
			TableLoad_func(o2, "BlockTable.txt", "BlockMap_Info.txt");
			if (secsize != 0 && !pos)
			{
				int temp = secsize / 2048;
				init(o1, o2, "block", temp);
				pos = o1;
				//blkdata load func
				SecLoad_Func(o1, "BlockData.txt");
			}
			Blk_Func(o1, o2);
		}
	}
}

int main()
{
	Flash* data;
	vector<int> table;
	Select_Func(data, table);
}
