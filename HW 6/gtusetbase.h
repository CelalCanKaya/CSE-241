#ifndef GTUSETBASE_H
#define GTUSETBASE_H

#include <iostream>

using namespace std;

namespace GTUCck{
	template<class T>
	class GTUSetBase{
	public:		// Pure virtual fonksiyonlar
		virtual const bool empty() const = 0;
		virtual const int size() const = 0;
		virtual const int max_size() const = 0;
		virtual void insert(const T& element) = 0;
		virtual const int erase(const T& element) = 0;
		virtual void clear() = 0;
		virtual const int count(T& element)const= 0;
		//virtual GTUIterator find(T& element) = 0;
		//virtual GTUIterator begin() = 0;
		//virtual GTUIterator end() = 0;
	};
}

#endif