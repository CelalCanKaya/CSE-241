#include "gtuset.h"

using namespace std;

namespace GTUCck{

	template <class T>
	GTUSet<T>::GTUSet(){	// Default constructorda memberlari initialize ettim
		capacity = 10;
		elementCounter = 0;
		shared_ptr<T> temp1(new T[capacity], array_deleter<T>());
		array = temp1;
		maximum=1280;
	}

	template <class T>
	const bool GTUSet<T>::empty() const{		// Eger elementCounter im 0'dan buyuk ise Set empty olmadigi icin false dondurdum
		if(elementCounter>0){
			return false;
		}
		return true;
	}

	template <class T>
	const int GTUSet<T>::size() const{			// elementCounterda size'i tuttugum icin return ettim
		return elementCounter;
	}

	template <class T>
	int const GTUSet<T>::max_size() const{		// Maximum elemen default constructorda initialize edilmisti.O Degeri return ediyorum
		return maximum;
	}

	template <class T>
	void GTUSet<T>::clear(){		// Shared ptr'mi sifirlayip tekrar 10'luk yer aliyorum. Default constructorımda yapilan seyler yapiliyor.
		capacity = 10;
		elementCounter = 0;
		array.reset();
		shared_ptr<T> temp1(new T[capacity], array_deleter<T>());
		array = temp1;
		cout << "Set Is Cleared!" << endl;
	}

	template <class T>
	void GTUSet<T>::insert(const T& element){
		int duplicate = 0;
		for(int i=0; i<elementCounter; i++){		// Eklemeye calistigim elemanın set icinde olup olmadigini kontrol ediyorum
			if(array.get()[i]==element){
				duplicate = 1;
			}
		}
		if(elementCounter>capacity){		// Eger size kapasiteyi astiysa 
			capacity=capacity*2;		// Kapasiteyi iki katina cikariyorum
			shared_ptr<T> temp2(new T[capacity], array_deleter<T>());		// Temp shared ptr olusturup dongum icerisinde tum elemanları ona aktariyorum
			array = temp2;
			for(int i=0; i<elementCounter; i++){
				temp2.get()[i] = array.get()[i];		
			}
			array.reset();		// Arrayimi resetliyorum ve tekrardan yeni kapasite kadar yer aliyorum
			shared_ptr<T> temp1(new T[capacity], array_deleter<T>());
			array = temp1;
			for(int i=0; i<elementCounter; i++){		// Temp'e attigim elemanları tekrardan arrayime aliyorum
				array.get()[i] = temp2.get()[i];
			}
			temp2.reset();
		}
		if(!duplicate && elementCounter<=maximum){		// Eger eklemeye calistigim eleman sette yoksa
			array.get()[elementCounter] = element;		// Elemani setin sonuna ekleyip size'i 1 arttiriyorum ve setimi sortluyorum
			elementCounter++;
			sortSet();
		}
		else{
			throw std::invalid_argument("Inserting Element Is Already In This Set");		// Eger sete eklemeye calistigim eleman zaten sette varsa exception throwluyorum
		}
	}

	template <class T>
	const int GTUSet<T>::count(T& element) const{		// Sete eklemeye calistigim elemanin sette olup olmadigini kontrol ediyorum
		for(int i=0; i<elementCounter; i++){
			if(element == array.get()[i]){
				return 1;
			}
		}
		return 0;
	}

	template <class T>
	const typename GTUSet<T>::GTUIterator GTUSet<T>::begin()const{		// Iteratoru basa döndürüyorum
		return GTUIterator(array.get());
	}

	template <class T>
	const typename GTUSet<T>::GTUIterator GTUSet<T>::end()const {		// Iteratoru sona döndürüyorum
		return GTUIterator(array.get()+elementCounter);
	}

	template <class T>
	const int GTUSet<T>::erase(const T& element){
		int found = 0;
		for(int i=0; i<elementCounter; i++){		// Silmeye calistigim elamanin sette olup olmadigini kontrol ediyorum
			if(array.get()[i]==element){
				found = 1;
			}
		}
		if(found==1){
			int counter = 0; 
			shared_ptr<T> temp2(new T[capacity], array_deleter<T>());
			for(int i=0; i<elementCounter; i++){		// Silecegim elemana kadar olan elemanlari temp arrayime atiyorum
				if(array.get()[i]==element){
					break;
				}
				temp2.get()[i] = array.get()[i];
				counter++;
			}
			for(int i = counter; i<elementCounter; i++){		// Silmeye calistigim elemani atliyorum geri kalani temp arrayime atiyorum
				if(i+1==elementCounter){		// Memoryde sahip olmadigimiz yere ulasmamak icin gerekli if
					break;
				}
				else{
					temp2.get()[i]=array.get()[i+1];
				}
			}
			array.reset();	// Arrayimi sifirlayip tekrardan yer aliyorum ve size'i bir azaltiyorum
			elementCounter--;
			shared_ptr<T> temp1(new T[capacity], array_deleter<T>());
			array = temp1;
			for(int i=0; i<elementCounter; i++){		// Temp arrayimi tekrardan arrayime atiyorum
				array.get()[i] = temp2.get()[i];
			}
			temp2.reset();
			return 1;
		}
		else{
			return 0;
		}
	}

	template<class T>
	const typename GTUSet<T>::GTUIterator GTUSet<T>::find(const T& element)const{		// Sette aradigim eleman varsa iteratoru o elemana goturuyorum
		for(int i=0; i<elementCounter; i++){
			if(element==array.get()[i]){
				return GTUIterator(array.get() + i);
			}
		}
	}

	template<class T>
	void GTUSet<T>::sortSet()const{		// Seti sortlayan fonksiyon
    	T temp;
    	for (int i = 0 ; i < elementCounter; i++)
    	{
        	for (int j = 0 ; j < elementCounter - 1 ; j++)
        	{
            	if ( array.get()[j] > array.get()[j + 1] )
            	{
	                temp = array.get()[j];
	                array.get()[j]=array.get()[j + 1];
	                array.get()[j + 1] = temp;
            	}
        	}
   	 	}
	}
}

