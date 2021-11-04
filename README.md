# ForwardList

В класс ForwardList добавить методы:

1. void erase(int index);		//Удаляет значение по заданному индексу
2. Написать деструктор таким образом, чтобы он очищал список (удалял из него све элементы) перед удалением;
3. Оптимировать методы удаления элементов;
4. CopyMethods
5. MoveMethods
6. Обеспечить создание списка следующим образом:

	ForwardList list = { 3, 5, 8, 13, 21 };
	
В двусвязный список добавить методы:

В двусвязный список добавить методы:

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
	cout << endl;
  
