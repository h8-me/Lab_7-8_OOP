#pragma once
#include <iostream>
#include <vector>


template <typename T>
class Multitude
{
	std::vector<T> multitude;
	std::vector<T> previous;
	std::vector<T> previous1; //������� ������
public:
	Multitude() {}

	Multitude(const Multitude<T>& mt)
	{
		(*this) = mt;
	}

	const bool contains(const T& element) const//��������� ����������� �� ������� �� ���������
	{
		for (auto& el : multitude)
		{
			if (el == element) { return true; }
		}
		return false;
	}

	const T operator[](size_t index)const//���������� ������� �� �������
	{
		return this->multitude[index];
	}

	void output() const
	{
		for (const auto & el : this->multitude)//����� ������
		{
			cout << el << " ";
		}
	}

	void inputVariable(const char* msg, int* var, int min, int max) {
		while (true) {
			std::cout << msg;
			std::cin >> *var;
			if (std::cin.good() && *var >= min && *var <= max) return;
			else {
				std::cout << "������� �����!" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}
	}

	const size_t size() const//���������� ������ ���������
	{
		return this->multitude.size();
	}

	void remove(const T& element)//������� �������,���� �� ���� � ������ ���������� ���� ��� ���
	{
		this->previous = this->multitude;
		for (auto el = this->multitude.begin(); el != this->multitude.end(); ++el)
		{
			if (*el == element) { this->multitude.erase(el); return; }
		}
		throw std::exception("��������� �� �������� ���������� ��������!");
	}

	Multitude<T>& operator+=(const T& element)//���������� �������� � ���������
	{
		this->previous = this->multitude;
		this->multitude.push_back(element);
		return (*this);
	}
	Multitude<T>& operator=(const Multitude<T>& element)//�������� �����
	{
		this->previous = this->multitude;
		this->multitude = element.returnVector();
		return (*this);
	}
	const std::vector<T> returnVector()const//���������� ���������
	{
		return this->multitude;
	}
	void input()//���� ���������
	{
		int SIZE;
		inputVariable("������� ������ ��������� = ", &SIZE, 1, 200);
		this->multitude = std::vector<T>(SIZE);
		for (int i = 0; i < SIZE; ++i)
		{
			std::cout << i + 1 << " ������� = ";
			std::cin >> this->multitude[i];
		}
	}
	friend Multitude<T> operator * (const Multitude<T>& mt1, const Multitude<T>& mt2)
	{
		Multitude<T> newM;//����� ����������� ��������
		for (int i = 0; i < mt1.size(); ++i)
		{
			for (int j = 0; j < mt2.size(); ++j)
			{
				if (mt1[i] == mt2[j] && !(newM.contains(mt1[i]))) 
				{ 
					newM += mt1[i]; 
					break;
				}
			}
		}
		return newM;
	}
	static void tranzaction(Multitude<T>& mt1, T element1, Multitude<T>& mt2, T element2)
	{
		mt1.previous1 = mt1.multitude;
		mt1.remove(element1);//���������� - ������� �� ������ ���������,��������� � ������
		mt1 += element2;
		mt2.previous1 = mt2.multitude;
		mt2.remove(element2); //���������� - ������� �� ������ ���������,��������� � ������
		mt2 += element1;

	}

	void cancelTransaction() {
		this->multitude = this->previous1;
	}
};


