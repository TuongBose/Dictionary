#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#define MAX 503

using namespace std;

struct Word
{
	string eng;
	string mean;
};

struct DictNode
{
	Word word;
	DictNode* next;
};
//Khởi tạo Hashmap
void initDict(DictNode* dicts[])
{
	for (int i = 0; i < MAX; i++)
	{
		dicts[i] = NULL;
	}
}
int isEmpty(DictNode* dicts[])
{
	for (int i = 0; i < MAX; i++)
	{
		if (dicts[i] != NULL) return 0;
	}
	return 1;
}
//Hàm băm
int hashFunc(Word w)
{
	int h = 0;
	for (int i = 0; i < w.eng.length(); i++)
		h += (int)tolower(w.eng[i]) * (i + 1);
	return h % MAX;
}
//hàm tạo Từ
DictNode* createWord(Word w)
{
	DictNode* NewWord = new DictNode;
	NewWord->word = w;
	NewWord->next = NULL;
	return NewWord;
}
//hàm thêm từ 
void addWord1(DictNode* dicts[], Word w)
{
	int h = hashFunc(w);
	DictNode* p = dicts[h];
	DictNode* r = createWord(w);
	if (p == NULL)
		dicts[h] = r;
	else
	{
		while (p->next != NULL)
			p = p->next;
		p->next = r;
	}
}


int hashFunc2(string w)
{
	int h = 0;
	for (int i = 0; i < w.length(); i++)
		h += (int)tolower(w[i]) * (i + 1);
	return h % MAX;
}

