#pragma once
#include "AbstractList.h"
#include "AbstractIterator.h"
template <typename T>
struct Node {
	T value;
	Node* next;
	Node* prev;
};
template <typename T>
class List : public AbstractList<T>{
private:
	Node<T>* buffer;
	Node<T>* current;
	int size;
public:
	class ListIterator : public AbstractIterator<T>{
	private:
		List* list;
		bool flag;
	public:
		ListIterator(List* inputList):list(inputList){}
		void start() {
			if (list->isEmpty()){
				throw "The list is empty.";
			}
			list->current = list->buffer->next;
			flag = true;
		}
		T get() {
			if (list->isEmpty()) {
				throw "The list is empty.";
			}
			if (list->current == list->buffer) {
				if (flag) {
					list->current = list->buffer->next;
				}
				else {
					list->current = list->buffer->prev;
				}
			}
			return list->current->value;
		}
		void next() {
			list->current = list->current->next;
			if (list->current == list->buffer && !flag){
				flag = true;
			} 
		}
		bool isFinish() {
			return list->current == list->buffer;
		}
	};
	List() {
		size = 0;
		Node<T> *tmp = new Node<T>;
		tmp->value = 0;
		tmp->next = tmp;
		tmp->prev = tmp;
		buffer = tmp;
	}
	List(const List& list){
		Node<T> *tmp = new Node<T>;
		tmp->value = 0;
		tmp->next = tmp;
		tmp->prev = tmp;
		buffer = tmp;
		current = buffer;
		tmp = list.buffer->next;
		while (tmp != list.buffer) {
			push(tmp->value);
			tmp = tmp->next;
		}
	}
	List(List&& list):buffer(list.buffer),current(list.current), size(list.length){
		list.buffer = nullptr;
		list.current = nullptr;
		list.size = 0;
	}
	~List() {
		doEmpty();
		delete buffer;
	}
	List& operator= (const List& input) {
		if (input.buffer != this->buffer) {
			doEmpty();
			Node<T> *tmp = input.buffer->next;
			while (tmp != input.buffer) {
				push(tmp->value);
				tmp = tmp->next;
			}
		}
		return *this;
	}
	List& operator= (List&& input) {
		if (input.buffer != this->buffer) {
			doEmpty();
			buffer = input.buffer;
			current = input.current;
			size = input.size;
		}
		return *this;
	}
	void push(T elem) {
		Node<T> *tmp = new Node<T>;
		tmp->prev = current;
		tmp->value = elem;
		if (isEmpty()) {
			tmp->next = buffer;
			buffer->next = tmp;
			buffer->prev = tmp;
		}
		else {
			tmp->next = current->next;
			current->next = tmp;
			tmp->next->prev = tmp;
		}
		size++;
		current = tmp;
	}
	T pop() {
		if (isEmpty()) {
			throw "The list is empty.";
		}
		Node<T> *tmp = buffer->next;
		T res = tmp->value;
	    buffer->next = tmp->next;
		tmp->next->prev = buffer;
		delete tmp;
		size--;
		current = buffer->prev;
		return res;
	}
	void doEmpty() {
		while (!isEmpty()) {
			pop();
		}
		current = buffer;
	}
	int getSize() {
		return size;
	}
	ListIterator* findFirst(T elem) {
		ListIterator* listIter = iterator();
		listIter->start();
		while (!listIter->isFinish()) {
			if (listIter->get() == elem) {
				return listIter;
			}
			else {
				listIter->next();
			}
		}
		return nullptr;
	}
	ListIterator* iterator() {
		ListIterator* listIter = new ListIterator(this);
		return listIter;
	}
	bool isEmpty() {
		return size == 0;
	}
};