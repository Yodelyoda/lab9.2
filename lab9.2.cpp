#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;
enum Spec { KOMPNAUK, INFORMAT, TRUDOVIK, FIZIK, MATEM };
string specStr[] = { "���������� �����", "������������", "����������� �� ��������","�Գ���� �� �����������","�������� ���������" };
struct Student
{
	string prizv;
	unsigned kurs;
	unsigned nomer;
	Spec spec;
	int SERrate;
	int FIZrate;
	int MATrate;
	union
	{
		int PEDArate;
		int PROGrate;
		int CHISLrate;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv,int SERrate,int TRIrate, const Spec spec);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{ // ������������ ����������� ��������:
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
	int N;
	string prizv;
	int ispec;
	Spec spec;
	int SERrate;
	int TRIrate;
	int found;
	cout << "������ ������� ��������: "; cin >> N;
	Student* p = new Student[N];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� ������ �� ��������� ���������� ����,�� ������� �� ����� �������,�� �������� �� ���������" << endl;
		cout << " [4] - ������� ����� �������� �� ������� ����� �� ������� �� ����� �������" << endl;
		cout << " [5] - �������� ������������� �� ���� �����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
				cout << "������ ����� ������:" << endl;
				cout << "������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 -������� �������� ): ";
				cin >> ispec;
				spec = (Spec)ispec;
				cin.get(); // ������� ����� ��������� � �� ����������� �������
				cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
				cout << " �������: "; getline(cin, prizv);
				cout << " ������� ������: "; cin >> SERrate;
				cout << " ������ �� ����� �������: "; cin >> TRIrate;
				cout << endl;
				if ((found = BinSearch(p, N, prizv, SERrate, TRIrate, spec)) != -1)
					cout << "�������� �������� � ������� " << found + 1 << endl;
				else
					cout << "�������� �������� �� ��������" << endl;
				break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "������� No " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ����: "; cin >> p[i].kurs;
		cout << " ���������� ����� �������� � ����: "; cin >> p[i].nomer;
		cout << " ������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 -������� �������� ): ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		switch (p[i].spec)
		{
		case KOMPNAUK:
			cout << " ������ � ������ : "; cin >> p[i].FIZrate;
			cout << " ������ � ���������� : "; cin >> p[i].MATrate;
			cout << " ������ � ������������� : "; cin >> p[i].PROGrate;
			p[i].SERrate = ((p[i].FIZrate + p[i].MATrate + p[i].PROGrate) / 3.0);
			cout << " ������� ������ = "<< p[i].SERrate;
			break;
		case INFORMAT:
			cout << " ������ � ������ : "; cin >> p[i].FIZrate;
			cout << " ������ � ���������� : "; cin >> p[i].MATrate;
			cout << " ������ � ��������� ������ : "; cin >> p[i].CHISLrate;
			p[i].SERrate = ((p[i].FIZrate + p[i].MATrate + p[i].CHISLrate) / 3.0);
			cout << " ������� ������ = " << p[i].SERrate;
			break;
		case TRUDOVIK:
			cout << " ������ � ������ : "; cin >> p[i].FIZrate;
			cout << " ������ � ���������� : "; cin >> p[i].MATrate;
			cout << " ������ � ��������� : "; cin >> p[i].PEDArate;
			p[i].SERrate = ((p[i].FIZrate + p[i].MATrate + p[i].PEDArate) / 3.0);
			cout << " ������� ������ = " << p[i].SERrate;
			break;
		case FIZIK:
			cout << " ������ � ������ : "; cin >> p[i].FIZrate;
			cout << " ������ � ���������� : "; cin >> p[i].MATrate;
			cout << " ������ � ��������� : "; cin >> p[i].PEDArate;
			p[i].SERrate = ((p[i].FIZrate + p[i].MATrate + p[i].PEDArate) / 3.0);
			cout << " ������� ������ = " << p[i].SERrate;
			break;
		case MATEM:
			cout << " ������ � ������ : "; cin >> p[i].FIZrate;
			cout << " ������ � ���������� : "; cin >> p[i].MATrate;
			cout << " ������ � ��������� : "; cin >> p[i].PEDArate;
			p[i].SERrate = ((p[i].FIZrate + p[i].MATrate + p[i].PEDArate) / 3.0);
			cout << " ������� ������ = " << p[i].SERrate;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "====================================================================================================================================================================================================="
		<< endl;
	cout << "| No | ������� | ���� | ���������� ����� �������� � ���� | ������������ | ������ � ������ | ������ � ���������� | ������ � ��������� ������ | ������ � ������������� | ������ � ���������|"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(4) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(6) << left << p[i].kurs
			<< "| " << setw(36) << right << p[i].nomer
			<< "| " << setw(20) << left << specStr[p[i].spec]
			<< "| " << setw(11) << right << p[i].FIZrate
			<< "| " << setw(11) << right << p[i].MATrate;
		switch (p[i].spec)
		{
		case KOMPNAUK:
			cout << "| " << setw(11) << right << "|" << " " << setw(8) << right << p[i].PROGrate << " |" << setw(11) << right << "|" << endl;
			break;
		case INFORMAT:
			cout << "| " << " " << setw(8) << right << p[i].CHISLrate << "|" << setw(11) << right << "|" << setw(11) << right << "|" << endl;
		case TRUDOVIK:
		case FIZIK:
		case MATEM:
			cout << "| " << setw(11) << right << "|" << setw(11) << right << "|" << " " << setw(8) << right << p[i].PEDArate << " |" << endl;
			break;
		}
	}
	cout << "====================================================================================================================================================================================================="
		<< endl;
	cout << endl;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i = 0; i < N; i++)
	{
		if (p[i].spec == KOMPNAUK)
		{
			for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
				for (int i1 = 0; i1 < N - i0 - 1; i1++)
					if ((p[i1].SERrate < p[i1 + 1].SERrate)
						||
						(p[i1].SERrate == p[i1 + 1].SERrate &&
							p[i1].PROGrate < p[i1 + 1].PROGrate)
						||
						(p[i1].SERrate == p[i1 + 1].SERrate &&
							p[i1].PROGrate == p[i1 + 1].PROGrate &&
							p[i1].prizv < p[i1 + 1].prizv))
					{
						tmp = p[i1];
						p[i1] = p[i1 + 1];
						p[i1 + 1] = tmp;
					}
		}
		if (p[i].spec == INFORMAT)
		{
			for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
				for (int i1 = 0; i1 < N - i0 - 1; i1++)
					if ((p[i1].SERrate > p[i1 + 1].SERrate)
						||
						(p[i1].SERrate == p[i1 + 1].SERrate &&
							p[i1].CHISLrate > p[i1 + 1].CHISLrate)
						||
						(p[i1].SERrate == p[i1 + 1].SERrate &&
							p[i1].CHISLrate == p[i1 + 1].CHISLrate &&
							p[i1].prizv < p[i1 + 1].prizv))
					{
						tmp = p[i1];
						p[i1] = p[i1 + 1];
						p[i1 + 1] = tmp;
					}
		}
		if (p[i].spec == TRUDOVIK || p[i].spec == FIZIK || p[i].spec == MATEM)
		{
			for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
				for (int i1 = 0; i1 < N - i0 - 1; i1++)
					if ((p[i1].SERrate > p[i1 + 1].SERrate)
						||
						(p[i1].SERrate == p[i1 + 1].SERrate &&
							p[i1].PEDArate > p[i1 + 1].PEDArate)
						||
						(p[i1].SERrate == p[i1 + 1].SERrate &&
							p[i1].PEDArate == p[i1 + 1].PEDArate &&
							p[i1].prizv < p[i1 + 1].prizv))
					{
						tmp = p[i1];
						p[i1] = p[i1 + 1];
						p[i1 + 1] = tmp;
					}
		}
	}
}
int BinSearch(Student* p, const int N, const string prizv,int SERrate,int TRIrate, const Spec spec)
{ 
	int L = 0, R = N - 1, m;
	
		do {
				m = (L + R) / 2;
				if (p[m].spec == KOMPNAUK)
			{
				if (p[m].prizv == prizv && p[m].PROGrate == TRIrate && p[m].SERrate == SERrate)
					return m;
				if ((p[m].PROGrate < TRIrate)
					||
					(p[m].PROGrate == TRIrate &&
						p[m].prizv < prizv)
					||
					(p[m].PROGrate == TRIrate &&
						p[m].prizv == prizv &&
						p[m].SERrate < SERrate))
				{
					L = m + 1;
				}
				else
				{
					R = m - 1;
				}
			}
			if (p[m].spec == INFORMAT)
			{
				if (p[m].prizv == prizv && p[m].PROGrate == TRIrate && p[m].SERrate == SERrate)
					return m;
				if ((p[m].CHISLrate < TRIrate)
					||
					(p[m].CHISLrate == TRIrate &&
						p[m].prizv < prizv)
					||
					(p[m].CHISLrate == TRIrate &&
						p[m].prizv == prizv &&
						p[m].SERrate < SERrate))
				{
					L = m + 1;
				}
				else
				{
					R = m - 1;
				}
			}
			if (p[m].spec == TRUDOVIK || p[m].spec == FIZIK || p[m].spec == MATEM)
			{
				if (p[m].prizv == prizv && p[m].PROGrate == TRIrate && p[m].SERrate == SERrate)
					return m;
				if ((p[m].PEDArate < TRIrate)
					||
					(p[m].PEDArate == TRIrate &&
						p[m].prizv < prizv)
					||
					(p[m].PEDArate == TRIrate &&
						p[m].prizv == prizv &&
						p[m].SERrate < SERrate))
				{
					L = m + 1;
				}
				else
				{
					R = m - 1;
				}
			}
		} while (L <= R);
	return -1;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "====================================================================================================================================================================================================="
		<< endl;
	cout << "| No | ������� | ���� | ���������� ����� �������� � ���� | ������������ | ������ � ������ | ������ � ���������� | ������ � ��������� ������ | ������ � ������������� | ������ � ���������|"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(4) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(6) << left << p[I[i]].kurs
			<< "| " << setw(36) << right << p[I[i]].nomer
			<< "| " << setw(20) << left << specStr[p[I[i]].spec]
			<< "| " << setw(11) << right << p[I[i]].FIZrate
			<< "| " << setw(11) << right << p[I[i]].MATrate;
		switch (p[I[i]].spec)
		{
		case KOMPNAUK:
			cout << "| " << setw(11) << right << "|" << " " << setw(8) << right << p[I[i]].PROGrate << " |" << setw(11) << right << "|" << endl;
			break;
		case INFORMAT:
			cout << "| " << " " << setw(8) << right << p[I[i]].CHISLrate << "|" << setw(11) << right << "|" << setw(11) << right << "|" << endl;
		case TRUDOVIK:
		case FIZIK:
		case MATEM:
			cout << "| " << setw(11) << right << "|" << setw(11) << right << "|" << " " << setw(8) << right << p[I[i]].PEDArate << " |" << endl;
			break;
		}
	}
	cout << "====================================================================================================================================================================================================="
		<< endl;
	cout << endl;
}
int *IndexSort(Student *p, const int N)
{ 
int *I = new int[N]; // �������� ��������� �����
for (int i=0; i<N; i++)
I[i]=i; // ��������� ���� ����������� ������
int i, j, value; // �������� ��������� ����� �������
for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].SERrate > p[value].SERrate) ||
			(p[I[j]].SERrate == p[value].SERrate &&
				p[I[j]].PROGrate > p[value].PROGrate)||
				(p[I[j]].SERrate == p[value].SERrate &&
					p[I[j]].PROGrate == p[value].PROGrate &&
					p[I[j]].prizv > p[value].prizv)||
					(p[I[j]].SERrate == p[value].SERrate &&
						p[I[j]].CHISLrate > p[value].CHISLrate) ||
						(p[I[j]].SERrate == p[value].SERrate &&
							p[I[j]].CHISLrate == p[value].CHISLrate &&
							p[I[j]].prizv > p[value].prizv)||
							(p[I[j]].SERrate == p[value].SERrate &&
								p[I[j]].PEDArate > p[value].PEDArate) ||
								(p[I[j]].SERrate == p[value].SERrate &&
									p[I[j]].PEDArate == p[value].PEDArate &&
									p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
}
return I;
}