void TYPE(string& str)
{
	for (int i = 0; i <= str.length(); i++) {
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
	}
}
int search(DictNode* dicts[], string w)
{
	TYPE(w);
	int h = hashFunc2(w);
	DictNode* p = dicts[h];
	while (p != NULL)
	{
		TYPE(p->word.eng);
		int x;
		x = w.compare(p->word.eng); ;
		if (x == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

int searchMean(DictNode* dicts[], string w, Word& W)
{
	TYPE(w);
	int h = hashFunc2(w);
	DictNode* p = dicts[h];
	while (p != NULL)
	{
		TYPE(p->word.eng);
		int x;
		x = w.compare(p->word.eng); ;
		if (x == 0)
		{
			W = p->word;
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//Ham chuan hoa cac ky tu va chu so
void chuanhoa(string& word)
{
	int i;
	for (i = 0; i < word.length(); i++)
	{
		if (word[i] == ',' || word[i] == '.' || (word[i] >= '0' && word[i] <= '9') || word[i] == ' ')
			break;
	}
	word.erase(i, word.length());
}
// hàm đọc file từ điển
int readFileDic(DictNode* dicts[])
{
	ifstream f;
	string a;
	cout << "\nNhap file can doc: ";
	cin >> a;
	f.open(a, ios::in);
	if (!f.is_open()) return 0;
	while (!f.eof())
	{
		Word w;
		getline(f, w.eng);
		getline(f, w.mean);
		addWord1(dicts, w);
	}
	f.close();
	return 1;
}
// hàm kiểm tra từ chưa xuất hiện trong từ điển của file và thêm vào trong từ điển
void readfileDoc(DictNode* dicts[])
{
	ifstream f;
	f.open("VB.txt", ios::in);
	cout << "\n\n=================New Word=================" << endl;
	while (!f.eof())
	{
		Word w;
		f >> w.eng;
		chuanhoa(w.eng);
		TYPE(w.eng);
		if (w.eng.length() == 0) break;
		if (search(dicts, w.eng) == 0)
		{
			fflush(stdin);
			cout << '"' << w.eng << '"' << ": ";
			getline(cin, w.mean);
			addWord1(dicts, w);
		}
	}
	f.close();
}
// hàm đếm số từ chưa xuất hiện trong từ điển của file
int count(DictNode* dicts[])
{
	int count = 0;

	ifstream f;
	f.open("VB.txt", ios::in);
	if (!f.is_open()) return -1;
	else
	{
		while (!f.eof())
		{
			fflush(stdin);
			string w;
			f >> w;
			chuanhoa(w);
			if (w.length() == 0) break;
			if (search(dicts, w) == 0)
			{
				cout << "\n" << count << w;
				count++;
			}
		}
	}
	f.close();
	return count;
}
void Delete(DictNode* dicts[]) {
	string en;
	cout << "\nNhap tu xoa:";
	cin >> en;
	int h = hashFunc2(en);
	DictNode* r = dicts[h];
	DictNode* prev = NULL;

	while (r != NULL) {
		if (r->word.eng.compare(en) == 0) {
			if (prev == NULL)
				dicts[h] = r->next;
			else
				prev->next = r->next;
			r->next = NULL;
			delete(r);
			cout << "Da xoa thanh cong";
			break;
		}
		prev = r;
		r = r->next;
	}
	if (r == NULL) cout << "Khong tim thay tu xoa";
}
int display(DictNode* dicts[])
{
	if (isEmpty(dicts) == 1) return 0;
	else
	{
		cout << "\n================================TU DIEN================================\n";
		for (int i = 0; i < MAX; i++)
		{
			if (dicts[i] != NULL)
			{
				cout << "==============PAGE " << i << "==============" << endl;
				DictNode* p = dicts[i];
				while (p != NULL)
				{
					cout << "  " << p->word.eng << ": " << p->word.mean << endl;
					p = p->next;
				}
			}
		}
		cout << "=================================KET THUC================================\n";
	}
	return 1;
}
int updateMean(DictNode* dicts[], Word w)
{
	int h = hashFunc(w);
	TYPE(w.eng);
	DictNode* p = dicts[h];
	if (p != NULL)
	{
		do
		{
			if (p->word.eng.compare(w.eng) == 0)
			{
				p->word = w;
				return 1;
			}
			else
				p = p->next;
		} while (p->next != NULL);
	}
	return 0;
}
int deleteWord(DictNode* dicts[], string w)
{
	int h = hashFunc2(w);
	TYPE(w);
	DictNode* p = dicts[h];
	DictNode* prev = NULL;
	while (p != NULL)
	{
		if (w.compare(p->word.eng) == 0)
		{
			if (prev == NULL)
				dicts[h] = p->next;
			else
				prev->next = p->next;
			delete(p);
			return 1;
		}
		prev = p;
		p = p->next;
	}
	return 0;
}
void MENU()
{
	cout << "\n=================================MENU=================================";
	cout << "\n1.  Xem MENU";
	cout << "\n2.  Doc file du lieu txt tao ra bang bam";
	//cout<<"\n3.  Tang kich thuoc cua bang bam khi vuot nguong luu tru";
	cout << "\n4.  Tim kiem nghia cua 1 tu trong bang bam";
	cout << "\n5.  Doc vao 1 doan van ban, dem so tu khong xuat hien trong bang bam";
	cout << "\n6.  Them tat ca cac tu khong xuat hien vao bang bam";
	cout << "\n7.  Nhap vao 1 tu bat ki tim va xoa no neu tim thay";
	cout << "\n8.  Liet ke cac tu trong bang bam";
	cout << "\n9.  Dieu chinh nghia cua tu trong bang bam";
	cout << "\n10. Xoa mot tu ra khoi bang bam";
	cout << "\n11. Don sach man hinh console";
	cout << "\n0.  Thoat";
	cout << "\n================================THE-END===============================";

}
int main()
{
	DictNode* dicts[MAX];
	initDict(dicts);
	Word w;
	string word;
	int chon, x;
	MENU();
	while (true)
	{
		cout << "\n\n===========>>Nhap vao thao tac: ";
		cin >> chon;
		switch (chon)
		{
		case 1:
			MENU();
			break;
		case 2:
			if (readFileDic(dicts) == 1)
				cout << "\nDoc FILE va them vao tu dien thanh cong";
			else
				cout << "\nDoc FILE that bai!!!";
			break;
		case 4:
			cout << "\nNhap vao tu muon tim nghia: ";
			cin >> word;
			if (searchMean(dicts, word, w) == 1)
			{
				cout << "\nDA TIM THAY\n";
				cout << w.eng << " : " << w.mean;
			}
			else
			{
				cout << "\nKHONG TIM THAY";
				cout << "\nTu khong co trong tu dien";
			}
			break;
		case 5:
			x = count(dicts);
			if (x == -1)
				cout << "\nDoc FILE that bai!!!";
			else
				cout << "\nSo tu khong xuat hien trong TU DIEN la: " << x;
			break;
		case 6:
			readfileDoc(dicts);
			break;
		case 7:
			Delete(dicts);
			break;
		case 8:
			if (display(dicts) == 0)
				cout << "\nTU DIEN RONG";
			break;
		case 9:
			cout << "\n\tNhap vao tu muon dieu chinh: ";
			cin >> w.eng;
			fflush(stdin);
			cout << "\n\tNhap vao nghia cua tu dieu chinh: ";
			getline(cin, w.mean);
			if (updateMean(dicts, w) == 1)
				cout << "\nChinh sua thanh cong";
			else
			{
				cout << "\nKhong tim thay tu " << w.eng << " trong tu dien";
				cout << "\nChinh sua that bai";
			}
			break;
		case 10:
			cout << "\n\tNhap vao tu muon Xoa: ";
			cin >> w.eng;
			if (deleteWord(dicts, w.eng) == 1)
				cout << "Xoa thanh cong";
			else
			{
				cout << "\nKhong tim thay tu " << w.eng << " trong tu dien";
				cout << "\nXoa that bai";
			}
			break;
		case 11:
			system("cls");
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
	return 0;
}