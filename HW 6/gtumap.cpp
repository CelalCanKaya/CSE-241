#include "gtumap.h"

namespace GTUCck{

	template <class K, class V>
	GTUMap<K,V>::GTUMap(){
		capacity = 10;
		elementCounter = 0;
		shared_ptr<pair<K,V>> temp1(new pair<K,V>[capacity], array_deleter<pair<K,V>>());
		array = temp1;
		maximum=1280;
	}


	template<class K, class V>
	void GTUMap<K,V>::insert(const K& key, const V& element){
		int duplicate = 0;
		for(int i=0; i<elementCounter; i++){		// Eklemeye calistigim elemanın map icinde olup olmadigini kontrol ediyorum
			if(array.get()[i].first==key){
				duplicate = 1;
			}
		}
		if(elementCounter>capacity && elementCounter<=maximum){		// Eger size kapasiteyi astiysa 
			capacity=capacity*2;		// Kapasiteyi iki katina cikariyorum
			shared_ptr<pair<K,V>> temp2(new pair<K,V>[capacity], array_deleter<pair<K,V>>());		// Temp shared ptr olusturup dongum icerisinde tum elemanları ona aktariyorum
			array = temp2;
			for(int i=0; i<elementCounter; i++){
				temp2.get()[i].first = array.get()[i].first;
				temp2.get()[i].second = array.get()[i].second;
			}
			array.reset();		// Arrayimi resetliyorum ve tekrardan yeni kapasite kadar yer aliyorum
			shared_ptr<pair<K,V>> temp1(new pair<K,V>[capacity], array_deleter<pair<K,V>>());
			array = temp1;
			for(int i=0; i<elementCounter; i++){		// Temp'e attigim elemanları tekrardan arrayime aliyorum
				array.get()[i].first = temp2.get()[i].first;
				array.get()[i].second = temp2.get()[i].second;
			}
			temp2.reset();
		}
		if(!duplicate){		// Eger eklemeye calistigim eleman mapte yoksa
			array.get()[elementCounter].first = key;		// Elemani setin sonuna ekleyip size'i 1 arttiriyorum ve mapimi sortluyorum
			array.get()[elementCounter].second = element;
			elementCounter++;
		}
		else{
			throw std::invalid_argument("Inserting Element Is Already In This Set");
		}	
	}


	template<class K, class V>
	const int GTUMap<K,V>::erase(const K& key, const V& element){
		int found = 0;
		for(int i=0; i<elementCounter; i++){
			if(array.get()[i].first==key && array.get()[i].second == element){		// Silmeye calistigim elamanin mapte olup olmadigini kontrol ediyorum	
				found = 1;
			}
		}
		if(found==1){
			int counter = 0; 
			shared_ptr<pair<K,V>> temp2(new pair<K,V>[capacity], array_deleter<pair<K,V>>());
			for(int i=0; i<elementCounter; i++){// Silecegim elemana kadar olan elemanlari temp arrayime atiyorum		
				if(array.get()[i].first==key){
					break;
				}
				temp2.get()[i].first = array.get()[i].first;
				temp2.get()[i].second = array.get()[i].second;
				counter++;
			}
			for(int i = counter; i<elementCounter; i++){    	// Silmeye calistigim elemani atliyorum geri kalani temp arrayime atiyorum
				if(i+1==elementCounter){	// Memoryde sahip olmadigimiz yere ulasmamak icin gerekli if
					break;
				}
				else{
					temp2.get()[i].first=array.get()[i+1].first;
					temp2.get()[i].second=array.get()[i+1].second;
				}
			}
			array.reset();	// Arrayimi sifirlayip tekrardan yer aliyorum ve size'i bir azaltiyorum
			elementCounter--;
			shared_ptr<pair<K,V>> temp1(new pair<K,V>[capacity], array_deleter<pair<K,V>>());
			array = temp1;
			for(int i=0; i<elementCounter; i++){		// Temp arrayimi tekrardan arrayime atiyorum
				array.get()[i].first = temp2.get()[i].first;
				array.get()[i].second = temp2.get()[i].second;
			}
			temp2.reset();
			return 1;
		}
		else{
			cout << "This Key Doesnt Exist In This Map";
			return 0;
		}
	}

	template <class K, class V>
	const int GTUMap<K,V>::count(const K& key) const{		// Mape eklemeye calistigim elemanin sette olup olmadigini kontrol ediyorum
		for(int i=0; i<elementCounter; i++){
			if(key == array.get()[i].first){
				return 1;
			}
		}
		return 0;
	}

	template<class K, class V>
	const typename GTUMap<K,V>::GTUIterator GTUMap<K,V>::begin() const{		// Iteratoru basa döndürüyorum
		return array.get();
	}

	template<class K, class V>
	const typename GTUMap<K,V>::GTUIterator GTUMap<K,V>::end() const{		// Iteratoru sona döndürüyorum
		return (array.get()+elementCounter);

	}

	template<class K, class V>
	const typename GTUMap<K,V>::GTUIterator GTUMap<K,V>::find(const K& key)const{		// Sette aradigim eleman varsa iteratoru o elemana goturuyorum
		for(int i=0; i<elementCounter; i++){
			if(key==array.get()[i].first){
				return array.get() + i;
			}
		}
	}

	template<class K, class V>
	const V& GTUMap<K,V>::operator [](const K& key){	// Operator overload
		for(int i = 0; i < elementCounter; i++)
		{
			if(array.get()[i].first == key)
			{
				return array.get()[i].second;
			}
		}
	}
}