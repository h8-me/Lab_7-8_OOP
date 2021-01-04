#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Lot
{
public:
	class iterator;
	friend class iterator; 
private:
	class lot_node;
	friend class lot_node;

	class lot_node 
	{
	public:
		friend class Lot<T>;
		friend class iterator;
		lot_node(T node_val) : val(node_val) {}
		lot_node() {}
		~lot_node() { next = nullptr; prev = nullptr; }
		void print_val()
		{
			std::cout << val << " ";
		}
		lot_node* next; 
		lot_node* prev; 
		T val; 
	};

public:
	class iterator
	{
		friend class Lot <T>;

	public:
		iterator() :the_node(0) {}
		iterator(lot_node* dn) : the_node(dn) {}
		iterator(const iterator& it) : the_node(it.the_node) {}
		iterator& operator=(const iterator& it)
		{
			the_node = it.the_node;
			return *this;
		}
		bool operator == (const iterator& it) const
		{
			return (the_node == it.the_node);
		}
		bool operator!=(const iterator& it) const
		{
			return !(it == *this);
		}
		iterator& operator++()
		{
			if (the_node == 0)
				throw "Попытка увеличить пустой итератор";
			if (the_node->next == 0)
				throw "Слишком большое увелечение";

			the_node = the_node->next;
			return *this;
		}
		iterator& operator--()
		{
			if (the_node == 0)
				throw "Попытка уменьшить пустой итератор";
			if (the_node->prev == 0)
				throw "Попытка сделать меньше 1";
			the_node = the_node->prev;
			return *this;
		}
		T& operator*() const
		{
			if (the_node == 0)
				throw "Пустой итератор!";
			return the_node->val;
		}
	private:
		lot_node* the_node;
	};
	lot_node* head; 
	lot_node* tail;
	iterator head_iterator; 
	iterator tail_iterator; 
	Lot() 
	{
		head = tail = new lot_node;
		tail->next = 0;
		tail->prev = 0;
		head_iterator = iterator(head);
		tail_iterator = iterator(tail);
	}
	Lot(T node_val)
	{
		head = tail = new lot_node;
		tail->next = 0;
		tail->prev = 0;
		head_iterator = iterator(head);
		tail_iterator = iterator(tail);
		add_front(node_val);
	}
	~Lot()
	{
		for (; this->is_empty();)
		{
			this->remove_front();
		}
	}
	bool is_empty() { return head == tail; }
	iterator front() { return head_iterator; }
	iterator rear() { return tail_iterator; }
	void add_front(T node_val)
	{
		lot_node* node_to_add = new lot_node(node_val);
		node_to_add->next = head;
		node_to_add->prev = 0;
		head->prev = node_to_add;
		head = node_to_add;
		head_iterator = iterator(head);
	}
	void add_rear(T node_val) //при добовлении в конец
	{
		if (is_empty())
			add_front(node_val);
		else
		{
			lot_node* node_to_add = new lot_node(node_val);
			node_to_add->next = tail;
			node_to_add->prev = tail->prev;
			tail->prev->next = node_to_add;
			tail->prev = node_to_add;
			tail_iterator = iterator(tail);
		}
	}
	bool insert_after(T node_val, const iterator& key_i) //вставляет node_val после key_i
	{
		for (lot_node* dn = head; dn != tail; dn = dn->next)
		{
			if (dn == key_i.the_node)
			{
				lot_node* node_to_add = new lot_node(node_val);
				node_to_add->prev = dn;
				node_to_add->next = dn->next;
				dn->next->prev = node_to_add;
				dn->next = node_to_add;
				return true;
			}
		}
		return false;
	}
	void clear() //очищает
	{
		for (; this->is_empty();)
		{
			this->remove_front();
		}
	}
	T remove_front() 
	{
		if (is_empty())
		throw "Попытка удалить из пустого множества!";
		lot_node* node_to_remove = head;
		T return_val = node_to_remove->val;
		head = node_to_remove->next;
		head->prev = 0;
		head_iterator = iterator(head);

		delete node_to_remove;
		return return_val;

	}
	T remove(const T& element) //удаление
	{
		if (is_empty())
			throw "Попытка удалить из пустого множества!";
		
		for (lot_node* node_to_remove = head; node_to_remove != tail; node_to_remove = node_to_remove->next)
		{
			if (node_to_remove->val == element)
			{
				if (node_to_remove == head) { this->remove_front();}
				else if (node_to_remove == tail->prev) { this->remove_rear();}
				else
				{
					node_to_remove->prev->next = node_to_remove->next;
					node_to_remove->next->prev = node_to_remove->prev;
					node_to_remove->next = 0;
					node_to_remove->prev = 0;
				}
				break;
			}
		}
		
		return element;

	}
	T remove_rear() 
	{
		if (is_empty())
			throw "Попытка удалить из пустого множества!";

		lot_node* node_to_remove = tail->prev;

		if (node_to_remove->prev == 0)
		{
			return remove_front();
		}
		else
		{
			T return_val = node_to_remove->val;
			node_to_remove->prev->next = tail;
			tail->prev = node_to_remove->prev;
			delete node_to_remove;
			return return_val;
		}
	}
	iterator get_nth(const int element_num) const
	{
		int count = 0;
		for (lot_node* dn = head; dn != tail; dn = dn->next)
		{
			if (count == element_num)
				return iterator(dn);
			++count;
		}

		return this->tail_iterator;
	}
	bool contains(const T& element) const
	{
		int count = 0;
		for (lot_node* dn = head; dn != tail; dn = dn->next)
		{
			if (dn->val == element) { return true; }
		}

		return false;
	}
	int size() const
	{
		int count = 0;
		for (lot_node* dn = head; dn != tail; dn = dn->next)
			++count;
		return count;
	}
	void print() const
	{
		for (lot_node* dn = head; dn != tail; dn = dn->next)
		{
			dn->print_val();
		}
	}
};
template<typename T>
class Multitude
{
	Lot<T> previous;

public:
	Lot<T> multitude;
	Multitude() = default;

