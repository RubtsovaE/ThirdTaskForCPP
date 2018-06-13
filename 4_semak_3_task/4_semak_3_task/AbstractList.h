#pragma once
#include "AbstractIterator.h"
template <typename T>
class AbstractList{
public:
	virtual void push(const T) = 0;
	virtual T pop() = 0;
	virtual AbstractIterator<T>* findFirst(const T) = 0;
	virtual void doEmpty() = 0;
	virtual bool isEmpty() = 0;
	virtual int getSize() = 0;
	virtual AbstractIterator<T>* iterator() = 0;
};
