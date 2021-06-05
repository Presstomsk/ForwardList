#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
class ForwardList;
ForwardList operator+(const ForwardList& right, const ForwardList& left);

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element* get_pNext()
	{
		return this->pNext;
	}
	void set_pNext(Element* pNext)
	{
		this->pNext = pNext;
	}
	Element(int Data, Element* pNext = nullptr)
	{
		count++;
		this->Data = Data;//Данные
		this->pNext = pNext;//указатель на следующий элемент
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{ 
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
	friend ForwardList operator+(const ForwardList& right, const ForwardList& left);
};
int Element::count = 0;
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
class ForwardList
{
	Element* Head;//Адрес начального элемента
	unsigned int size;
public:
	Element* get_Head() const
	{
		return Head;
	}
	void set_Head(Element* Head)
	{
		this->Head = Head;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;//Если Голова указывает на 0, то список пуст
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il):ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other):ForwardList()
	{   
		//size = 0;
		//Head = nullptr;
		Element* Temp = other.Head;//Итератор Temp будет проходить по списку other
		while (Temp)
		{
			push_back(Temp->Data);//Каждый элемент списка other добавляем в конец нашего списка
			Temp = Temp->pNext; // Переход на следующий элемент
		}
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) noexcept
	{
		this->size = other.size;
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{   
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	// Adding elements
	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Element* New = new Element(Data);
		//2) Привязываем новый элемент к списку
		New->pNext = Head;
		//3) Говорим, что новый элемент будет начальным элементом списка
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)//Если список пуст, вызываем push_front
		{
			push_front(Data);
			return;
		}
	    //1) Создаем новый элемент
		Element* New = new Element(Data);
		//2) Доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		//3) Прикрепляем новый элемент к последнему
		Temp->pNext = New;
		size++;
	}
	// Erasing elements:
	void pop_front()
	{
	    //1) Запоминаем адрес удаляемого элемента
		Element* to_del = Head;
		//Исключаем удаляемый элемент из списка
		Head = Head->pNext;
		//3) Удаляем элемент из памяти
		delete to_del;
		size--;
	}
	void pop_back()
	{   //1) Доходим до предпоследнего элемента
		Element* to_del = Head;
		while (to_del->pNext->pNext)
			to_del = to_del->pNext;
		//2) Удаляем последний элемент из памяти
		delete to_del->pNext;
		//3) Зануляем указатель на предпоследний элемент
		to_del->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index >= size)return;
		Element* Temp = Head;// Итератор
		for (int i = 0; i < Index - 1; i++)//Доходим до элемента перед удаляемым
		{
			Temp = Temp->pNext;
		}
		Element* to_del = Temp->pNext;//Запоминаем адрес удаляемого элемента
		Temp->pNext = Temp->pNext->pNext;//Исключаем элемент из списка
		delete to_del;//Удаляем элемент*/
		size--;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Index > size)return;
		//1) Создаем новый элемент
		Element* New = new Element(Data);
		Element* Temp = Head;
		//2) Доходим до нужного элемента
		for (int i = 0; i < Index-1; i++)
		{
			Temp = Temp->pNext;			
		}
		//3) Вставляем нужный элемент на необходимую позицию
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;//Итератор Temp будет проходить по списку other
		while (Temp)
		{
			push_back(Temp->Data);//Каждый элемент списка other добавляем в конец нашего списка
			Temp = Temp->pNext; // Переход на следующий элемент
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) noexcept
	{
		while (Head)pop_front();
		this->size = other.size;
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator+=(const ForwardList& right) 
	{
		//1) Доходим до конца первого списка
		
		ForwardList Copyright = right;
		Element* Temp = this->Head;
		while (Temp->pNext)
			Temp=Temp->pNext;
		//3) "Сшиваем списки"
		Temp->pNext = Copyright.Head;
		Copyright.Head=nullptr;
		return *this;
	}
	
	//Methods
	void print()
	{
		Element* Temp = Head;//Temp-итератор.
		while (Temp)         //Итератор-это указатель, при помощи которого
			                 //можно получить доступ к элементам структуры данных
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	//1) Доходим до конца первого списка
	ForwardList cat = left;
	for (Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}
#define BASE_CHECK
//#define COPY_METHODS_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANG_BASED_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef COPY_METHODS_CHECK
	int n; //Размер списка
	cout << "Введите количество элементов списка: "; cin >> n;
	ForwardList list,list5;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		list5.push_back(rand() % 100);
	}
	list.print();

	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	int index, value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index,value);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	ForwardList list2 = list; //CopyConstructor
	list2.print();
	ForwardList list3;
	list3 = list2;     //CopyAssignment
	list3.print();
#endif // COPY_METHODS_CHECK
#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1 = {3,5,8,13,21};
	/*list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);*/
	ForwardList list2= {34,55,89};
	/*list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);*/

	ForwardList list3 = list1 + list2;//MoveConstructor
	list3.print();
	list1 = list3 + list2;//MoveAssignment
	list1.print();
#endif //OPERATOR_PLUS_CHECK
#ifdef RANG_BASED_LIST
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	//Range-based for(Цикл for для контейнера)
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif RANG_BASED_LIST
	ForwardList list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	for (Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}