	Multitude(const Multitude<T>& mt)
	{
		(*this) = mt;
	}
	const bool contains(const T element) //проверка на наличие элемента в множестве
	{
		for (int i = 0; i < this->size(); ++i)
		{
			if (*multitude.get_nth(i) == element) { return true; }
		}
		return false;
	}
	void save() //сохранение множеств перед транзакцией
	{
		Lot<T> temp;
		for (int i = 0; i < this->size(); ++i)
		{
			temp.add_rear(*(this->multitude.get_nth(i)));
		}
		this->previous = temp;
	}
	void output()
	{
		for (int i = 0; i < this->size(); ++i)
		{
			std::cout << *(multitude.get_nth(i)) << " ";
		}
	}

	const size_t size() const
	{
		return this->multitude.size();
	}

	void remove(const T& element) //удаление
	{
		this->multitude.remove(element);
	}

	void reload()//откат
	{
		if (!(this->previous.is_empty()))
		{
			this->multitude = this->previous;
		}
		else
		{
			throw std::exception("Предидущее состояние не найдено!");
		}
	}
	Multitude<T> & operator+=(const T& element)
	{
		this->multitude.add_rear(element);
		return (*this);
	}
	Multitude<T> & operator=(const Multitude<T>& element)
	{
		this->multitude = element.multitude;
		return (*this);
	}
	
	void input() //добавелние 
	{
		T temp;
		size_t sizeOf;
		std::cout << "Размер множества: ";
		std::cin >> sizeOf;
		for (size_t i = 0; i < sizeOf; ++i)
		{
			std::cout << i + 1 << " Элемент: ";
			std::cin >> temp;
			this->multitude.add_rear(temp);
		}
	}
	static void trunzaction(Multitude<T>& mt1, T element1, Multitude<T>& mt2, T element2)
	{
		mt1.save();
		mt2.save();
		mt1.remove(element1); 
		mt1 += element2;
		mt2.remove(element2);
		mt2 += element1;
	}
};

template<class T>

void cross(const Multitude<T> &m1, const Multitude<T> & m2)
{
	Lot<T> temp;
	for (size_t i = 0; i < m1.size(); i++)
	{
		for (size_t j = 0; j < m2.size(); j++)
		{
			if (*m1.multitude.get_nth(i) == *m2.multitude.get_nth(j) && !(temp.contains(*(m1.multitude.get_nth(i)))))
			{
				temp.add_rear(*m1.multitude.get_nth(i));
				break;
			}
		}
	}
	temp.print();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	try
	{
		Multitude<int> mt1, mt2;
		mt1.input();
		mt2.input();
		cout << "Пересечение = ";
		cross(mt1,mt2);
		cout << "\n";
		int temp1, temp2, temp3;
		cout << "Хотите ли добавить элемент а множество 1 (0/1): ";
		cin >> temp1;
		if (temp1)
		{
			cout << "Элемент: ";
			cin >> temp1;
			mt1 += temp1;
		}
		cout << "Хотите ли добавить элемент а множество 2 (0/1): ";
		cin >> temp2;
		if (temp2)
		{
			cout << "Элемент: ";
			cin >> temp2;
			mt2 += temp2;
		}

		cout << "Хотите ли удалить элемент из множества 1 (0/1): ";
		cin >> temp1;
		if (temp1)
		{
			cout << "Элемент: ";
			cin >> temp1;
			mt1.remove(temp1);
		}
		cout << "Хотите ли удалить элемент из множества 2 (0/1): ";
		cin >> temp2;
		if (temp2)
		{
			cout << "Элемент: ";
			cin >> temp2;
			mt2.remove(temp2);
		}
		cout << "1 : ";
		mt1.output();
		cout << "\n";
		cout << "2 : ";
		mt2.output();
		cout << "\n";

		cout << "Хотите ли произвести транзакцию (0/1): ";
		cin >> temp1;
		if (temp1)
		{
			cout << "Введите элемент из 1 множества : ";
			cin >> temp1;
			cout << "Введите элемент из 2 множества : ";
			cin >> temp2;
			Multitude<int>::trunzaction(mt1, temp1, mt2, temp2);

			cout << "1 : ";
			mt1.output();
			cout << "\n";
			cout << "2 : ";
			mt2.output();
			cout << "\n";
			
			cout << "Хотите выполнить откат транзакции (0/1): ";
			cin >> temp3;
			if (temp3)
			{
				cout << "Откат транзакции выполнен! \n";
				mt1.reload();
				mt2.reload();
			}
		}
		cout << "1 : ";
		mt1.output();
		cout << "\n";
		cout << "2 : ";
		mt2.output();
		cout << "\n";
	}
	catch (std::exception & ex) { cout << ex.what() << "\n"; }
	system("pause");
	return 0;
}