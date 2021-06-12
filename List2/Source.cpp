/*В двусвязный список добавить методы:
1. void push_back(int Data); DONE
2. void pop_front(); DONE
3. void pop_back(); DONE
4. void insert(int index, int data); DONE
5. void erase(int index); DONE
6. Деструктор должен очищать список; DONE
7. Этот проверочный код должен заработать:
	List list = {3,5,8,13,21}; DONE
	for(int i:list)
		cout << i << tab;
	cout << endl;*/

#include<iostream>
using namespace std;

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	} *Head, * Tail;//Сразу же после описания класса объявляем два указателя на объекты этого класса.
	unsigned int size;
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr)
		{
			this->Temp = Temp;
			cout << "ITConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ITDestructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*() const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}

	};
	//  Adding elements
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{			
		Element* New = new Element(Data);
		New->pNext = Head;
		New->pPrev = nullptr;
		if (Head) Head->pPrev = New;
		Head = New; 
		if (!Tail) Tail = Head;
		size++;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		New->pPrev = Tail;
		New->pNext = nullptr;
		if (Tail) Tail->pNext = New;
		Tail = New;
		if (!Head) Head = Tail;
		size++;
	}
	void insert(int index, int data)
	{
		if (index == 0)
		{
			push_front(data);
			return;
		}
		if (index == size)
		{
			push_back(data);
			return;
		}
		if (index > size)return;
		if (index <= size / 2)
		{
			Element* New = new Element(data);
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)
			{
				Temp = Temp->pNext;
			}
			New->pNext = Temp->pNext;
			New->pPrev = Temp;
			Temp->pNext->pPrev = New;
			Temp->pNext = New;
			size++;
		}
		else
		{
			Element* New = new Element(data);
			Element* Temp = Tail;
			for (int i = 0; i < size-index - 1; i++)
			{
				Temp = Temp->pPrev;
			}
			New->pPrev = Temp->pPrev;
			New->pNext = Temp;
			Temp->pPrev->pNext = New;
			Temp->pPrev = New;
			size++;
		}

	}
	void pop_front()
	{
		Element* to_del = Head;
		Head = Head->pNext;
		if (Head) Head->pPrev =nullptr;   
		else Tail = nullptr;
		delete to_del;
		size--;
	}
	void pop_back()
	{
		Element* to_del = Tail;
		Tail = Tail->pPrev;
		if (Tail) Tail->pNext = nullptr;
		else Head = nullptr;
		delete to_del;
		size--;
	}
	void erase(int index)
	{
		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index == size-1)
		{
			pop_back();
			return;
		}
		if (index >= size)return;
		if (index <= size / 2)
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)
			{
				Temp = Temp->pNext;
			}
			Element* to_del = Temp->pNext;
			Temp->pNext->pNext->pPrev = Temp;
			Temp->pNext = Temp->pNext->pNext;
			delete to_del;
			size--;
		}
		else
		{
			Element* Temp = Tail;
			for (int i = 0; i < size - index-2; i++)
			{
				Temp = Temp->pPrev;
			}
			Element* to_del = Temp->pPrev;
			Temp->pPrev->pPrev->pNext = Temp;
			Temp->pPrev = Temp->pPrev->pPrev;
			delete to_del;
			size--;
		}

	}
	void Print()
	{   
		
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << " " << Temp->pPrev << " " <<Temp->Data<<" "<<Temp->pNext<< endl;
			cout << "Количество элементов списка: "<<size<<endl;
		}
		cout << "------------------------------" << endl;
	}
};

void main()
{
	setlocale(LC_ALL,"Russian");
	int n,p;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand()%100);
	}
	list.Print();
	list.push_back(123);
	list.Print();
	list.pop_front();
	list.Print();
	list.pop_back();
	list.Print();
	cout << "Введите индекс добавляемого элемента: "; cin >> n;
	cout << "Введите значение добавляемого элемента: "; cin >> p;
	list.insert(n, p);
	list.Print();
	cout << "Введите индекс удаляемого элемента: "; cin >> n;
	list.erase(n);
	list.Print();
	List list2 = { 2,14,45,67,100 };
	list2.Print();
	for (int i : list2)
	{
		cout << i << " ";
	}
	cout << endl;
}