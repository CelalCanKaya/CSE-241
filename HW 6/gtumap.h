#ifndef GTUMAP_H
#define GTUMAP_H

#include "gtuset.h"

// Map header dosyasi

namespace GTUCck{
	template<class K, class V>
	class GTUMap : public GTUSet<std::pair<K, V> >{
		public:
			GTUMap();	// Default constructor
			void insert(const K& key, const V& element);
			const int erase(const K& key, const V& element);
			const int count(const K& key) const;
			const V& operator[](const K& key);
		    const typename GTUMap<K,V>::GTUIterator begin() const;
		    const typename GTUMap<K,V>::GTUIterator end() const;
			const typename GTUMap<K,V>::GTUIterator find(const K& key) const;
		private:
			int capacity;
			int elementCounter;
			shared_ptr<pair<K,V>> array;
			int maximum;
	};
}

#endif