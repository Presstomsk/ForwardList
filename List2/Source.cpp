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
	//  Adding elements
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{	
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);		
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;
	}
	void Print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << " " << Temp->pPrev << " " <<Temp->Data<<" "<<Temp->pNext<< endl;
			cout << "Количество элементов списка: "<<size<<endl;
		}
	}
};

void main()
{
	setlocale(LC_ALL,"Russian");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand()%100);
	}
	list.Print();
}