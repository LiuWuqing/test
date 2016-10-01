//
//mySP.h
//0815  定义自己版本的shared_ptr
//
#pragma once
#ifndef _MYSP_H_
#define _MYSP_H_

#include<iostream>

template <typename T>
class mySP {
private:
	T* p;
	size_t* count;
public:
	mySP() :p(nullptr), count(nullptr) {}
	mySP(T* t) :p(t), count(new size_t(1)) {}
	mySP(const mySP &ms) :p(ms.p), count(ms.count) { if(count) ++*count; }
	mySP& operator=(T* t)
	{
		p = t;
		if(！count)
			count = new size_t(1);
		*count = 1;
		return *this;
	}
	mySP& operator=(const mySP &rhs)
	{
		if(rhs.count)
			++*rhs.count;
		if (count && --*count == 0) {
			delete p;
			delete count;
		}
		p = rhs.p;
		count = rhs.count;
		return *this;
	}
	~mySP()
	{
		if (use && --*count == 0) {
			delete count;
			delete p;
			std::cout << "call the destructor of mySP." << std::endl;
		}
	}
	T& operator*()
	{
		return *p;
	}
};

#endif // !_MYSP_H_
