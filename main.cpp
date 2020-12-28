#include <iostream>
#include <string>
#include "Multitude.h"

using namespace std;

int main()
{
	setlocale(LC_ALL,"Russian");
	try
	{
		Multitude<int> mt1, mt2;
		mt1.input();
		mt2.input();
		cout << "����������� = ";
		(mt1 * mt2).output();
		cout << "\n";
		int temp1, temp2;
		cout << "������ �������� ������� � ��������� 1 (0/1): ";
		cin >> temp1;

		if (temp1)
		{
			cout << "������� �������: ";
			cin >> temp1;
			mt1 += temp1;
		}
		cout << "������ �������� ������� � ��������� 2 (0/1): ";
		cin >> temp2;
		if (temp2)
		{
			cout << "������� �������: ";
			cin >> temp2;
			mt2 += temp2;
		}
		cout << "������ ������� ������� �� ��������� 1 (0/1): ";
		cin >> temp1;
		if (temp1)
		{
			cout << "������� �������: ";
			cin >> temp1;
			mt1.remove(temp1);
		}
		cout << "������ ������� ������� �� ��������� 2 (0/1): ";
		cin >> temp2;
		if (temp2)
		{
			cout << "������� �������: ";
			cin >> temp2;
			mt2.remove(temp2);
		}
		cout << "1 : ";
		mt1.output();
		cout << "\n";
		cout << "2 : ";
		mt2.output();
		cout << "\n";

		char tranz;
		cout << "������ ��������� ���������� (0/1): ";
		cin >> tranz;
		if (tranz)
		{
			cout << "������� ������� ��� ���������� �� 1 ��������� : ";
			cin >> temp1;
			cout << "������� ������� ��� ���������� �� 2 ��������� : ";
			cin >> temp2;
			Multitude<int>::tranzaction(mt1, temp1, mt2, temp2);
		}
		cout << "1 : ";
		mt1.output();
		cout << "\n";
		cout << "2 : ";
		mt2.output();
		cout << "\n";
		if (tranz) {
			cout << "������ ��������� ����� ���������� (0/1): ";
			cin >> temp1;
			if (temp1) {
				mt1.cancelTransaction();
				mt2.cancelTransaction();
				cout << "1 : ";
				mt1.output();
				cout << "\n";
				cout << "2 : ";
				mt2.output();
				cout << "\n";
			}
		}
	}
	catch (std::exception & ex) { cout << ex.what() << "\n"; }
	system("pause");
	return 0;
}