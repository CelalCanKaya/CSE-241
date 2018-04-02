#include "gtuset.cpp"
#include "gtumap.cpp"
#include <string>

using namespace GTUCck;


int main(){

	GTUSet<int> obj;
	GTUSet<int>::GTUIterator it;

	cout << "Integer Set Created." << endl << endl;

	try{
	obj.insert(7);
	cout << "7 Inserted!" << endl;
	obj.insert(2);
	cout << "2 Inserted!" << endl;
	}
	catch(invalid_argument){
		cerr << "This Element Is Already In This Set!" << endl;
	}

	cout << endl << "SET : ";
	for(it = obj.begin(); it != obj.end(); ++it){
		cout << *it << " ";
	};
	cout << endl << endl;

	obj.erase(2);
	cout << "2 Erased" << endl;
	obj.erase(5);
	cout << "5 Is Not In This Set" << endl;

	cout << endl << "SET : ";
	for(it = obj.begin(); it != obj.end(); ++it){
		cout << *it << " ";
	};
	cout << endl << endl;

	try{
	obj.insert(45);
	cout << "45 Inserted!" << endl;
	obj.insert(23);
	cout << "23 Inserted!" << endl;
	obj.insert(4);
	cout << "4 Inserted!" << endl;
	obj.insert(9);
	cout << "9 Inserted!" << endl;
	obj.insert(23);
	cout << "23 Inserted!" << endl;
	}
	catch(invalid_argument){
		cerr << endl << "EXCEPTION ----- This Element Is Already In This Set!" << endl;
	};

	cout << "Set Size: " << obj.size();

	cout << endl << "SET : ";
	for(it = obj.begin(); it != obj.end(); ++it){
		cout << *it << " ";
	};
	cout << endl << endl;

	obj.clear();
	cout << "Set Cleared!" << endl;
	obj.insert(8);
	cout << "8 Inserted" << endl;

	cout << endl << "SET : ";
	for(it = obj.begin(); it != obj.end(); ++it){
		cout << *it << " ";
	};
	cout << endl << endl;

	GTUSet<int> obj5;

	obj5.insert(7);

	cout << "-----------------------------------------------";

	GTUSet<string> obj2;
	GTUSet<string>::GTUIterator it2;

	cout << endl << endl << "String Set Is Created." << endl << endl;

	try{
	obj2.insert("Bursa");
	cout << "Bursa Inserted!" << endl;
	obj2.insert("Sivas");
	cout << "Sivas Inserted!" << endl;
	obj2.insert("Istanbul");
	cout << "Istanbul Inserted!" << endl;
	obj2.insert("Ankara");
	cout << "Ankara Inserted!" << endl;
	obj2.insert("Sivas");
	}
	catch(invalid_argument){
		cerr << endl << "EXCEPTION --- This Element Is Already In This Set!" << endl;
	};

	cout << endl << "SET : ";
	for(it2 = obj2.begin(); it2 != obj2.end(); ++it2){
		cout << *it2 << " ";
	}
	cout << endl << endl;

	obj2.erase("Bursa");
	cout << "Bursa Erased!" << endl;
	obj2.erase("Trabzon");
	cout << "Trabzon Is Not In This Set!" << endl;

	cout << endl << "SET : ";
	for(it2 = obj2.begin(); it2 != obj2.end(); ++it2){
		cout << *it2 << " ";
	};
	cout << endl << endl;

	obj2.clear();


	cout << "-----------------------------------------------" << endl;

	GTUMap<char, int> obj3;
	GTUMap<char, int>::GTUIterator it3;

	cout << endl << "Map Created!" << endl << endl;


	try{
		obj3.insert('a', 15);
		cout << "a 15 Inserted!" << endl;
		obj3.insert('b', 26);
		cout << "b 26 Inserted!" << endl;
		obj3.insert('d', 58);
		cout << "d 58 Inserted!" << endl;
		obj3.insert('d', 58);

	}
	catch(invalid_argument){
		cerr << endl << "EXCEPTION --- This Key Is Already In This Map!" << endl;
	};


	cout << endl << "MAP : ";
	for(it3 = obj3.begin(); it3 != obj3.end(); ++it3){
		cout << endl << it3->first << " " << it3->second << endl;
	};

	obj3.erase('a', 15);
	cout << endl << "a 15 Erased!" << endl;

	cout << endl << "MAP : ";
	for(it3 = obj3.begin(); it3 != obj3.end(); ++it3){
		cout << endl << it3->first << " " << it3->second << endl;
	};

	return 0;
}
