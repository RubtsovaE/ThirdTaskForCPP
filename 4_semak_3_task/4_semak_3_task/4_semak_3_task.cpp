// 4_semak_3_task.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include "AbstractIterator.h"
#include "List.h"
#define COUNT 11
int main()
{
	using namespace std;
	system("color 75");
	cout << "Start" << endl;
	List<int> buffer;
	for (int i = 1; i < COUNT; i++) {
		buffer.push(i);
	}
	cout << "Size of List: " << buffer.getSize() << endl;
	List<int>::ListIterator iterator(&buffer);
	cout << "List: " << endl;
	iterator.start();
	while (!iterator.isFinish()) {
		cout << iterator.get() << " ";
		iterator.next();
	}
	cout << endl;
	List<int> copy(buffer);
	List<int>::ListIterator it(&copy);
	cout << "Copy of list: " << endl;
	it.start();
	while (!it.isFinish()) {
		cout << it.get() << " ";
		it.next();
	}
	cout << endl;
	cout << "List after popping one element: " << endl;
	buffer.pop();
	iterator.start();
	while (!iterator.isFinish()) {
		cout << iterator.get() << " ";
		iterator.next();
	}
	cout << endl;
	return 0;
}
