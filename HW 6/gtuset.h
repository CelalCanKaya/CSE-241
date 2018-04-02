#ifndef GTUSET_H
#define GTUSET_H

#include "gtusetbase.h"
#include <memory>

namespace GTUCck{
	template<class T>
	class GTUSet : public GTUSetBase<T>{		// SetBaseden inherit edildi
		public:
		class GTUIterator{
		public:
			GTUIterator(){		// Default constructor
				ptr=NULL;
			}
			GTUIterator(T* p){
				ptr=p;
			}
			T operator*(){		// Operator overload
				return *ptr;
			}
			T* operator->(){		// Arrow operator overload
				return ptr;
			}
			GTUIterator& operator++(){		// pre increment
				ptr++;
				return *this;
			}
			GTUIterator& operator++(int){		// post increment
				GTUIterator tmp = *this;
				ptr++;
				return tmp;
			}
			GTUIterator& operator--(){		// pre decrement	
				ptr--;
				return *this;
			}
			GTUIterator& operator--(int){		// post decrement
				GTUIterator tmp = *this;
				ptr--;
				return tmp;
			}
			bool operator==(const GTUIterator& second){		// Iki iteratoru karsilastiran operator overload
				return ptr==second.ptr;
			}
			bool operator!=(const GTUIterator& second){
				return ptr!=second.ptr;
			}
			GTUIterator& operator=(const GTUIterator& second){
				ptr=second.ptr;
				return *this;
			}
		private:
			T* ptr;
		};			
			GTUSet();
			virtual const bool empty() const;
			virtual const int size()const;
			virtual const int max_size() const;
			virtual void insert(const T& element);
			virtual const int erase(const T& element);
			virtual const GTUIterator find(const T& element)const;
			virtual void clear();
			virtual const int count(T& element)const;
		    virtual const GTUSet<T>::GTUIterator begin() const;
			virtual const GTUSet<T>::GTUIterator end() const;
			virtual void sortSet()const;
		private:
			int capacity;		// Toplam kapasitem
			int elementCounter;		// Eleman sayim
			shared_ptr<T> array;		// Shared pointer
			int maximum;		// Maximum eleman sayim
	};

	template<class T>		// Shared pointerda array olusturdugum icin array deleter yazdım
	class array_deleter{
	public:
		void operator ()(T const* p){
			delete [] p;
		}
	};
}

#endif
