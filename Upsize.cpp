#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Word
{
	string eng;
	string mean;
};


// tạo Hashmap
Word* createHashMap(int n)
{
	Word* dicts = new Word[n];
	return dicts;
}
//Khởi tạo HashMap
void initDict(Word* dicts, int n)
{
	Word w;
	w.eng = " ";
	w.mean = " ";
	for (int i = 0; i < n; i++)
	{
		dicts[i] = w;
	}
}
//Kiểm tra rỗng
int isEmpty(Word* dicts, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (dicts[i].eng.compare(" ") != 0) return 0;
	}
	return 1;
}
//Kiểm tra đầy
int isFull(Word* dicts, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (dicts[i].eng.compare(" ") == 0) return 0;
	}
	return 1;
}
//hàm băm
int hashFunc(Word w, int n)
{
	int h = 0;
	for (int i = 0; i < w.eng.length(); i++)
		h += (int)tolower(w.eng[i]) * (i + 1);
	return h % n;
}
//hàm thêm từ 
void addWord1(Word* dicts, int n, Word w)
{
	int h = hashFunc(w, n);
	bool flag = false;
	if (dicts[h].eng.compare(" ") == 0)
		dicts[h] = w;
	else
	{
		for (int i = h + 1; i < n; i++)
		{
			if (dicts[i].eng.compare(" ") == 0)
			{
				dicts[i] = w;
				flag = true;
				break;
			}
		}
		if (flag == false)
			for (int i = 0; i < h; i++)
			{
				if (dicts[i].eng.compare(" ") == 0)
				{
					dicts[i] = w;
					break;
				}
			}
	}
}
//hàm copy hashmap
void CopyDict(Word* p, Word* temp, int& n)
{
	for (int i = 0; i < n / 2; i++)
	{
		addWord1(temp, n, p[i]);
	}
}
//hàm tăng kích thước
Word* Upsize(Word* dicts, int& n)
{
	n = n * 2;
	Word* newdicts = new Word[n];
	initDict(newdicts, n);
	CopyDict(dicts, newdicts, n);
	return newdicts;
}

int display(Word* dicts, int n)
{
	if (isEmpty(dicts, n) == 1) return 0;
	else
	{
		cout << "\n================================TU DIEN================================\n";
		for (int i = 0; i < n; i++)
		{
			if (dicts[i].eng.compare(" ") != 0)
			{
				cout << "==============PAGE " << i << "==============" << endl;

				cout << "  " << dicts[i].eng << ": " << dicts[i].mean << endl;

			}
		}
		cout << "=================================KET THUC================================\n";
	}
	return 1;
}

void MENU()
{
	cout << "\n=================================MENU=================================";
	cout << "\n1.  Them tu";
	cout << "\n2.  UpSize HashMap";
	cout << "\n3.  Liet ke cac tu trong HashMap";
	cout << "\n0.  Thoat";
	cout << "\n================================THE-END===============================";
}
void main()
{
	Word w;
	int n, chon;
	cout << "\nNhap vao kich thuoc HashMap: ";
	cin >> n;
	Word* dicts = createHashMap(n);
	initDict(dicts, n);
	while (true)
	{
		MENU();
		cout << "\n\n===========>>Nhap vao thao tac: ";
		cin >> chon;
		switch (chon)
		{
		case 1:
			if (isFull(dicts, n) == 0)
			{
				cout << "\nNhap tu Tieng Anh: "; cin >> w.eng;
				fflush(stdin);
				cout << "\nNhap tu Tieng Viet: "; getline(cin, w.mean);
				addWord1(dicts, n, w);
				cout << "\nThem vao thanh cong";
			}
			else
			{
				cout << "\nTu dien da FULL";
				cout << "\nXin hay Upsize";
			}
			break;
		case 2:
			if (isFull(dicts, n) == 1)
			{
				dicts = Upsize(dicts, n);
				cout << "\nUpSize thanh cong";
			}
			else
			{
				cout << "\nTu dien chua FULL";
				cout << "\nCon them tu duoc";
			}
			break;
		case 3:
			display(dicts, n);
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "\nKhong co thao tac " << chon;
			cout << "\nVUI LONG NHAP LAI!!!";
			break;
		}
	}
	system("pause");
}


