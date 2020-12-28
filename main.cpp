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
		cout << "Пересечение = ";
		(mt1 * mt2).output();
		cout << "\n";
		int temp1, temp2;
		cout << "Хотите добавить элемент в множество 1 (0/1): ";
		cin >> temp1;

		if (temp1)
		{
			cout << "Введите элемент: ";
			cin >> temp1;
			mt1 += temp1;
		}
		cout << "Хотите добавить элемент в множество 2 (0/1): ";
		cin >> temp2;
		if (temp2)
		{
			cout << "Введите элемент: ";
			cin >> temp2;
			mt2 += temp2;
		}
		cout << "Хотите удалить элемент из множества 1 (0/1): ";
		cin >> temp1;
		if (temp1)
		{
			cout << "Введите элемент: ";
			cin >> temp1;
			mt1.remove(temp1);
		}
		cout << "Хотите удалить элемент из множества 2 (0/1): ";
		cin >> temp2;
		if (temp2)
		{
			cout << "Введите элемент: ";
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
		cout << "Хотите выполнить транзакцию (0/1): ";
		cin >> tranz;
		if (tranz)
		{
			cout << "Введите элемент для транзакции из 1 множества : ";
			cin >> temp1;
			cout << "Введите элемент для транзакции из 2 множества : ";
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
			cout << "Хотите выполнить откат транзакции (0/1): ";
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